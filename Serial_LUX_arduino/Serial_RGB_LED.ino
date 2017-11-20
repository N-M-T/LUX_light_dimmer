#include <TimerOne.h> // library for timing to control AC dimmer module
#include <Wire.h> //remaining libraries for LUX sensor
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

//These variables for AC light module
int channel_1 = 4; // Output to Opto Triac pin, channel 2
int channel_2 = 6; // Output to Opto Triac pin, channel 1 redundant -- triac is broken
int CH1 = 95; //off
int CH2 = 95; //off
int i=0;
int clock_tick; // variable for Timer1

//This variable for LUX sensor
int intendedLUX = 0; 
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

void setup(){
  //begin serial connection
  Serial.begin(9600);
  
  //setting for AC dimmer module
  pinMode(channel_1, OUTPUT);// Set AC Load pin as output
  pinMode(channel_2, OUTPUT);// Set AC Load pin as output
  attachInterrupt(1, zero_crosss_int, RISING);
  Timer1.initialize(100); // set a timer of length 100 microseconds for 50Hz or 83 microseconds for 60Hz;
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here
  
  //settings for LUX sensor
  configureSensor();
}

//main loop
void loop(){
  parseSerial();
  updateBrightness();
}

//function to configure LUX sensor
void configureSensor(void){
  tsl.enableAutoRange(true); 
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);   
}

//function for AC dimmer timing
void timerIsr(){
  clock_tick++;
  if (CH1==clock_tick){
    digitalWrite(channel_1, HIGH); // triac firing
    delayMicroseconds(10); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_1, LOW); // triac Off
  }
}

/*
if (CH2==clock_tick)
{
digitalWrite(channel_2, HIGH); // triac firing
delayMicroseconds(10); // triac On propogation delay (for 60Hz use 8.33)
digitalWrite(channel_2, LOW); // triac Off
}

}
*/

// function to be fired at the zero crossing to dim the light
void zero_crosss_int(){ 
  clock_tick=0;
}

//function to get integer from Serial data and update intended LUX variable
void parseSerial(void){
  if ( Serial.available () > 0 )
  {
    static char input[16];
    static uint8_t i;
    char c = Serial.read ();
  
  if ( c != 'e' && i < 15 ) // assuming e is the end character
    input[i++] = c;
     
  else
  {
    input[i] = '\0';
    i = 0;
       
    int number = atoi( input );
    
    if((number >= 0) && (number <= 500)){ //we have a valid intended LUX 
      intendedLUX = number; //change intendedLUX to serial input
      //Serial.println(number);                                             
    }
  }
}
}

//function to change brightness depending on intended LUX value
void updateBrightness(void){
  sensors_event_t event; 
  tsl.getEvent(&event);
  int calibratedBrightness = event.light;
  if((calibratedBrightness - 5 < intendedLUX) && (calibratedBrightness + 5 < intendedLUX)){ //event.light = actual LUX measurement - ive plus or minus 5 threhsold
    if(CH1 > 5){ //dont go below threshold 
      CH1--;
      //Serial.println(CH1);
    }
  }
    
  if((calibratedBrightness -5  > intendedLUX) && (calibratedBrightness + 5 > intendedLUX)){
    if(CH1 < 95){ //dont go above threshold
      CH1++;
      //Serial.println(CH1);
    }
  }
}


