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

int pressedTime;
int releasedTime;
int currentTime;
int short_press_time = 500;
int long_press_time = 5000;
bool isPressed = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buttons = lcd.readButtons();

  if (buttons & BUTTON_SELECT) {
    if (not isPressed) {
      Serial.println("Select button pressed!");
      isPressed = true;
      pressedTime = millis();
    } else if (isPressed) {
      currentTime = millis();
      if ((currentTime - pressedTime) > long_press_time) {
        Serial.println("User is holding it down!");
      }
    }
  } else {
    pressedTime = 0;
    currentTime = 0;
    isPressed = false;
  }
}
