// Boilerplate code for a new project
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

long sum(int n);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);

  
  int result = sum(10);
  Serial.println(result);
  lcd.print("Input: ");
}

void loop() {
  // put your main code here, to run repeatedly:
  String incoming = Serial.readString();
  if (incoming != "") {
    lcd.clear();
    lcd.print("Input: ");
    lcd.println(incoming);
    delay(2000);
  }

}

long sum(int n) {
  long result; 
  if (n == 0) result = 0;
  else result = n + sum(n-1);
  lcd.println(result);
  return result;
}
