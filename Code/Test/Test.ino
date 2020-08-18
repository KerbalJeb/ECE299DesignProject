#include <LiquidCrystal.h>

/**
 * @brief Used for enabling debug printing, breaks simulator
 *
 */
// #define DEBUG

#define B_TIME_INC 6
#define B_TIME_DEC 7
#define B_SNOOZE A2
#define B_CANCEL A1
#define B_BACKLIGHT A3
#define B_ALARM_SET A4

#define BACKLIGHT_PIN 10
#define LIGHT_SENSE A0
#define BUZZER 9

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

unsigned long last_blink = 0;
bool state = false;

void setup()
{
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.print("Hello World");
    pinMode(BACKLIGHT_PIN, OUTPUT);
    pinMode(LIGHT_SENSE, INPUT);
    pinMode(BUZZER, OUTPUT);

    pinMode(B_TIME_INC, INPUT_PULLUP);
    pinMode(B_TIME_DEC, INPUT_PULLUP);
    pinMode(B_SNOOZE, INPUT_PULLUP);
    pinMode(B_CANCEL, INPUT_PULLUP);
    pinMode(B_BACKLIGHT, INPUT_PULLUP);
    pinMode(B_ALARM_SET, INPUT_PULLUP);
    delay(1000);
    lcd.setCursor(0, 1);
}

void loop()
{
    if (millis() - last_blink > 1000)
    {
        if (state)
        {
            noTone(BUZZER);
            digitalWrite(BACKLIGHT_PIN, LOW);
        }
        else
        {
            tone(BUZZER, 1000);
            digitalWrite(BACKLIGHT_PIN, HIGH);
        }
        last_blink = millis();
        state = !state;
    }

    if (!digitalRead(B_TIME_INC))
    {
        Serial.println("T+");
    }

    if (!digitalRead(B_TIME_DEC))
    {
        Serial.println("T-");
    }

    if (!digitalRead(B_ALARM_SET))
    {
        Serial.println("AlarmSet");
    }

    if (!digitalRead(B_BACKLIGHT))
    {
        Serial.println("Backlight");
    }

    if (!digitalRead(B_SNOOZE))
    {
        Serial.println("Snooze");
    }

    if (!digitalRead(B_CANCEL))
    {
        Serial.println("Cancel");
    }
    lcd.setCursor(0, 1);
    lcd.print(String(analogRead(LIGHT_SENSE)) + String("   "));
    delay(10);
}