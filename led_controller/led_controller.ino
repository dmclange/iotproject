#define FASTLED_INTERNAL

#include "FastLED.h"
#include "math.h"
#include <Wire.h>

#define PIN 9
#define NUM_LEDS 33
#define BRIGHTNESS 255

#define I2C_ADDRESS 1

#define TIMEOUT 5000

CRGB leds[NUM_LEDS];

int sine_table[NUM_LEDS];
int cosine_table[NUM_LEDS];

unsigned long time = 0;

/////////////////////////////////////////////////////////////////////////////////////

void setup() {
  FastLED.addLeds<WS2812, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );

  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(control_leds);

  for (int i = 0; i < NUM_LEDS; i++) {
    sine_table[i] = (sin(i * M_PI * 2 / NUM_LEDS) + 1) / 2 * BRIGHTNESS;
    cosine_table[i] = (sin((i - NUM_LEDS / 2) * M_PI * 2 / NUM_LEDS) + 1) / 2 * BRIGHTNESS;
  } 
}

int brightness;
int profile;

void loop() {
  if (millis()-time>TIMEOUT) {
    set_light(0);
  }
  
  switch(profile) {
  case 1:
    colors();
    break;
  case 2:
    set_light(brightness);
    break;
  }
}

/////////////////////////////////////////////////////////////////////////////////////

void control_leds(int howMany) {
  
  time = millis();

  int value = Wire.read();

  if (value == 101) {
    profile = 1;
  }
  else
    profile = 2;
    brightness = (value/100)*255;
}

//SET LIGHT
void set_light(int brightness) {
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].r = brightness;
    leds[i].g = brightness;
    leds[i].b = brightness;
  }
  FastLED.show();
}

//COLORS
void colors() {
  for (int j = 0; j < NUM_LEDS; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {

      int value = i;
      int offset = j;

      if (value + offset >= NUM_LEDS) {
        offset -= NUM_LEDS;
      }

      leds[i].r = sine_table[value + offset];
      leds[i].g = 0;
      leds[i].b = cosine_table[value + offset];

    }
    FastLED.show();
    delay(50);
  }
}
