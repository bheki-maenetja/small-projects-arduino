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
  First = 1,
  Data = 2
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
  heat = 1,
  lamp = 2 
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
  int on_time = 720;
  int off_time = 720;
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
  int num_floors = 3;
  room current_room = 0;
  int num_rooms = 6;
  device_type current_device = 0;
  int num_devices = 3;
  action current_action = 0;
  int num_actions = 3;
};

menu_state menu_level;
menu_selection menu_choice;

device homeDevices[18];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  setUpHouse();
  delay(100);
  Serial.println("BASIC");
  menu_level = 0;
  getMenuState(menu_level);
  Serial.setTimeout(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonHandler();
  if (Serial.readString() == "Q") {
    sendAllData();
  }
}

void setUpHouse() {
  for (int i = 0; i < 18; i++) {
    if (i < 9) {
      homeDevices[i].house_floor = Ground;
      homeDevices[i].floor_room = i % 3;
    } else {
      homeDevices[i].house_floor = First;
      homeDevices[i].floor_room = (i % 3) + 3;
    }

    if (i % 9 > 5) {
      homeDevices[i].type = 2;
    } else if (i % 9 < 3) {
      homeDevices[i].type = 0;
    } else {
      homeDevices[i].type = 1;
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
    case Data:
      return "Export";
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
    case lamp:
      return "Lamp";
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
      lcd.print(getActionName(menu_choice.current_action) + ": ");
      switch(menu_choice.current_action) {
        case on_time:
          lcd.print(calculateTime((*getCurrentDevice()).on_time));
          break;
        case off_time:
          lcd.print(calculateTime((*getCurrentDevice()).off_time));
          break;
        case level:
          lcd.print((*getCurrentDevice()).level);
          break;
        default:
          break;
      }
    default:
      break;
  }
}

String getDeviceName(device_type device) {
  switch (device) {
    case lamp:
      return "Table";
      break;
    default:
      return "Main";
      break;
  }
}

void printDeviceInfo(device *home_device) {
  Serial.println(
    getFloorName((*home_device).house_floor) + "/" 
    + getRoomName((*home_device).floor_room) + "/" 
    + getTypeName((*home_device).type) + "/" 
    + getDeviceName((*home_device).type) + "/"
    + "On: " + calculateTime((*home_device).on_time) 
  );
  Serial.println(
    getFloorName((*home_device).house_floor) + "/" 
    + getRoomName((*home_device).floor_room) + "/" 
    + getTypeName((*home_device).type) + "/" 
    + getDeviceName((*home_device).type) + "/"
    + "Off: " + calculateTime((*home_device).off_time) 
  );
  Serial.println(
    getFloorName((*home_device).house_floor) + "/" 
    + getRoomName((*home_device).floor_room) + "/" 
    + getTypeName((*home_device).type) + "/" 
    + getDeviceName((*home_device).type) + "/"
    + "Level: " + (*home_device).level 
  );
}

void sendAllData() {
  for (int i = 0; i < 18; i++) {
    printDeviceInfo(&homeDevices[i]);
  }
}

device* getCurrentDevice() {
  for (int i = 0; i < 18; i++) {
    bool deviceFound = homeDevices[i].house_floor == menu_choice.current_floor 
                       && homeDevices[i].floor_room == menu_choice.current_room
                       && homeDevices[i].type == menu_choice.current_device;
    if (deviceFound) {
       return &homeDevices[i];  
    }
  }
  Serial.println("Not found");
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
        adjustMenuChoice(1);
      } else if (buttons & BUTTON_LEFT) {
        adjustMenuLevel(false);
      } else if (buttons & BUTTON_RIGHT) {
        adjustMenuLevel(true);
      } else if (buttons & BUTTON_DOWN) {
        adjustMenuChoice(-1);
      } else if (buttons & BUTTON_SELECT) {
        printDeviceInfo(getCurrentDevice());
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
  if (menu_choice.current_floor == Data) {
    sendAllData();
    return;
  }
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
    case values:
      adjustDeviceValue(increment);
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

void adjustDeviceValue(int increment) {
  device *current_device = getCurrentDevice();
  switch(menu_choice.current_action) {
    case on_time:
      (*current_device).on_time = (*current_device).on_time + 5 * increment;
      if ((*current_device).on_time < 0) {
        (*current_device).on_time = 1435;
      } else if ((*current_device).on_time > 1435) {
        (*current_device).on_time = 0;
      }
      break;
    case off_time:
      (*current_device).off_time = (*current_device).off_time + 5 * increment;
      if ((*current_device).off_time < 0) {
        (*current_device).off_time = 1435;
      } else if ((*current_device).off_time > 1435) {
        (*current_device).off_time = 0;
      }
      break;
    case level:
      (*current_device).level = (*current_device).level + increment;
      if ((*current_device).level < 0) {
        (*current_device).level = 100;
      } else if ((*current_device).level > 100) {
        (*current_device).level = 0;
      }
    default:
      break;
  }
}

String calculateTime(int minutes) {
  int hour_value = floor(minutes / 60);
  int minute_value = minutes - hour_value * 60;
  if (hour_value < 10) {
    if (minute_value < 10) {
      return "0" + (String) hour_value + ":" + "0" + (String) minute_value;
    } else {
      return "0" + (String) hour_value + ":" + (String) minute_value;
    }
  } else if (minute_value < 10) {
      return (String) hour_value + ":" + "0" + (String) minute_value;
  } else {
      return (String) hour_value + ":" + (String) minute_value;
  }
}
