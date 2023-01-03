#include <Adafruit_NeoPixel.h>

const int halleffect1 = 0; //hall effect sensor 1 is connected to input pin 0
const int halleffect2 = 1; //hall effect sensor 2 is connected to input pin 1
const int halleffect3 = 2; //hall effect sensor 3 is connected to input pin 2

// ledstrip has 30 leds
const int numleds = 30;

// ledstrip is connected to pin 16
const int ledstrippin = 16;

// initialize leds as object
Adafruit_NeoPixel leds = Adafruit_NeoPixel(numleds, ledstrippin);

//initialize sensor states
bool zuid = false;
bool west = false;
bool oost = false;

//initialize time
int time = 0;

int count = 0;

void setup() {
  //configure hall effect pin as input
  pinMode(halleffect1, INPUT);
  pinMode(halleffect2, INPUT);
  pinMode(halleffect3, INPUT);
  //start leds
  leds.begin();
  //start serial for debugging hall effect sensor state
  Serial.begin(115200);
  Serial.println("event_start");
}

void loop() {
  count++;
  
  //fetch hall effect sensor state
  bool oost_now = digitalRead(halleffect1)==LOW;
  bool zuid_now = digitalRead(halleffect2)==LOW;
  bool west_now = digitalRead(halleffect3)==LOW;

  if (oost_now | zuid_now | west_now) {
    //one of the sensors is currently on

    if (oost | zuid | west) {
      //one of the sensors was on last loop iteration (sensor is still on)
      return;

    } else {
      //none of the sensors was on last loop iteration (sensor just came on)
      if (zuid_now) {
        Serial.println("event_zuid");
        leds.setPixelColor(0, leds.Color(255, 0, 0));
        leds.setPixelColor(3, leds.Color(255, 0, 0));
      }
      if (oost_now) {
        Serial.println("event_oost");
        leds.setPixelColor(2, leds.Color(255, 0, 0));
      }
      if (west_now) {
        Serial.println("event_west");
        leds.setPixelColor(1, leds.Color(255, 0, 0));
      }
      leds.show();
    }

  } else {
    //none of the sensors is currently on
    if (oost | zuid | west) {
      //one of the sensors was on last loop iteration (sensor was on but is now off)

      //keep led on for a 10 seconds
      delay(10000);

      //turn off leds
      for (int i = 0; i < 4; i++) {
        leds.setPixelColor(i, leds.Color(0, 0, 0));
      }
      leds.show();

    } else {
      //none of the sensors was on last loop iteration

      time++;
      //check if time limit to heartbeat has been reached
      if (time >= 500) {
        heartbeat();
      }
    }

  }

  //store values
  oost = oost_now;
  zuid = zuid_now;
  west = west_now;

  //delay to keep counter static
  delay(10);
}

void heartbeat() {
  //reset time limit
  time = 0;

  //turn on green leds
  for (int i = 0; i < 4; i++) {
    leds.setPixelColor(i, leds.Color(0, 255, 0));
  }
  leds.show();

  //print heartbeat to serial console
  Serial.print("event_heartbeat_");
  Serial.println(count);

  //wait
  delay(100);

  //turn off green leds
  for (int i = 0; i < 4; i++) {
    leds.setPixelColor(i, leds.Color(0, 0, 0));
  }
  leds.show();
}

void testsensors() {
  Serial.print("sensor 1: ");
  Serial.println(digitalRead(halleffect1));
  Serial.print("sensor 2: ");
  Serial.println(digitalRead(halleffect2));
  Serial.print("sensor 3: ");
  Serial.println(digitalRead(halleffect3));
}
