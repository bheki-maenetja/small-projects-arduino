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

typedef enum house_floor { 
  Ground = 0, 
  First = 1
};

typedef enum room { 
  kitchen = 0, 
  living_room = 1,
  hall = 2,
  bathroom = 3,
  bedroom_1 = 4,
  bedroom_2 = 5 
};

typedef enum device_type { 
  light = 0, 
  heat = 1 
};

typedef enum action {
  on_time = 0,
  off_time = 1,
  level = 2
};

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
  actions = 3,
  values = 4
};

typedef struct menu_selection {
  house_floor current_floor = 0;
  int num_floors = 2;
  room current_room = 0;
  int num_rooms = 6;
  device_type current_device = 0;
  int num_devices = 2;
  action current_action = 0;
  int num_actions = 3;
};

menu_state menu_level;
menu_selection menu_choice;

device homeDevices[12];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  setUpHouse();
  delay(100);
  menu_level = 0;
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

String getActionName(action action) {
  switch(action) {
    case on_time:
      return "On time";
      break;
    case off_time:
      return "Off time";
      break;
    case level:
      return "Level";
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
      lcd.print("Floor: " + getFloorName(menu_choice.current_floor));
      break;
    case rooms:
      lcd.print("Room: " + getRoomName(menu_choice.current_room));
      break;
    case devices:
      lcd.print("Device: " + getTypeName(menu_choice.current_device));
      break;
    case actions:
      lcd.print("Action: " + getActionName(menu_choice.current_action));
      break;
    case values:
      lcd.print(getActionName(menu_choice.current_action) + ": " + "0");
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
      + getDeviceName() + "/"
      + "On: " + homeDevices[i].on_time 
    );
    Serial.println(
      getFloorName(homeDevices[i].house_floor) + "/" 
      + getRoomName(homeDevices[i].floor_room) + "/" 
      + getTypeName(homeDevices[i].type) + "/" 
      + getDeviceName() + "/"
      + "Off: " + homeDevices[i].off_time 
    );
    Serial.println(
      getFloorName(homeDevices[i].house_floor) + "/" 
      + getRoomName(homeDevices[i].floor_room) + "/" 
      + getTypeName(homeDevices[i].type) + "/" 
      + getDeviceName() + "/"
      + "Level: " + homeDevices[i].level 
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
        adjustMenuChoice(1);
      } else if (buttons & BUTTON_LEFT) {
        Serial.println("Left");
        adjustMenuLevel(false);
      } else if (buttons & BUTTON_RIGHT) {
        Serial.println("Right");
        adjustMenuLevel(true);
      } else if (buttons & BUTTON_DOWN) {
        Serial.println("Down");
        adjustMenuChoice(-1);
      } else if (buttons & BUTTON_SELECT) {
        sendToMonitor();
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
  if (increment and menu_level != 4) {
    menu_level = menu_level + 1;
  } else if (!increment and menu_level != 0) {
    menu_level = menu_level - 1;
  }
  getMenuState(menu_level);
}

void adjustMenuChoice(int increment) {
  switch(menu_level) {
    case floors:
      adjustFloor(increment);
      break;
    case rooms:
      adjustRoom(increment);
      break;
    case devices:
      menu_choice.current_device = menu_choice.current_device + increment;
      if (menu_choice.current_device < 0) {
        menu_choice.current_device = menu_choice.num_devices - 1;
      } else if (menu_choice.current_device >= menu_choice.num_devices) {
        menu_choice.current_device = 0;
      }
      break;
    case actions:
      menu_choice.current_action = menu_choice.current_action + increment;
      if (menu_choice.current_action < 0) {
        menu_choice.current_action = menu_choice.num_actions - 1;
      } else if (menu_choice.current_action >= menu_choice.num_actions) {
        menu_choice.current_action = 0;
      }
      break;
    default:
      break;
  }
  getMenuState(menu_level);
}

void adjustFloor(int increment) {
  menu_choice.current_floor = menu_choice.current_floor + increment;
  if (menu_choice.current_floor < 0) {
    menu_choice.current_floor = menu_choice.num_floors - 1;
  } else if (menu_choice.current_floor >= menu_choice.num_floors) {
    menu_choice.current_floor = 0;
  }

  if (menu_choice.current_floor == 0) {
    menu_choice.current_room = 0;
  } else if (menu_choice.current_floor == 1) {
    menu_choice.current_room = 3;
  }
}

void adjustRoom(int increment) {
  menu_choice.current_room = menu_choice.current_room + increment;
  int min_value, max_value;
  if (menu_choice.current_floor == 0) {
    min_value = 0;
    max_value = 2;
  } else if (menu_choice.current_floor == 1) {
    min_value = 3;
    max_value = 5; 
  }

  if (menu_choice.current_room < min_value) {
    menu_choice.current_room = max_value;
  } else if (menu_choice.current_room > max_value) {
    menu_choice.current_room = min_value;
  }
}
