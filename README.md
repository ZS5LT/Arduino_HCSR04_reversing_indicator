# Arduino_stuff
/*
  This file is a simple driver for the HCSR04 ultrasonic distance sensor and a buzzer.
  
  The HCSR04 distance sensor is connected to Arduino pins D12 and D13.
  
  A buzzer is connected to Arduino pin Dx.
  
  The buzzer emits an audio 'pip' (of duration PIP_TIME mS) at regulatr intervals.  
  If there is no object or surface closer than 4m away, the unit will pip every FAR_PIP_DELAY mS.
  If there is an object at distance 2mm from the sensor or closer, the unit will pip every NEAR_PIP_DELAY mS.
  The period between pips varies proportionally between these two distances and times, speeding up as the object moves closer.  
  
  Other constants: LOOP_DELAY is the period of the loop (the frequency of sensor readings)    
                   BUFFSIZE is the number of sensor readings that are averaged to determine the distance.  
                   Too small a value and the unit is subject to spurous readings.
                   Too large a value and the unit will smooth out spurous readings but detecting changes will lag. 
*/
