#include <Wire.h>
/*
    A key mapping. Index 0 and one are spaces (placeholders). 
    Pin 2 maps to the '*' key; pin 3 maps to the '7' key and so on.
*/
char keys[13] = "*7410852#963";


void setup()
{
    Wire.begin(); // join i2c bus (address optional for master)
    Serial.begin(9600);
}

void loop()
{
    char key = getKey();        // get the current key (may be void)
    if (key) {
        Serial.println(key);    // debug
        transmit(key);          // send the key
    }
}

char getKey()
{
    char key;
    int i;
    for (i = 2; i <= 13; i++)    // loop through the input pins
    {
        if (digitalRead(i)) {    // if a pin reads HIGH
            key = keys[i - 2];   // map to corresponding char
            delay(250);          // delay to avoid picking up the key several times per press
            break;               // don't care about any other key, first one found is sent out
        }
    }
    return key;        
}

void transmit(char key)
{
    Wire.beginTransmission(27);// transmit to device #27  
    Wire.write(key);           // send the key
    Wire.endTransmission();    // stop transmitting

}
