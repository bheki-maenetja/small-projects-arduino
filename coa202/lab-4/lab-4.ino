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

//char msg[] = "locked";
char *btn_sequence[] = { "0", "0", "0" };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  change_message("locked");
}

void loop() {
  // put your main code here, to run repeatedly:
  static uint8_t old_buttons = lcd.readButtons();
  uint8_t buttons = lcd.readButtons();

  int button_changes = old_buttons & ~buttons;

  if (button_changes & BUTTON_LEFT) {
    if (btn_sequence[0] != "L") {
      btn_sequence[0] = "L";
    } else {
      reset_sequence();
    }
  }
  if (button_changes & BUTTON_RIGHT) {
    if (btn_sequence[0] == "L" && btn_sequence[1] != "R") {
      btn_sequence[1] = "R";
    } else {
      reset_sequence();
    }
  }

  if ((button_changes & BUTTON_UP) && (button_changes & BUTTON_DOWN)) {
    Serial.println("TRUE");
    if (btn_sequence[0] == "L" && btn_sequence[1] == "R" && btn_sequence[2] != "UD") {
      btn_sequence[2] = "UD";
    } else {
      reset_sequence();
    }
  }

  if (old_buttons != buttons) {
    check_sequence();
  }

  //  if (millis() % 50 == 0) {
  //    lcd.scrollDisplayLeft();
  //  }

  print_elems();
  old_buttons = buttons;
}

void print_elems() {
  for (int i = 0; i < 3; i++) {
    Serial.println(btn_sequence[i]);
  }
}

void change_message(char msg[]) {
  lcd.clear();
  lcd.print(msg);
}

void check_sequence() {
  for (int i = 0; i < 3; i++) {
    if (btn_sequence[i] == "0") {
      change_message("locked");
      return;
    }
  }
  change_message("unlocked");
}

void reset_sequence() {
  btn_sequence[0] = "0";
  btn_sequence[1] = "0";
  btn_sequence[2] = "0";
}
