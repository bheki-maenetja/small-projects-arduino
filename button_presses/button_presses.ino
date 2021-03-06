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

char * message = malloc(50);

enum button_state {pressed = 'p', holding = 'h', idle = 'i'};
button_state current_state;
button_state old_state;

int pressedTime;
int currentTime;
int press_time = 2000;
bool isPressed = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  current_state = idle;
  strcpy(message, "Idle");
  lcd.print(message);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buttons = lcd.readButtons();

  if (buttons & BUTTON_SELECT) {
    old_state = current_state;
    if (not isPressed) {
      pressedTime = millis();
      strcpy(message, "Pressed");
      isPressed = true;
      current_state = pressed;
    } else if (isPressed) {
      currentTime = millis();
      if ((currentTime - pressedTime) > press_time) {
        strcpy(message, "Holding");
        current_state = holding;
      }
    }
  } else {
    pressedTime = 0;
    currentTime = 0;
    isPressed = false;
    strcpy(message, "Idle");
    old_state = current_state;
    current_state = idle;
  }

  Serial.println(char(current_state));
  if (current_state != old_state) {
    lcd.clear();
    lcd.print(message); 
  }
}
