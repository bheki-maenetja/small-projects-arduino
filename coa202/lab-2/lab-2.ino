#include <Wire.h>
#include <Adafruit_RGBLCDShield.h> 
#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield ();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
//  lcd.setCursor(0,0);
//  lcd.print("I am learning");
//  lcd.setCursor(0,1);
//  lcd.print("Wazzup!!!");
}

void loop() {
  // put your main code here, to run repeatedly:
//  String myString = Serial.readString();
//  lcd.setCursor(0,0);
//  lcd.print("T: " + myString);
//  lcd.setCursor(0,1);
//  lcd.print("B: " + myString);
//  delay(2000);
//  lcd.clear();
}
