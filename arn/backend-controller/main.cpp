#include "math.h"
#include <Wire.h>

#include "led_controller.ino"
#include "class_blinds.ino"
#include "class_light.ino"

unsigned long time = 0;

class profile {
    //profile identifier
    public int profile_id
    //lt_1 through 4 are int that state what status the LED is in at different times (6hr intervals starting at midnight) 
    //this can be a brightness between 0-100, and different animations when >100 
    public int lt_1, lt_2, lt_3, lt_4;
    //b_1 through 4 are int that state how open or closed the blinds are, 100 for closed and 0 for open 
    //same time periods as for lights
    public int b_1, b_2, b_3, b_4;
    //awful contstructor
    profile(int id, 
	    int t_00_06, int t_06_12, int t_12_18, int t_18_24, 
	    int b_00_06, int b_06_12, int b_12_18, int b_18_24){
	profile_id = id;
	lt_1 =  t_00_06;
	lt_1 =  t_06_12;
	lt_1 =  t_12_18;
	lt_1 =  t_18_24;
	b_1 =  b_00_06;
	b_2 =  b_06_12;
	b_3 =  b_12_18;
	b_4 =  b_18_24;
    }
}

Void setup() {
  FastLED.addLeds<WS2812, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );

  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(control_leds);
	
  for (int i = 0; i < NUM_LEDS; i++) {
    sine_table[i] = (sin(i * M_PI * 2 / NUM_LEDS) + 1) / 2 * BRIGHTNESS;
    cosine_table[i] = (sin((i - NUM_LEDS / 2) * M_PI * 2 / NUM_LEDS) + 1) / 2 * BRIGHTNESS;
  } 

}

Light led_1(1);
Light led_2(2);
Blinds blind_lower;
//active pf for both floors starts on default which is automatic setting
//controls blinds and LEDs as outside luminosity changes
active_pf_f1 = 0;
active_pf_f2 = 0;

//blinds closed at night, light off during day and sleep, on during morning and evening
profile work(3, 0, 20, 0, 25, 100, 0, 0, 100);
//blinds always closed as to not disturb the neighbors, animate at night and no/barely any light at morning due to hangovers
profile party(4, 102, 0, 10, 101, 100, 100, 100, 100);
//blinds closed at all times, light dimly on during night, on during day
profile paranoid(5, 10, 80, 80, 10, 100, 100, 100, 100);
//as a sidenote, profile id start at 3 and not 1 as 1 and 2 are lights on/blinds closed and lights off/blinds open respectively 
//add custom profiles to an array
profile profile_arr[3]{
  work,
  party,
  paranoid
};

void manage_floor1(int active, profile obj[3]){
  if(time >= 0 && time <= 15){
    led_1.set_light(obj[active].lt_1);
    blind_lower.close(obj[active].b_1);
  } else if (time > 15 && time <= 30) {
    led_1.set_light(obj[active].lt_2);   
    blind_lower.close(obj[active].b_2);    
  } else if (time > 30 && time <= 45) {
    led_1.set_light(obj[active].lt_3);   
    blind_lower.close(obj[active].b_3);    
  } else {
    led_1.set_light(obj[active].lt_4);   
    blind_lower.close(obj[active].b_4);    
  }
}

void manage_floor2(profile obj[], int size){
  if(time >= 0 && time <= 15){
    led_2.set_light(obj[active].lt_1);
  } else if (time > 15 && time <= 30) {
    led_2.set_light(obj[active].lt_2);   
  } else if (time > 30 && time <= 45) {
    led_2.set_light(obj[active].lt_3);   
  } else {
    led_2.set_light(obj[active].lt_4);   
  }
}



void loop() {
//get profile info for each floor from server, pretend it works
int server_pf_1;
int server_pf_2;


//if (millis()-time>TIMEOUT) {
//  set_light(0);
//}

time += 1;

//switch checks what id we should be running, and makes changes as the
  switch (active_pf_f1){
    case 0:
      //check luminosity
      int lum = 1;
      led_1.set_light(100-lum);
      blind_lower.close(100-lum);
    case 1:
      led_1.set_light(100);
      blind_lower.close(100);
    case 2:
      led_1.set_light(0);
      blind_lower.close(0);
    default:
    	manage_floor1(active_pf_f1, [profile_arr[]]);
  }

  switch (active_pf_f2){
    case 0:
      //check luminosity
      int lum = 1;
      led_2.set_light(100-lum);
    case 1:
      led_2.set_light(100);
    case 2:
      led_2.set_light(0);
    default:
        manage_floor2(active_pf_f2, [profile_arr[]]);
  }


//if time hits equivalent of 1 minute, reset the time to 0, allowing us to simulate a day in 60sec
//as the day is split into 6hr quarters, 15sec simulates 6 hrs
  if(time >= 60) { time= 0; }
//delay each cycle by 1s
delay(1000);
}
