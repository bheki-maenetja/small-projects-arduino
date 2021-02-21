#include <Wire.h>
#include <Adafruit_RGBLCDShield.h> 
#include <utility/Adafruit_MCP23017.h>
#include <string.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield ();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(1,0);
  lcd.print("Hello Worlds!");
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t demButtons = lcd.readButtons();

  if (demButtons & BUTTON_LEFT) {
    lcd.scrollDisplayLeft();
  } else if (demButtons & BUTTON_RIGHT) {
    lcd.scrollDisplayRight();
  }
  delay(100);
}
