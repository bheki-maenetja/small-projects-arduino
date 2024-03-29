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

byte straightPerson1x0[] = { B00000, B01110, B01110, B00100, B11111, B00100, B01010, B10001 };
byte rightPerson1x1[] = { B00000, B01110, B01110, B00101, B01110, B10100, B01010, B10001 };
byte leftPerson1x2[] = { B00000, B01110, B01110, B10100, B01110, B00101, B01010, B10001 };
byte upPerson1x3[] = { B00000, B01110, B01110, B10101, B01110, B00100, B01010, B10001 };
byte downPerson1x4[] = { B00000, B01110, B01110, B00100, B01110, B10101, B01010, B10001 };

void setup() {
    Serial.begin(9600);
    lcd.begin(16,2);
}

void loop() {
  uint8_t buttons = lcd.readButtons();
  byte chosenPerson[8];  

  if (buttons) {
    lcd.clear();
    lcd.setCursor(0,0);
    if (buttons & BUTTON_UP) {
      lcd.print("UP ");
      lcd.setBacklight(YELLOW);
      memmove(chosenPerson, upPerson1x3, 8);
    }
    if (buttons & BUTTON_DOWN) {
      lcd.print("DOWN ");
      lcd.setBacklight(RED);
      memmove(chosenPerson, downPerson1x4, 8);
    }
    if (buttons & BUTTON_LEFT) {
      lcd.print("LEFT ");
      lcd.setBacklight(TEAL);
      memmove(chosenPerson, leftPerson1x2, 8);
    }
    if (buttons & BUTTON_RIGHT) {
      lcd.print("RIGHT ");
      lcd.setBacklight(GREEN);
      memmove(chosenPerson, rightPerson1x1, 8);
    }
    if (buttons & BUTTON_SELECT) {
      lcd.print("SELECT ");
      lcd.setBacklight(VIOLET);
      memmove(chosenPerson, straightPerson1x0, 8);
    }
    lcd.createChar(0, chosenPerson);
    lcd.createChar(1, chosenPerson);
    lcd.createChar(2, chosenPerson);
    lcd.setCursor(0, 1);
    lcd.write(0);
    lcd.write(1);
    lcd.write(2);
  }
}
