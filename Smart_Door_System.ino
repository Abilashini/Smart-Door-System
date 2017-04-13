#include "pirSensor.h"
#include "smsSender.h"
#include <SPI.h>
#include <Adafruit_CC3000.h>
#include "pirSensor.h"
#include "smsSender.h"
#include "Door.h"


Door DS(4);
smsSender send;
pirSensor S1(1, 13, 2);

void setup() {
	

	Serial.begin(9600);
  
	send.GetInstance();
	send.start();

}

void loop() {
 S1.detectMotion();
 Serial.print(S1.detectMotion);
 Serial.print(" , ");
 Serial.print(DS.check_Door);

}
