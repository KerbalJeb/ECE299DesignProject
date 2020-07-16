/**
 * @file AlarmCode.ino
 * @author Ben Kellman - V00898289
 * @brief ECE299 Alarm Clock project, runs on an Arduino UNO R3.
 * @version 0.1
 * @date 2020-07-16
 *
 */

#include <LiquidCrystal.h>

#define MILLIS_PER_SECOND 100
#define SLOW_TO_FAST_INC_TIME 5000

#define INC_DELAY 500

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
enum BacklightBrightness{
    OFF = 0,
    MIN = 50,
    MED = 127,
    MAX = 255
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
    TIME_CHANGE
};

/**
 * @brief The current state of the alarm clock
 *
 */
States CurrentState = TIME_UNSET;

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
 * @brief Set the brightness of the backlight (via PWM)
 *
 * @param state The brightness of the backlight from the BacklightBrightness enum
 */
void setBacklight(BacklightBrightness state);

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
    #endif
    /* Initialize LCD */
    lcd.begin(16, 2);

    /* Initialize all used pins */
    pinMode(BACKLIGHT_PIN, OUTPUT);
    pinMode(LIGHT_SENSE  , OUTPUT);
    pinMode(BUZZER       , OUTPUT);

    setBacklight(MED);
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
    {
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

            CurrentState = TIME_CHANGE;
        }

        else if(UI::check_for_press(B_ALARM_SET)){
            UI::clear_flags();
            TimeSetTime  = &AlarmTime;
            CurrentState = ALARM_TIME_SET;
            lcd.setCursor(0, 1);
            displayTime((void*)&AlarmTime, true);
        }

        /* TODO: Add Backlight input check */
        break;

    /**
     * @brief State used to set times for both the alarm and clock time
     *
     * @details Exits when the Time inc or time dec buttons are released (so ensure they have been pressed before entering)
     */
    case TIME_CHANGE:
        if (millis()-LastIncTime >= INC_DELAY)
        {
            LastIncTime = millis();
            if ((millis()-StateChangeTime) < SLOW_TO_FAST_INC_TIME)
            {
                TimeSetTime->increment(time_inc_sign*60);
            }
            else
            {
                TimeSetTime->increment(time_inc_sign*600);
            }
            displayTime((void*)TimeSetTime, SettingAlarmTime);
        }

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

            CurrentState = TIME_CHANGE;
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
        if (UI::check_for_press(B_TIME_DEC) || UI::check_for_press(B_TIME_DEC))
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
                displayTime((void*) TimeSetTime, true);
            }
            else
            {
                lcd.setCursor(0, 1);
                lcd.print("  No Alarm Set  ");
            }

        }

        break;

    default:
        #ifdef DEBUG
            Serial.println("Error, undefined state reached");
        #endif
        break;
    }

    /*Update Logic*/
    if (ClockRunning)
    {
        updateTime();
    }

    UI::poll_buttons();
}

void updateTime()
{
    /* Must be called every loop */
    static unsigned long last_update = 0;

    unsigned int delta_time = millis()-last_update;
    if (delta_time >= MILLIS_PER_SECOND)
    {
        CurrentTime.increment(delta_time/MILLIS_PER_SECOND);
        displayTime((void*)&CurrentTime);
        last_update = millis();
    }
}

void displayTime(void* time_vp, bool alarm_time)
{
    Time* time = (Time*)time_vp;
    static char timeString[16];
    if(alarm_time)
    {
        lcd.setCursor(0, 1);
        sprintf(timeString, "Alarm At: %02d:%02d", time->hours, time->minutes);
    }
    else
    {
        lcd.setCursor(0, 0);
        sprintf(timeString, "    %02d:%02d:%02d    ", time->hours, time->minutes, time->seconds);
    }
    lcd.print(timeString);
}

void setBacklight(BacklightBrightness state)
{
    analogWrite(BACKLIGHT_PIN, state);
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
                button->been_pressed = false;
            }

            return value;
        }

        button = button->next;
    }
    #ifdef DEBUG
        Serial.println("pin not found");
    #endif
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