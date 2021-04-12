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

typedef struct device {
  String house_floor;
  room floor_room;
  String type;
  String device_name = "Main";
  int on_time = 0;
  int off_time = 0;
  int level = 0;
};

device homeDevices[12];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  setUpHouse();
  for (int i = 0; i < 12; i++) {
    device d = homeDevices[i];
    Serial.println(d.house_floor + "/" + d.floor_room + "/" + d.type + "/" + d.device_name);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}

void setUpHouse() {
  lcd.println("How we doin folks?");
  for (int i = 0; i < 12; i++) {
    if (i < 6) {
      homeDevices[i].house_floor = "Ground";
      homeDevices[i].floor_room = i % 3;
    } else {
      homeDevices[i].house_floor = "First";
      homeDevices[i].floor_room = (i % 3) + 3;
    }

    if (i % 2 == 0) {
        homeDevices[i].type = "light";
    } else {
        homeDevices[i].type = "heat";
    }
    
  } 
}
