/**
 * @file AlarmCode.ino
 * @author Ben Kellman - V00898289
 * @brief ECE299 Alarm Clock project, runs on an Arduino UNO R3.
 * @version 0.1
 * @date 2020-07-16
 *
 */

#include <LiquidCrystal.h>

/**
 * @brief Used for enabling debug printing, breaks simulator
 *
 */
// #define DEBUG

#define MILLIS_PER_SECOND 17

#define SLOW_INC_DELAY 100
#define FAST_INC_DELAY 150
#define SLOW_TO_FAST_INC_TIME SLOW_INC_DELAY*10 - SLOW_INC_DELAY/2

#define BRIGHTNESS_PER_PERCENT 8
#define SNOOZE_TIME 5*60

#define B_TIME_INC    6
#define B_TIME_DEC    7
#define B_SNOOZE      A2
#define B_CANCEL      A1
#define B_BACKLIGHT   A3
#define B_ALARM_SET   A4

#define BACKLIGHT_PIN 10
#define LIGHT_SENSE   A0
#define BUZZER        9

/* Tinkercad doesn't support nullptr (but latest arduino ide does), hacky way to allow it to run on tinkercad*/
#define nullptr NULL
#define ALARM_ENABLED_MSG  "Alarm Enabled   "
#define ALARM_DISABLED_MSG "Alarm Disabled  "

/**
 * @brief A struct to hold the current state of a button (used to form a linked list of all
 * buttons used in the UI)
 *
 */
struct Button
{
    Button *next;
    bool last_state;
    bool true_state;
    bool been_pressed;
    bool been_released;
    unsigned long last_changed;
    unsigned char pin_id;
};

/**
 * @brief A static only class used to mange regestering and de-bouncing button presses
 *
 * @details Registers Press and Release events, one press event occurs when a button is initally pressed
 * and one release event occurs when it is released. These events can be accessed by the check_for_press and
 * check_for_release fuctions. Checking an event will clear it by default.
 */
class UI
{
public:
    /**
     * @brief How long the button must go without it's state chaing for a state
     * change to be registered (in ms). Will configure it as input pullup.
     *
     */
    static const unsigned long debounce_delay = 50;

    /**
     * @brief Adds a button to the UI
     *
     * @param pin_id The pin that the button is connected to (0, 2, 13, A0, ect.)
     */
    void static add_button(unsigned int pin_id);

    /**
     * @brief Updates the buttons. MUST be called regularly (Once per loop).
     *
     */
    void static poll_buttons();

    /**
     * @brief Will reset the pressed/released states for all buttons (set to false)
     *
     * @details Should be used if an button is not being used in a state, since if it is pressed in that state
     * the press/release flags will still be set. This could cause unexpected behaviour when entering a new state.
     * i.e. button press from a long time ago could suddenly register.
     */
    void static clear_flags();

    /**
     * @brief Checks if the button associated with pin_id has been pressed
     *
     * @param pin_id The pin number the button is connected to
     * @param clear Clear on read (true by default), will not reset the state on calling the function if set to false.
     * @return true The button has been pressed (since last call)
     * @return false The button has not been pressed (since last call)
     */
    bool static check_for_press(unsigned int pin_id, bool clear=true);

    /**
     * @brief Checks if the button associated with pin_id has been released
     *
     * @param pin_id The pin number the button is connected to
     * @param clear clear Clear on read (true by default), will not reset the state on calling the function if set to false.
     * @return true The button has been released (since last call)
     * @return false The button has not been released (since last call)
     */
    bool static check_for_release(unsigned int pin_id, bool clear=true);

private:
    static Button *head;

    static Button* last_node();

    void static update_button(Button *);
};

Button* UI::head = nullptr;

/**
 * @brief Used to store and increment a time in 24h format
 *
 */
struct Time
{
    int hours;
    int minutes;
    int seconds ;

    /**
     * @brief Used to increment the time by delta_seconds seconds
     *
     * @param delta_seconds Number of seconds to increment by
     */
    void increment(int delta_seconds){
        seconds += delta_seconds;
        if (seconds >= 0)
        {
            minutes += (seconds/60);
            hours   += (minutes/60);

            seconds  %= 60;
            minutes  %= 60;
            hours    %= 24;
        }
        else
        {
            while(seconds<0)
            {
                seconds += 60;
                minutes -= 1;
            }

            while (minutes < 0)
            {
                minutes += 60;
                hours -= 1;
            }

            while (hours < 0)
            {
                hours +=24;
            }
        }
    }
};


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
bool ClockRunning = false;
bool AlarmActive = false;

/**
 * @brief Stores values used for digitalWrite when setting backlight brightness
 *
 */
enum BacklightMode_t{
    OFF = 0,
    ON,
    AUTO
};

/**
 * @brief The internal States used for the alarm, see the main loop form more details
 *
 */
enum States{
    TIME_UNSET,
    ALARM_TIME_SET,
    ALARM_SET,
    CLOCK,
    ALARM_TRIGGERED,
    SNOOZEING,
    SLOW_CHANGE,
    FAST_CHANGE,
    TIME_CHANGE,
    BACKLIGHT_MODE,
    BACKLIGHT_THRES_ADJ
};

/**
 * @brief The current state of the alarm clock
 *
 */
States CurrentState = TIME_UNSET;

BacklightMode_t BacklightMode = AUTO;

unsigned int BacklightThreshold = 80;

/**
 * @brief Used by some states to measrue elapsed time inside state
 *
 */
unsigned long StateChangeTime;

/**
 * @brief Used by the TIME_CHANGE state to increment the current time periodically (press and hold)
 *
 */
unsigned long LastIncTime;

/**
 * @brief Used to store the sign for TIME_CHANGE logic (incrementing or decrementing current time)
 *
 */
char time_inc_sign;

/**
 * @brief Used so TIME_CHANGE can know if it is setting an alarm time or the clock time
 *
 */
bool SettingAlarmTime = false;

bool ShowTime = true;

bool AlarmTriggered = false;

/**
 * @brief Used to update the current time (based on millis() so it will not be very accurate,
 * could dedicate a timer to this task if desired)
 *
 */
void updateTime();

/**
 * @brief Used to dispaly a time on the LCD
 *
 * @param time A pointer to a Time struct (must be cast to a void*,
 * since tinkercad doesn't seem to allow function parameters that are structs or classes....)
 * @param alarm_time If this is the alarm time or current time (alarm time will be displayed on second row with text to
 * indicate that an alarm is set for this time)
 */
void displayTime(void* time, bool alarm_time=false);

/**
 * @brief The Current clock time
 *
 */
Time CurrentTime;

/**
 * @brief The time the alarm is set for
 *
 */
Time AlarmTime;

/**
 * @brief A pointer passed to the TIME_CHANGE state to simplify the logic of setting both the alarm
 * and clock time
 *
 */
Time* TimeSetTime;

void setup()
{
    /*Print debug messages over serial if #define DEBUG is present*/
    #ifdef DEBUG
        Serial.begin(9600);
        Serial.println("Starting with debugging prints enabled");
    #endif
    /* Initialize LCD */
    lcd.begin(16, 2);

    /* Initialize all used pins */
    pinMode(BACKLIGHT_PIN, OUTPUT);
    pinMode(LIGHT_SENSE  , INPUT);
    pinMode(BUZZER       , OUTPUT);

    digitalWrite(BACKLIGHT_PIN, LOW);
    lcd.setCursor(0, 0);
    lcd.print("  Time Not Set  ");
    lcd.setCursor(0, 1);
    lcd.print("  No Alarm Set  ");

    UI::add_button(B_TIME_INC );
    UI::add_button(B_TIME_DEC );
    UI::add_button(B_SNOOZE   );
    UI::add_button(B_CANCEL   );
    UI::add_button(B_BACKLIGHT);
    UI::add_button(B_ALARM_SET);
}

void loop()
{
    bool t_inc;
    bool t_dec;
    /**
     * @brief The FSM Logic
     *
     */
    switch (CurrentState)
    { // TODO: Add alarm triggered, snooze, and adjust backlight states
        /**
         * @brief The state the alarm enters after a reset
         *
         * @details Exits state to CLOCK when the TIME_INC or TIME_DEC buttons are pressed, never reenters
         */
    case TIME_UNSET:

        if (UI::check_for_press(B_TIME_INC, false) || UI::check_for_press(B_TIME_DEC, false))
        {
            TimeSetTime  = &CurrentTime;
            CurrentState = CLOCK;

            CurrentTime.hours   = 0;
            CurrentTime.minutes = 0;
            CurrentTime.seconds = 0;
        }

        break;

    /**
     * @brief Main state, displays time and alarm info while keeping time
     *
     * @details Exits to appropriate state when any UI button is pressed
     */
    case CLOCK:
        noTone(BUZZER);
        t_inc = UI::check_for_press(B_TIME_INC);
        t_dec = UI::check_for_press(B_TIME_DEC);

        if (t_inc || t_dec)
        {
            ClockRunning = false;
            SettingAlarmTime = false;
            TimeSetTime  = &CurrentTime;
            StateChangeTime = millis();
            LastIncTime = 0;
            TimeSetTime->seconds = 0;

            if (t_inc)
            {
                time_inc_sign = 1;
            }

            else
            {
                time_inc_sign = -1;
            }

            CurrentState = SLOW_CHANGE;
        }

        else if(UI::check_for_press(B_ALARM_SET)){
            UI::clear_flags();
            TimeSetTime  = &AlarmTime;
            CurrentState = ALARM_TIME_SET;
            lcd.setCursor(0, 1);
            lcd.print("Alarm Set: ");
            displayTime((void*)&AlarmTime, true);
        }

        else if (UI::check_for_press(B_BACKLIGHT))
        {
            CurrentState = BACKLIGHT_MODE;
            lcd.clear();
            diplay_backlight_mode();
            ShowTime = false;
        }

        else if (CurrentTime.minutes == AlarmTime.minutes && CurrentTime.hours == AlarmTime.hours && AlarmActive)
        {
            if (!AlarmTriggered)
            {
                CurrentState = ALARM_TRIGGERED;
                AlarmTriggered = true;
                tone(BUZZER, 1000);
                UI::clear_flags();
            }
        }

        else
        {
            AlarmTriggered = false;
        }


        //TODO: Add Backlight input check and check for alarm being triggered (probably only need to check in CLOCK)
        break;

    /**
     * @brief Used to set the time of the alarm
     *
     * @details Will go into TIME_CHANGE if the T+ or T- buttons are pressed. Pressing the Alarm set button again
     * will exit to the ALARM_SET state. No other buttons have any effect.
     */
    case ALARM_TIME_SET:
        t_inc = UI::check_for_press(B_TIME_INC);
        t_dec = UI::check_for_press(B_TIME_DEC);

        if (t_inc || t_dec)
        {
            StateChangeTime = millis();
            LastIncTime = 0;
            TimeSetTime->seconds = 0;
            SettingAlarmTime = true;

            if (t_inc)
            {
                time_inc_sign = 1;
            }

            else
            {
                time_inc_sign = -1;
            }

            CurrentState = SLOW_CHANGE;
        }

        if (UI::check_for_press(B_ALARM_SET))
        {
            CurrentState = ALARM_SET;
            AlarmActive = true;
            lcd.setCursor(0, 1);
            lcd.print(ALARM_ENABLED_MSG);
        }

        break;

    /**
     * @brief Used to disable or enable the alarm
     *
     * @details Will toggle alarm status on pressing T+ or T- buttons. Exits to CLOCK on pressing Alarm set again.
     */
    case ALARM_SET:
        if (UI::check_for_press(B_TIME_DEC) || UI::check_for_press(B_TIME_INC))
        {
            AlarmActive = !AlarmActive;
            lcd.setCursor(0, 1);

            if (AlarmActive)
            {
                lcd.print(ALARM_ENABLED_MSG);
            }
            else
            {
                lcd.print(ALARM_DISABLED_MSG);
            }
        }

        if (UI::check_for_press(B_ALARM_SET))
        {
            CurrentState = CLOCK;
            UI::clear_flags();
            if (AlarmActive)
            {
                lcd.setCursor(0, 1);
                lcd.print("Alarm At:  ");
                displayTime((void*) TimeSetTime, true);
            }
            else
            {
                lcd.setCursor(0, 1);
                lcd.print("  No Alarm Set  ");
            }

        }

        break;

    /**
     * @brief Used for incrementing the current time or alarm time by 1 minute
     *
     */
    case SLOW_CHANGE:
        if (UI::check_for_release(B_TIME_DEC) || UI::check_for_release(B_TIME_INC))
        {
            ClockRunning = true;
            UI::clear_flags();
            if(SettingAlarmTime)
            {
                CurrentState = ALARM_TIME_SET;
            }
            else
            {
                CurrentState = CLOCK;
            }
        }
        else
        {
            if ((millis()-StateChangeTime) >= SLOW_TO_FAST_INC_TIME && TimeSetTime->minutes%10 == 0)
            {
                CurrentState = FAST_CHANGE;
                #ifdef DEBUG
                    Serial.println(millis()-StateChangeTime);
                #endif
            }
            else if (millis()-LastIncTime >= SLOW_INC_DELAY)
            {
                LastIncTime = millis();
                TimeSetTime->increment(time_inc_sign*60);
                displayTime((void*)TimeSetTime, SettingAlarmTime);
            }
        }
        break;

    /**
     * @brief Used to change the alarm or current time by 10 minutes
     *
     */
    case FAST_CHANGE:
        if (millis()-LastIncTime >= FAST_INC_DELAY)
        {
            LastIncTime = millis();
            TimeSetTime->increment(time_inc_sign*600);
            displayTime((void*)TimeSetTime, SettingAlarmTime);
        }
        if (UI::check_for_release(B_TIME_DEC, false) || UI::check_for_release(B_TIME_INC, false))
        {
            CurrentState = SLOW_CHANGE;
        }
        break;

    case BACKLIGHT_MODE:
        t_inc = UI::check_for_press(B_TIME_INC);
        t_dec = UI::check_for_press(B_TIME_DEC);
        if (t_inc || t_dec)
        {
            if (t_inc)
            {
                BacklightMode = (BacklightMode_t)((unsigned int)BacklightMode + 1);
                if ((unsigned int)BacklightMode > AUTO)
                {
                    BacklightMode = OFF;
                }
            }
            else
            {
                BacklightMode = (BacklightMode_t)((unsigned int)BacklightMode - 1);
                if ((unsigned int)BacklightMode > AUTO)
                {
                    BacklightMode = AUTO;
                }
            }
            diplay_backlight_mode();
        }

        if (UI::check_for_press(B_BACKLIGHT))
        {
            CurrentState = CLOCK;
            lcd.setCursor(0, 1);
            lcd.print("Alarm At:  ");
            displayTime((void*)&CurrentTime);
            displayTime((void*)&AlarmTime, true);
            ShowTime=true;
        }
        break;

    case ALARM_TRIGGERED:
        if (UI::check_for_press(B_SNOOZE))
        {
            CurrentState = SNOOZEING;
            StateChangeTime = millis();
            noTone(BUZZER);
            lcd.clear();
            displayTime((void*)&CurrentTime);
            lcd.setCursor(0, 1);
            lcd.print("    Snoozing    ");
        }
        else if (UI::check_for_press(B_CANCEL))
        {
            CurrentState = CLOCK;
            noTone(BUZZER);
            UI::clear_flags();
            lcd.setCursor(0, 1);
            lcd.print("Alarm At:  ");
            displayTime((void*)&AlarmTime, true);
        }

        break;

    case SNOOZEING:
        if (millis()-StateChangeTime > SNOOZE_TIME*MILLIS_PER_SECOND)
        {
            CurrentState = ALARM_TRIGGERED;
            tone(BUZZER, 1000);
            lcd.setCursor(0, 1);
            lcd.print("Alarm At:  ");
            displayTime((void*)&AlarmTime, true);
        }
        else if (UI::check_for_press(B_CANCEL))
        {
            CurrentState = CLOCK;
            UI::clear_flags();
            lcd.setCursor(0, 1);
            lcd.print("Alarm At:  ");
            displayTime((void*)&AlarmTime, true);
        }
        break;

    default:
        #ifdef DEBUG
            Serial.println("Error, undefined state reached");
        #endif
        break;
    }

    /*Update Logic*/

    switch (BacklightMode)
    {
    case AUTO:
        if (analogRead(LIGHT_SENSE)/BRIGHTNESS_PER_PERCENT < BacklightThreshold)
        {
            digitalWrite(BACKLIGHT_PIN, HIGH);
        }
        else
        {
            digitalWrite(BACKLIGHT_PIN, LOW);
        }
        break;

    case ON:
        digitalWrite(BACKLIGHT_PIN, HIGH);
        break;

    case OFF:
        digitalWrite(BACKLIGHT_PIN, LOW);
        break;
    default:
        break;
    }

    UI::poll_buttons();
    updateTime();
}

void diplay_backlight_mode()
{
    lcd.setCursor(0, 0);
    switch (BacklightMode)
    {
    case ON:
        lcd.print("  Backlight ON  ");
        break;

    case OFF:
        lcd.print("  Backlight OFF ");
        break;

    case AUTO:
        lcd.print("    Automatic   ");
        break;
    default:
        break;
    }

}

void updateTime()
{
    /* Must be called every loop */
    static unsigned long last_update = 0;

    if (!ClockRunning)
    {
        last_update = millis();
    }
    else
    {
        unsigned int delta_time = millis()-last_update;
        if (delta_time >= MILLIS_PER_SECOND)
        {
            CurrentTime.increment(delta_time/MILLIS_PER_SECOND);
            if (ShowTime)
            {
                displayTime((void*)&CurrentTime);
            }

            last_update = millis();
        }
    }
}

void pad(String& str, int len, char c)
{
    while (str.length()<len)
    {
        str = String(c) + str;
    }
}

void displayTime(void* time_vp, bool alarm_time){
    Time* time = (Time*)time_vp;

    String hour_string    = String(time->hours);
    String minute_string  = String(time->minutes);
    String second_string  = String(time->seconds);
    String timeString;

    pad(hour_string   , 2, '0');
    pad(minute_string, 2, '0');
    pad(second_string , 2, '0');

    if(alarm_time)
    {
        lcd.setCursor(11, 1);
        timeString = hour_string + String(":") + minute_string;
    }
    else
    {
        lcd.setCursor(0, 0);
        timeString = String("    ") + hour_string + String(":") + minute_string + String(":") + second_string + String("    ");
    }

    lcd.print(timeString);
}

void UI::add_button(unsigned int pin_id)
{
    Button *new_button = (Button*)malloc(sizeof(Button));
    new_button->last_changed = 0;
    new_button->pin_id = pin_id;
    new_button->next = nullptr;
    new_button->last_state = true;
    new_button->true_state = true;
    pinMode(pin_id, INPUT_PULLUP);

    if(head == nullptr){
      head = new_button;
    }
    else{
      last_node()->next = new_button;
    }
}

void UI::poll_buttons()
{
    Button *button = head;
    while (button != nullptr)
    {
        update_button(button);
        button = button->next;
    }
}

void UI::clear_flags()
{
    Button *button = head;
    while (button != nullptr)
    {
        button->been_pressed  = false;
        button->been_released = false;
        button = button->next;
    }
}

bool UI::check_for_press(unsigned int pin_id, bool clear)
{
    Button *button = head;
    while (button != nullptr)
    {
        if (button->pin_id == pin_id)
        {
            bool value = button->been_pressed;
            if (clear)
            {
                button->been_pressed=false;
            }

            return value;
        }

        button = button->next;
    }
}

bool UI::check_for_release(unsigned int pin_id, bool clear)
{
    Button *button = head;
    while (button != nullptr)
    {
        if (button->pin_id == pin_id)
        {
            bool value = button->been_released;
            if (clear)
            {
                button->been_released = false;
            }

            return value;
        }

        button = button->next;
    }
}

Button* UI::last_node()
{
    Button *node = head;
    while (node->next != nullptr)
    {
        node = node->next;
    }
    return node;
}

void UI::update_button(Button *button)
{
    bool state = digitalRead(button->pin_id);

    if (state != button->last_state)
    {
        button->last_changed = millis();
        button->last_state = state;
    }

    if ((state != button->true_state) && ((millis()-button->last_changed) > debounce_delay))
    {
        button->true_state = button->last_state;

        if (state == true)
        {
            button->been_released = true;
        }
        else
        {
            button->been_pressed = true;
        }
    }
}