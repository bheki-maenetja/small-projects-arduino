#include <Wire.h>
#include <Adafruit_RGBLCDShield.h> 
#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield ();

void setup() {
  // put your setup code here, to run once:
  lcd.begin(200, 200);
  lcd.setCursor(0, 0);
  lcd.print("Hello ,World!");
  lcd.setCursor(0, 1);
  lcd.print("Hi there!");

  for (int i = 0; i < 8; i++) {
    lcd.setBacklight(i);
    delay(500);
  }
}

void printVars(int x, int y) {
  Serial.println(x);
  Serial.println(y);
}

void loop() {
  // put your main code here, to run repeatedly:
}
