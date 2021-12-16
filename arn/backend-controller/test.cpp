//#include "sensor.cpp"
//#include "light.cpp"
//#include "blinds.cpp"
#include <iostream>
#include <unistd.h>
using namespace std;

class profile {
    //profile identifier
  public:
    int profile_id;	
    //lt_1 through 4 are int that state what status the LED is in at different counters (6hr intervals starting at midnight) 
    //this can be a brightness between 0-100, and different animations when >100 
    int lt_1, lt_2, lt_3, lt_4;
    //b_1 through 4 are int that state how open or closed the blinds are, 100 for closed and 0 for open 
    //same counter periods as for lights
    int b_1, b_2, b_3, b_4;
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
};
/*
Void setup() {
  Sensor sensor;
  Light light;
  Blinds blinds;
}
*/


//active pf for both floors starts on default which is automatic setting
//controls blinds and LEDs as outside luminosity changes
int active_pf_1 = 0;
int active_pf_2 = 0;
int counter = 0;
//blinds closed at night, light off during day and sleep, on during morning and evening
profile work(3, 0, 20, 0, 25, 100, 0, 0, 100);
//blinds always closed as to not disturb the neighbors, animate at night and no/barely any light at morning due to hangovers
profile party(4, 102, 0, 10, 101, 100, 100, 100, 100);
//blinds closed at all counters, light dimly on during night, on during day
profile paranoid(5, 10, 80, 80, 10, 100, 100, 100, 100);
//as a sidenote, profile id start at 3 and not 1 as 1 and 2 are lights on/blinds closed and lights off/blinds open respectively 
//add custom profiles to an array
profile profile_arr[3]{
  work,
  party,
  paranoid
};

void manage_floor(int floor, int active, profile arr[]){
  if(counter >= 0 && counter <= 15){
    cout << "floor " << floor << "lights on: " << arr[active].lt_1 << endl;  
    if (floor==1){
      cout << "floor " << floor << "blinds open: " << arr[active].b_1 << endl;
    }     
  } else if (counter > 15 && counter <= 30) {
    cout << "floor " << floor << "lights on: " << arr[active].lt_2 << endl;
    if (floor==1){
      cout << "floor " << floor << "blinds open: " << arr[active].b_2 << endl;
    }     
  } else if (counter > 30 && counter <= 45) {
    cout << "floor " << floor << "lights on: " << arr[active].lt_3 << endl;
    if (floor==1){
      cout << "floor " << floor << "blinds open: " << arr[active].b_3 << endl;
    }          
  } else {
    cout << "floor " << floor << "lights on: " << arr[active].lt_4 << endl;
    if (floor==1){
      cout << "floor " << floor << "blinds open: " << arr[active].b_4 << endl;
    }   
  }
}

/*void loop()*/ int main (){
//get profile info for each floor from server, pretend it works
int server_pf_1 = 3;
int server_pf_2 = 5;

while(1){
counter += 1;

//switch checks what id we should be running, and makes changes as the
  switch (server_pf_1){
    default:
	cout << "floor 1 lights: " << profile_arr[server_pf_1].lt_1 << "floor 1 blinds: " << profile_arr[server_pf_1].b_1 << endl;
    	manage_floor(1, server_pf_1, profile_arr);
  }

  switch (server_pf_2){
    default:
        manage_floor(2, server_pf_2, profile_arr);
  }


//if counter hits equivalent of 1 minute, reset the counter to 0, allowing us to simulate a day in 60sec
//as the day is split into 6hr quarters, 15sec simulates 6 hrs
  if(counter >= 60) { counter= 0; }
//delay each cycle by 1s

sleep(10);
  //delay(1000);
}
}
