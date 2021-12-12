#define FASTLED_INTERNAL

#include "FastLED.h"
#include "math.h"
#include <Wire.h>

#define PIN 9
#define NUM_LEDS 33
#define BRIGHTNESS 255

#define ON 1
#define OFF 2

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

void loop() {
  if (millis()-time>TIMEOUT) {
    off();
  }
  
  delay(100);
}

/////////////////////////////////////////////////////////////////////////////////////

void control_leds(int howMany) {
  time = millis();
  
  if (Wire.read() == ON) {
    on();
  }
}

//ON
void on() {
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].r = BRIGHTNESS;
    leds[i].g = BRIGHTNESS;
    leds[i].b = BRIGHTNESS;
  }
  FastLED.show();
}

//OFF
void off() {
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].r = 0;
    leds[i].g = 0;
    leds[i].b = 0;
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
    delay(100);
  }
}
