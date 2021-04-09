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

typedef struct action {
  String action_name;
  int level;
  String on_time;
  String off_time;
};

typedef struct type {
  String typeName;
  action actions[2];
};

typedef struct room {
  String room_name;
  type types[2]; 
};

typedef struct house_floor {
  String floor_name;
  room rooms[3];
};

typedef struct house {
  house_floor floors[2];
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  house myHouse;
  setUpHouse(&myHouse);
  Serial.println(myHouse.floors[0].floor_name);
  Serial.println(myHouse.floors[1].floor_name);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void setUpHouse(house *houseObj) {
  (*houseObj).floors[0].floor_name = "Ground";
  (*houseObj).floors[1].floor_name = "First";
  (*houseObj).floors[0].rooms[0].room_name = "kitchen";
  (*houseObj).floors[0].rooms[1].typeName = "Heat";
  (*houseObj).floors[0].rooms[1].room_name = "hall";
  (*houseObj).floors[0].rooms[2].room_name = "living room"; 
}
