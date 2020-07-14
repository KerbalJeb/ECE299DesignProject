#include <LiquidCrystal.h>

#define TIME_SCALE_FACTOR 10
#define BACKLIGHT_PIN 10

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
char timeString[9];
bool clockRunning = false;

enum BacklightBrightness{
    OFF = 0,
    MIN = 50,
    MED = 127,
    MAX = 255
};

void updateTime();
void displayTime(unsigned char, unsigned char, unsigned char);
void setBacklight(BacklightBrightness state);

void setup()
{
    /*Print debug messages over serial if #define DEBUG is present*/
    #ifdef DEBUG
        Serial.begin(9600);
    #endif
    lcd.begin(16, 2);

    pinMode(BACKLIGHT_PIN, OUTPUT);
    setBacklight(MED);
    lcd.setCursor(0, 0);
    lcd.print("  Time Not Set  ");
}

void loop()
{
    if (clockRunning)
    {
        updateTime();
    }
}

void updateTime()
{
    /* Must be called every loop */
    static unsigned long last_update = 0;
    static unsigned char hours        = 0;
    static unsigned char minutes      = 0;
    static unsigned char seconds     = 0;

    unsigned int delta_time = millis()-last_update;
    if (delta_time >= (1000/TIME_SCALE_FACTOR))
    {
        last_update = millis();
        seconds += 1;
        if (seconds >= 60)
        {
            minutes += 1;
            if (minutes >= 60)
            {
                hours += 1;
            }

        }
        seconds %= 60;
        minutes  %= 60;
        hours    &= 24;
        displayTime(hours, minutes, seconds);
    }
}

void displayTime(unsigned char hours, unsigned char minutes, unsigned char seconds){
    sprintf(timeString, "    %02d:%02d:%02d", hours, minutes, seconds);
    lcd.setCursor(0, 0);
    lcd.print(timeString);
}

void setBacklight(BacklightBrightness state){
    analogWrite(BACKLIGHT_PIN, state);
}