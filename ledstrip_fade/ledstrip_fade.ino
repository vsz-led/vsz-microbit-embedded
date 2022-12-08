#include <Adafruit_NeoPixel.h>

// ledstrip has 30 leds
const int numleds = 30;

// ledstrip is connected to pin 16
const int ledstrippin = 16;

// initialize led strip as object
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numleds, ledstrippin);

void setup() {
  // start led strip
  strip.begin();
}

void loop() {
  for (int led = 0; led < numleds; led++) {
    for (int i = 0; i < 255; i++) {
      strip.setPixelColor(led, strip.Color(i, 0, 0));
      strip.show();
    }
  }
  for (int led = 0; led < numleds; led++) {
    for (int i = 0; i <= 255; i++) {
      strip.setPixelColor(led, strip.Color(255-i, i, 0));
      strip.show();
    }
  }
  for (int led = 0; led < numleds; led++) {
    for (int i = 0; i <= 255; i++) {
      strip.setPixelColor(led, strip.Color(0, 255-i, i));
      strip.show();
    }
  }
  for (int led = 0; led < numleds; led++) {
    for (int i = 0; i <= 255; i++) {
      strip.setPixelColor(led, strip.Color(0, 0, 255-i));
      strip.show();
    }
  }
}