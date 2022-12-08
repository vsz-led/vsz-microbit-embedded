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
  Serial.println("vsz_led-start");
}

void loop() {
  count++;
  //turn off green led if it was on
  for (int i = 0; i < 4; i++) {
    leds.setPixelColor(i, leds.Color(0, 0, 0));
  }
  leds.show();
  
  //fetch hall effect sensor state
  oost = digitalRead(halleffect1)==LOW;
  zuid = digitalRead(halleffect2)==LOW;
  west = digitalRead(halleffect3)==LOW;


  if (oost | zuid | west) {
    //input detected
    if (zuid) {
      Serial.println("zuid");
      leds.setPixelColor(0, leds.Color(255, 0, 0));
      leds.setPixelColor(3, leds.Color(255, 0, 0));
      leds.show();
    }
    if (oost) {
      Serial.println("oost");
      leds.setPixelColor(2, leds.Color(255, 0, 0));
      leds.show();
    }
    if (west) {
      Serial.println("west");
      leds.setPixelColor(1, leds.Color(255, 0, 0));
      leds.show();
    }
  } else {
    //input not detected, red led can turn off and time can increase for idle led
    leds.setPixelColor(1, leds.Color(0, 0, 0));
    leds.setPixelColor(2, leds.Color(0, 0, 0));
    leds.setPixelColor(3, leds.Color(0, 0, 0));
    leds.setPixelColor(4, leds.Color(0, 0, 0));
    leds.show();
    time++;
    
    //check if time limit to blink has been reached
    if (time >= 500) {
      //reset time limit
      time = 0;
      //turn on green led
      for (int i = 0; i < 4; i++) {
        leds.setPixelColor(i, leds.Color(0, 255, 0));
      }
      leds.show();

      Serial.print("vsz_led-heartbeat ");
      Serial.println(count);

      //wait
      delay(100);
    }
  }

  //delay to keep counter static
  delay(10);
}

void testsensors() {
  Serial.print("sensor 1: ");
  Serial.println(digitalRead(halleffect1));
  Serial.print("sensor 2: ");
  Serial.println(digitalRead(halleffect2));
  Serial.print("sensor 3: ");
  Serial.println(digitalRead(halleffect3));
}
