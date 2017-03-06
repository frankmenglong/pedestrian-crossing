/*5) Use the following techniques to implement the System in a neat and easy to read way:
- Use a timer rather than delay()s between each change, so that your run loop would be free to handle other tasks 
- Use a Finite State Machine (or more if you like) to implement the system.*/

#include "TimerOne.h"

//Define delay times
#define DELAY_BUTTON_HOLD 20
#define DELAY_CAR2PED 3000
#define DELAY_PED_CROSSING 6000
#define DELAY_PED2CAR 3000



// Pin definitions of leds and buttons
int west_red_car_led = 13;
int west_yellow_car_led = 12;
int west_green_car_led = 11;

int south_red_ped_led = 10;
int south_green_ped_led = 9;

int north_red_ped_led = 8;
int north_green_ped_led = 7;

int east_red_car_led = 6;
int east_yellow_car_led = 5;
int east_green_car_led = 4;

int south_button = 3;
int north_button = 2;

//button states
int south_button_state = 0;
int north_button_state = 0;

int button_pressed = 0;
int button_hold = 0;

//states of the traffic light system
enum States {
  CAR_GOES,
  CAR2PED,
  PED_GOES,
  PED2CAR,
  ERR = -1,
};

States current_state; //the current state

//led patterns at all the states
                         //r,y,g,  r,g   r,g   r,y,g  
int leds_car_goes[]     = {0,0,1,  1,0,  1,0,  0,0,1};
int leds_car2ped[]      = {0,1,0,  1,0,  1,0,  0,1,0};
int leds_ped_goes[]     = {1,0,0,  0,1,  0,1,  1,0,0};
int leds_ped2car[]      = {1,1,0,  1,0,  1,0,  1,1,0};
int leds_err_blk[]      = {0,1,0,  0,0,  0,0,  0,1,0};
int leds_err_off[]      = {0,0,0,  0,0,  0,0,  0,0,0};


//implement a timer
unsigned long timer = 0;

void update_timer(){
  timer += 100;
}

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(west_red_car_led, OUTPUT);
  pinMode(west_yellow_car_led, OUTPUT);
  pinMode(west_green_car_led, OUTPUT);
  
  pinMode(south_red_ped_led, OUTPUT);
  pinMode(south_green_ped_led, OUTPUT);
  
  pinMode(north_red_ped_led, OUTPUT);
  pinMode(north_green_ped_led, OUTPUT);
  
  pinMode(east_red_car_led, OUTPUT);
  pinMode(east_yellow_car_led, OUTPUT);
  pinMode(east_green_car_led, OUTPUT);
  
  pinMode(south_button, INPUT);
  pinMode(north_button, INPUT);

  Timer1.initialize(100000);         // initialize timer1, and set a 0.1 second period
  Timer1.attachInterrupt(update_timer);  // attaches update_timer() as a timer overflow interrupt


  attachInterrupt(digitalPinToInterrupt(north_button), north_button_interrupt , CHANGE); // Enable Button interrupt
  attachInterrupt(digitalPinToInterrupt(south_button), south_button_interrupt , CHANGE); 

  current_state = CAR_GOES; //starts as CG state
  timer = 0;

}

void south_button_interrupt{
  south_button_state = digitalRead(south_button);
}

void north_button_interrupt{
  north_button_state = digitalRead(north_button);
}

// set all leds to the corresponding led patterns
void set_leds(int leds[10]){
  digitalWrite(west_red_car_led, leds[0]);   
  digitalWrite(west_yellow_car_led, leds[1]);
  digitalWrite(west_green_car_led, leds[2]);
   
  digitalWrite(south_red_ped_led, leds[3]);
  digitalWrite(south_green_ped_led, leds[4]);
    
  digitalWrite(north_red_ped_led, leds[5]);
  digitalWrite(north_green_ped_led, leds[6]);
    
  digitalWrite(east_red_car_led, leds[7]);  
  digitalWrite(east_yellow_car_led, leds[8]);
  digitalWrite(east_green_car_led, leds[9]);
}

void blink_yellow_led(){
  if((timer % 2000) < 1000){ //blinks the yellow led every second.
    set_leds(leds_err_blk);
  }
  else{
    set_leds(leds_err_off);
  }
}

//implement the state machine
void change_state(){

  switch(current_state){
    case CAR_GOES:
      set_leds(leds_car_goes);
      if (button_pressed == 1){
        current_state = CAR2PED;
        button_pressed = 0;
        timer = 0;
      }
      if (timer > 60000){ // set back timer when running to long in the same state to prevent overflow
        timer = 0;
      }
      break;

    case CAR2PED:
      set_leds(leds_car2ped);
      if (timer > DELAY_CAR2PED){
        current_state = PED_GOES;
        timer = 0;
      }
      break;

    case PED_GOES:
      set_leds(leds_ped_goes);
      if (timer > DELAY_PED_CROSSING){
        current_state = PED2CAR;
        timer = 0;
      }
      break;

    case PED2CAR:
      set_leds(leds_ped2car);
      if (timer > DELAY_PED2CAR){
        current_state  = CAR_GOES;
        timer = 0;
      }
      break;

    //set default as error state, which happens when pressing the button too long or any error occurs in the program
    default:
      blink_yellow_led();
      if (timer > 60000){ // set back timer when running to long in the same state to prevent overflow
        timer = 0;
      }
      break;
  }
}


// the loop routine runs over and over again forever:
void loop() {


  //check if any of the buttons is pressed
  if ((south_button_state == 1) || (north_button_state == 1)){
    button_pressed = 1;
    button_hold++;
  }
  else{
    button_hold = 0;
  }

  if (button_hold > DELAY_BUTTON_HOLD){ //check if button has been hold for a long time
    if (current_state != ERR){ // set to Error state if not already in Error state
      current_state = ERR;
      button_hold = 0;
    }
    else {
      current_state = CAR2PED; // set to CAR2PED state if long-press button at Error state
      button_hold = 0;
    }
  }

  // check and change the state 
  change_state();

  button_pressed = 0; //prevent button pressed in states other than CAR_GOES
}