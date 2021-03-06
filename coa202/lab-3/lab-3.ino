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
int count_2 = 0;
int tick_speed = 250;

bool isPressed;
int currentTime = 0;
int pressedTime = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(count);
}

void loop() {
  // put your main code here, to run repeatedly:
//  standard_increment();
  speedup_increment();
}

void standard_increment() {
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

void speedup_increment() {
  uint8_t buttons = lcd.readButtons();

  if ((buttons & BUTTON_UP) || (buttons & BUTTON_DOWN)) {
    lcd.clear();
    if (not isPressed) {
      pressedTime = millis();
      isPressed = true;
      Serial.println("Pressed");
    } else if (isPressed) {
      currentTime = millis();
      if ((currentTime - pressedTime) > 3000) {
        Serial.println("Holding");
        tick_speed = 100;
      }
    }

    if (buttons & BUTTON_UP) {
      count_2++;
    } else if (buttons & BUTTON_DOWN) {
      count_2--;
    }
    lcd.print(count_2);
    delay(tick_speed);
  } else {
    currentTime = 0;
    pressedTime = 0;
    isPressed = false;
    tick_speed = 250;
  }
}
