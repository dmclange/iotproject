//#include "sensor.cpp"
//#include "light.cpp"
//#include "blinds.cpp"
#include <iostream>

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
	lt_2 =  t_06_12;
	lt_3 =  t_12_18;
	lt_4 =  t_18_24;
	b_1 =  b_00_06;
	b_2 =  b_06_12;
	b_3 =  b_12_18;
	b_4 =  b_18_24;
    }
}

Void setup() {
  /*Sensor sensor;
  Light light;
  Blinds blinds;*/
}

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

void manage_floor(int floor, int active, arr[3]){
  if(time >= 0 && time <= 15){
    light.set(floor,(obj[active].lt_1));  
    if (floor==1){
      blinds.close(obj[active].b_1);
    }     
  } else if (time > 15 && time <= 30) {
    light.set(floor,(obj[active].lt_2);       
    if (floor==1){
      blinds.close(obj[active].b_2);
    }    
  } else if (time > 30 && time <= 45) {
    light.set(floor, (obj[active].lt_3));      
    if (floor==1){
      blinds.close(obj[active].b_3);
    }         
  } else {
    light.set(floor ,(obj[active].lt_4));      
    if (floor==1){
      blinds.close(obj[active].b_4);
    }  
  }
}

/*void loop()*/ int main (){
//get profile info for each floor from server, pretend it works
int server_pf_1 = 3;
int server_pf_2 = 5;
while(1){
time += 1;

//switch checks what id we should be running, and makes changes as the
  switch (server_pf_f1){
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

  switch (server_pf_f2){
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

sleep(1000);
  //delay(1000);
}
}
