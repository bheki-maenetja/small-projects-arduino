#include <Wire.h>
#include <Adafruit_RGBLCDShield.h> 
#include <utility/Adafruit_MCP23017.h>
#include <string.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield ();

#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

int count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(count);
}

void loop() {
  // put your main code here, to run repeatedly:
   uint8_t buttons = lcd.readButtons();
   if (buttons) {
      lcd.clear();
      if ((buttons & BUTTON_UP) && count < 50) {
        count++;
      } else if ((buttons & BUTTON_DOWN) && count > -50) {
        count--;
      } else if (buttons & BUTTON_SELECT) {
        Serial.println(count);
      }
      lcd.print(count);
      delay(250);
   }
}
