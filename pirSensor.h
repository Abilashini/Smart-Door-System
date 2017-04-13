#include "Arduino.h"
#include "smsSender.h"
#include "Door.h"

class pirSensor
{
  private:
    int pirId;
    int ledPin;
    int inputPin;
    int pirState;
    int val;
    
  public:
    pirSensor(int pirId, int ledPin, int inputPin);
    
    int detectMotion();    
};

pirSensor::pirSensor(int pirId, int ledPin, int inputPin):
  pirId(pirId), ledPin(ledPin), inputPin(inputPin) 
{
   pirState = LOW;
   val = 0;                      // define the initial value of 1
   pinMode(ledPin, OUTPUT);      // declare LED as output
   pinMode(inputPin, INPUT);     // declare sensor as input
  
  

  
}

int pirSensor::detectMotion()
{
  {
      val = digitalRead(inputPin);
      if (val == HIGH) 
      {            // check if the input is HIGH
        digitalWrite(ledPin, HIGH);  // turn LED ON
        if (pirState == LOW) 
        {
          pirState = HIGH;
        }
		
      } 
      else 
      {
        digitalWrite(ledPin, LOW); // turn LED OFF
        if (pirState == HIGH)
        {
			if (DS.check_Door == 0)
			{
				send.sendSMS();
			}
          pirState = LOW;
        }
	
      }
	  
	  return pirState;

    }
}
