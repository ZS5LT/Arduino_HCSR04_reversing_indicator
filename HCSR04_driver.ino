/*
  driver for the HCSR04 ultrasonic sensor, including a buzzer that blips at increasing frequency as the distance decreases
  sensor is on D12 and D13
*/

#include <HCSR04.h>

#define NEAR_DISTANCE 0.2   // near point (cm) at which the sensor becomes unreliable  
#define FAR_DISTANCE 400.0  // far point (cm) at which the sensor becomes unreliable  
#define NEAR_PIP_DELAY 200  // inter-pip period (mS) at NEAR_DISTANCE  
#define FAR_PIP_DELAY 2000  // inter-pip period (mS) at FAR_DISTANCE  
#define PIP_TIME 20         // pip period (mS)  

#define LOOP_DELAY 250      // delay in the loop (mS)   
#define BUFFSIZE 10         // number of readings used to arrive at a moving average

float buffer[BUFFSIZE];
byte i = 0;                 // index of the next free element in buffer
float d, av, sum;


UltraSonicDistanceSensor distanceSensor(13, 12);  // Initialize sensor useing digital pins 13 and 12
unsigned long last_pip_time;
unsigned long inter_pip_delay;

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
    for (byte j=0; j<BUFFSIZE; j++)
      buffer[j] = 0.0;
      
    last_pip = millis();
}

void loop () {    
    buffer[i] = distanceSensor.measureDistanceCm(); // read the sensor and buffer the result (in cm)
    Serial.println(buffer[i]);
    i = (i++)%BUFFSIZE; 
    
    // get the average of the readings in the buffer
    sum = 0.0;
    for (byte j=0; j<BUFFSIZE; j++)
      sum += buffer[j];
  
    av = sum/BUFFSIZE;
    
    // work out a new inter-pip delay based on the distance measured
    if(av > FAR_DISTANCE) 
      inter_pip_delay = FAR_PIP_DELAY;
    else
      if(av < NEAR_DISTANCE) 
        inter_pip_delay = NEAR_PIP_DELAY;
      else
        inter_pip_delay = (int)(((FAR_DISTANCE - NEAR_DISTANCE)/av)/(FAR_PIP_DELAY - NEAR_PIP_DELAY));
    
    // see if it is time for a pip, bvased on the current distance
    if((millis() - last_pip_time) > (last_pip_time + inter_pip_delay))
    {
      // time for a pip
      // sound the pip for (PIP_TIME) mS
      last_pip_time = millis(); 
    }
    
    delay(LOOP_DELAY);
}
