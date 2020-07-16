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

#define nullptr NULL
#define ALARM_ENABLED_MSG  "Alarm Enabled   "
#define ALARM_DISABLED_MSG "Alarm Disabled  "


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

class UI
{
public:
    static const unsigned long debounce_delay = 50;

    void static add_button(unsigned int);

    void static poll_buttons();

    void static clear_flags();

    bool static check_for_press(unsigned int pin_id, bool clear=true);

    bool static check_for_release(unsigned int pin_id, bool clear=true);

private:
    static Button *head;

    static Button* last_node();

    void static update_button(Button *);
};

Button* UI::head = nullptr;

struct Time
{
    int hours;
    int minutes;
    int seconds ;

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

enum BacklightBrightness{
    OFF = 0,
    MIN = 50,
    MED = 127,
    MAX = 255
};

enum States{
    TIME_UNSET,
    ALARM_TIME_SET,
    ALARM_SET,
    CLOCK,
    ALARM_TRIGGERED,
    SNOOZEING,
    TIME_CHANGE
};

States CurrentState = TIME_UNSET;
unsigned long StateChangeTime;
unsigned long LastIncTime;
char time_inc_sign;
bool SettingAlarmTime = false;

void updateTime();
/* Tinker cad doesn't allow custom types as function parmeters */
void displayTime(void*, bool=false);
void setBacklight(BacklightBrightness state);

Time CurrentTime;
Time AlarmTime;
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

    pinMode(B_TIME_INC , INPUT_PULLUP);
    pinMode(B_TIME_DEC , INPUT_PULLUP);
    pinMode(B_SNOOZE   , INPUT_PULLUP);
    pinMode(B_CANCEL   , INPUT_PULLUP);
    pinMode(B_BACKLIGHT, INPUT_PULLUP);
    pinMode(B_ALARM_SET, INPUT_PULLUP);


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
    /* FSM Logic*/
    switch (CurrentState)
    {
    case TIME_UNSET:
        /* Inital State */

        if (UI::check_for_press(B_TIME_INC, false) || UI::check_for_press(B_TIME_DEC, false))
        {
            TimeSetTime  = &CurrentTime;
            CurrentState = CLOCK;

            CurrentTime.hours   = 0;
            CurrentTime.minutes = 0;
            CurrentTime.seconds = 0;
        }

        break;

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

        break;

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
    //Serial.println("pin not found");
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