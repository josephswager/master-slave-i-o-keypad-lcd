#include <Wire.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int numberOfChars = 0;

void setup()
{
  lcd.begin(16, 2);              // set up the LCD's number of columns and rows:
  Wire.begin(27);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent);  // register event
  Serial.begin(9600);            // start serial for output
}

void loop()
{
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(0 < Wire.available()) // loop through all
  {
    char c = Wire.read(); // receive byte as a character
    
    //this is just to set lcd cursor for the first time since its method doesnt work in setup()
    if(numberOfChars == 0){
       numberOfChars = 1;
       lcd.setCursor(0, 0);
    }
    
    if(c == '*'){ 
        if (numberOfChars < 17){ // if the * is pushed on row one
          numberOfChars = 17;
        } else { // if the * is pushed on row two resets screen and numberOfChars count
          lcd.clear();
          numberOfChars = 1;
        }
    }
 
    // go to second row of lcd if numberOfChars is at 17
    if(numberOfChars == 17){
      lcd.setCursor(0, 1);
    }
    // reset screen if all 32 chars are displayed or # is pushed 
    if(c == '#' || numberOfChars == 33){
      lcd.clear();
      numberOfChars = 1;
    }
    
    // print char if its not an * or # and add to char count for numberOfChars
    if(c != '*' &&  c != '#'){
      lcd.print(c);
      numberOfChars++;
    }
    
    Serial.print(c);  // print the character for daig purposes 
  }
}
