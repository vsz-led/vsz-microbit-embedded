#include <Adafruit_NeoPixel.h>

// ledstrip has 30 leds
const int numleds = 30;

// ledstrip is connected to pin 16
const int ledstrippin = 16;

// initialize led strip as object
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numleds, ledstrippin);

// configure colors
uint32_t red = strip.Color(0xFF, 0x00, 0x00);
uint32_t green = strip.Color(0x00, 0xFF, 0x00);
uint32_t blue = strip.Color(0x00, 0x00, 0xFF);
uint32_t white = strip.Color(0xFF, 0xFF, 0xFF);
uint32_t off = strip.Color(0x00, 0x00, 0x00);

void setup() {
  // start led strip
  strip.begin();
}

void loop() {
  // use for loop to go over every led
  for (int i = 0; i < numleds; i++) {
    // set led color to red
    led_red(i);

    // wait
    delay(500);

    // set led color to green
    led_green(i);

    // wait
    delay(500);

    // set led color to blue
    led_blue(i);

    // wait
    delay(500);

    // turn led off
    led_off(i);

    // wait
    delay(500);
  }
}

void led_red(int led) {
  // set led color to red
  strip.setPixelColor(led, red);
  // show change on ledstrip
  strip.show();
}

void led_green(int led) {
  // set led color to green
  strip.setPixelColor(led, green);
  // show change on ledstrip
  strip.show();
}

void led_blue(int led) {
  // set led color to blue
  strip.setPixelColor(led, blue);
  // show change on ledstrip
  strip.show();
}

void led_off(int led) {
  // turn led off
  strip.setPixelColor(led, off);
  // show change on ledstrip
  strip.show();
}