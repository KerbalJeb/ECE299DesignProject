/*
ECE299 Lab3
*/

#define BUTTON_PIN 2
/*How long to wait between regestring inputs in ms*/
#define DEBOUNCE_DELAY 5
// #define DEBUG

/* 
The GPIO pins connected to the 7 segment dispaly in order
from sement A-G
*/
int segment_pins[] = {6,7,8,9,10,11, 12}

/*
Maps integer values to a byte than encodes what segments 
to light up in order ABCDEFG (ie. bit 1 is A, bit 2 is B, ect.)
*/
char num_to_7seg[] {0x7E,
                    0x30,
                    0x6D,
                    0x79,
                    0x33,
                    0x5B,
                    0x5F,
                    0x70,
                    0x7F,
                    0x7B};


void display_number(unsigned int num);
void button_press_isr();
bool check_bit(unsigned int data, unsigned int idx);

void setup()
{
    /*Print debug messages over serial if #define DEBUG is present*/
    #ifdef DEBUG
        Serial.begin(9600);
    #endif

    /*Pins should be configured as output automaticaly, but we will do it explicitly*/
    for (int i=0; i<7; i++){
        pinMode(segment_pins[i], OUTPUT);
    }   
    /*Internal pullup used to simply physical circuit*/
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    /*Since dispaly_number is only called in the button press isr, 
    we will initialize it to zero so the display is initial on*/
    display_number(0);
    /*Configure the isr to trigger on the falling edge because negative logic is used (ie. HIGH is the unpressed state)*/
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), button_press_isr, FALLING);
}

void loop()
{

}

void display_number(unsigned int num){
    /*Validate input data*/
    if (num > 9)
    {
        /*Error Contion, Number must be less than 9*/
        #ifdef DEBUG
            Serial.print("Error: display_number was passed a value greater than 9 (");
            Serial.print(num);
            Serial.println(")");
        #endif

        /*Return so we don't end up reading junk from the ram when we read outside of the array bounds*/
        return;
    }
    /*Update the 7 segment display output*/
    for (unsigned int i=0; i<7; i++){
        bool segment_is_on = check_bit(num_to_7seg[num], i);
        digitalWrite(segment_pins[i], segment_is_on);
    }
}

/*Returns true if the i^th bit is 1, false otherwise*/
bool check_bit(char data, unsigned int i){
    /*Some bitwise ops to check if the ith bit in a byte is 0 or 1*/
    return (bool)(data&(0x01<<i));
}

void button_press_isr(){
    /*Keeps track of the last time the ISR ran to debounce the button*/
    static unsigned long last_press;
    /*Counter is static so it is shared by all functions calls (persits after function returns)*/
    static char counter = 0;
    /*
    Make sure we are not triggering of off the button bounceing by making sure the last time the 
    isr ran was longer than the DEBOUNCE_DELAY
    */
   unsigned long delta_time = millis()-last_press;
    if(delta_time>DEBOUNCE_DELAY){
        /*Count in mod 10, ie. 0-9 cyclic*/
        counter+=1;
        counter%=10;
        display_number(counter);
        last_press=millis();
    }

    #ifdef DEBUG
        Serial.print("Debug: Button Press Rising Edge Detected, time since last press is: ");
        Serial.print(delta_time);
        Serial.println("ms");
    #endif
}