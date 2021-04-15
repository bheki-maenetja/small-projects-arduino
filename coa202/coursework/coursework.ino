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

typedef enum room { 
  kitchen = 0, 
  living_room = 1,
  hall = 2,
  bathroom = 3,
  bedroom_1 = 4,
  bedroom_2 = 5 
};

typedef enum house_floor { Ground, First };

typedef enum device_type { light, heat };

typedef struct device {
  house_floor house_floor;
  room floor_room;
  device_type type;
  int on_time = 0;
  int off_time = 0;
  int level = 0;
};

typedef enum menu_state {
  floors = 0,
  rooms = 1,
  devices = 2,
  actions = 3
};

menu_state menu_level;

int level_index = 0;

device homeDevices[12];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  setUpHouse();
  delay(100);
  menu_level = level_index;
  getMenuState(menu_level);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonHandler();
}

void setUpHouse() {
  for (int i = 0; i < 12; i++) {
    if (i < 6) {
      homeDevices[i].house_floor = Ground;
      homeDevices[i].floor_room = i % 3;
    } else {
      homeDevices[i].house_floor = First;
      homeDevices[i].floor_room = (i % 3) + 3;
    }

    if (i % 2 == 0) {
        homeDevices[i].type = light;
    } else {
        homeDevices[i].type = heat;
    }
  } 
}

String getFloorName(house_floor floor) {
  switch (floor) {
    case Ground:
      return "Ground";
      break;
    case First:
      return "First";
      break;
    default:
      return "";
      break;
  }
}

String getTypeName(device_type device) {
  switch (device) {
    case light:
      return "Light";
      break;
    case heat:
      return "Heat";
      break;
    default:
      return "";
      break;
  }
}

String getRoomName(room room) {
  switch (room) {
    case kitchen:
      return "kitchen";
      break;
    case living_room:
      return "living room";
      break;
    case hall:
      return "hall";
      break;
    case bathroom:
      return "bathroom";
      break;
    case bedroom_1:
      return "bedroom 1";
      break;
    case bedroom_2:
      return "bedroom 2";
      break;
    default:
      return "";
      break;
  }
}

void getMenuState(menu_state state) {
  lcd.clear();
  Serial.println(state);
  switch(state) {
    case floors:
      lcd.print("State: Floors");
      break;
    case rooms:
      lcd.print("State: Rooms");
      break;
    case devices:
      lcd.print("State: Devices");
      break;
    case actions:
      lcd.print("State: Actions");
      break;
    default:
      break;
  }
}

String getDeviceName() {
  return "Main";
}

void sendToMonitor() {
  for (int i = 0; i < 12; i++) {
    Serial.println(
      getFloorName(homeDevices[i].house_floor) + "/" 
      + getRoomName(homeDevices[i].floor_room) + "/" 
      + getTypeName(homeDevices[i].type) + "/" 
      + getDeviceName()
    );
    delay(500);
  }
}


void buttonHandler() {
  static int pressedTime;
  static int currentTime;
  static uint8_t old_buttons = lcd.readButtons();
  static bool isPressed = false;
  uint8_t buttons = lcd.readButtons();

  if (buttons) {
    if (not isPressed) {
      pressedTime = millis();
      isPressed = true;
      if (buttons & BUTTON_UP) {
        Serial.println("Up");
      } else if (buttons & BUTTON_LEFT) {
        Serial.println("Left");
        adjustMenuLevel(false);
      } else if (buttons & BUTTON_RIGHT) {
        Serial.println("Right");
        adjustMenuLevel(true);
      } else if (buttons & BUTTON_DOWN) {
        Serial.println("Down");
      }
    } else if (isPressed) {
      currentTime = millis();
      if ((currentTime - pressedTime) > 2000) {
        Serial.println("Holding");
      }
    }
  } else {
    pressedTime = 0;
    currentTime = 0;
    isPressed = false;
  }
}

void adjustMenuLevel(bool increment) {
  if (increment and menu_level != 3) {
    menu_level = menu_level + 1;
  } else if (!increment and menu_level != 0) {
    menu_level = menu_level - 1;
  }
  getMenuState(menu_level);
}
