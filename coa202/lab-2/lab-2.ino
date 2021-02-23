#include <Wire.h>
#include <Adafruit_RGBLCDShield.h> 
#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield ();
unsigned long myTime;

byte straightPerson1x0[] = { B00000, B01110, B01110, B00100, B11111, B00100, B01010, B10001 };
byte rightPerson1x1[] = { B00000, B01110, B01110, B00101, B01110, B10100, B01010, B10001 };
byte leftPerson1x2[] = { B00000, B01110, B01110, B10100, B01110, B00101, B01010, B10001 };
byte upPerson1x3[] = { B00000, B01110, B01110, B10101, B01110, B00100, B01010, B10001 };
byte downPerson1x4[] = { B00000, B01110, B01110, B00100, B01110, B10101, B01010, B10001 };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buttons = lcd.readButtons();

  if (buttons) {
    lcd.clear();
    lcd.setCursor(0,0);
    if (buttons & BUTTON_UP) {
      lcd.print("UP ");
      lcd.setBacklight(5);
      
      lcd.createChar(0, upPerson1x3);
      lcd.createChar(1, upPerson1x3);
      lcd.createChar(2, upPerson1x3);
      lcd.setCursor(0, 1);
      lcd.write(0);
      lcd.write(1);
      lcd.write(2);
    }
    if (buttons & BUTTON_DOWN) {
      lcd.print("DOWN ");
      lcd.setBacklight(1);

      lcd.createChar(0, downPerson1x4);
      lcd.createChar(1, downPerson1x4);
      lcd.createChar(2, downPerson1x4);
      lcd.setCursor(0, 1);
      lcd.write(0);
      lcd.write(1);
      lcd.write(2);
    }
    if (buttons & BUTTON_LEFT) {
      lcd.print("LEFT ");
      lcd.setBacklight(2);

      lcd.createChar(0, leftPerson1x2);
      lcd.createChar(1, leftPerson1x2);
      lcd.createChar(2, leftPerson1x2);
      lcd.setCursor(0, 1);
      lcd.write(0);
      lcd.write(1);
      lcd.write(2);
    }
    if (buttons & BUTTON_RIGHT) {
      lcd.print("RIGHT ");
      lcd.setBacklight(3);

      lcd.createChar(0, rightPerson1x1);
      lcd.createChar(1, rightPerson1x1);
      lcd.createChar(2, rightPerson1x1);
      lcd.setCursor(0, 1);
      lcd.write(0);
      lcd.write(1);
      lcd.write(2);
    }
    if (buttons & BUTTON_SELECT) {
      lcd.print("SELECT ");
      lcd.setBacklight(4);

      lcd.createChar(0, straightPerson1x0);
      lcd.createChar(1, straightPerson1x0);
      lcd.createChar(2, straightPerson1x0);
      lcd.setCursor(0, 1);
      lcd.write(0);
      lcd.write(1);
      lcd.write(2);
    }
  }
}
