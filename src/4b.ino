//4b) Implement the Traffic light system as simply/quickly as you can.

//Define delay times
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
}

// the loop routine runs over and over again forever:
void loop() {
  
  //set default as car goes, ped stops
  digitalWrite(west_red_car_led, LOW);   
  digitalWrite(west_yellow_car_led, LOW);
  digitalWrite(west_green_car_led, HIGH);
  
  digitalWrite(south_red_ped_led, HIGH);
  digitalWrite(south_green_ped_led, LOW);
  
  digitalWrite(north_red_ped_led, HIGH);
  digitalWrite(north_green_ped_led, LOW);
  
  digitalWrite(east_red_car_led, LOW);  
  digitalWrite(east_yellow_car_led, LOW);
  digitalWrite(east_green_car_led, HIGH);

  //check if any of the buttons is pressed
  if (digitalRead(north_button) == 1 || digitalRead(south_button) == 1){


    //car light goes yellow
    digitalWrite(west_red_car_led, LOW);   
    digitalWrite(west_yellow_car_led, HIGH);
    digitalWrite(west_green_car_led, LOW);
    
    digitalWrite(south_red_ped_led, HIGH);
    digitalWrite(south_green_ped_led, LOW);
    
    digitalWrite(north_red_ped_led, HIGH);
    digitalWrite(north_green_ped_led, LOW);
    
    digitalWrite(east_red_car_led, LOW);  
    digitalWrite(east_yellow_car_led, HIGH);
    digitalWrite(east_green_car_led, LOW);
    delay(DELAY_CAR2PED); // wait 3s

    //ped light goes green, car light goes red
    digitalWrite(west_red_car_led, HIGH);   
    digitalWrite(west_yellow_car_led, LOW);
    digitalWrite(west_green_car_led, LOW);
    
    digitalWrite(south_red_ped_led, LOW);
    digitalWrite(south_green_ped_led, HIGH);
    
    digitalWrite(north_red_ped_led, LOW);
    digitalWrite(north_green_ped_led, HIGH);
    
    digitalWrite(east_red_car_led, HIGH);  
    digitalWrite(east_yellow_car_led, LOW);
    digitalWrite(east_green_car_led, LOW);
    delay(DELAY_PED_CROSSING); // wait 6s

    //times up for pedestrians. car light goes yellow & red, ped light goes red
    digitalWrite(west_red_car_led, HIGH);   
    digitalWrite(west_yellow_car_led, HIGH);
    digitalWrite(west_green_car_led, LOW);
    
    digitalWrite(south_red_ped_led, HIGH);
    digitalWrite(south_green_ped_led, LOW);
    
    digitalWrite(north_red_ped_led, HIGH);
    digitalWrite(north_green_ped_led, LOW);
    
    digitalWrite(east_red_car_led, HIGH);  
    digitalWrite(east_yellow_car_led, HIGH);
    digitalWrite(east_green_car_led, LOW);
    delay(DELAY_PED2CAR); // wait 3s


  }
  
}