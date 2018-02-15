/*
 Name:		LedController.ino
 Created:	13.02.18 16:19:15
 Author:	Krzysiek M
*/

#include "CircularBuffer.h"
#include "IGpio.h"
#include "Led.h"
#include "LedPool.h"

CircularBuffer *receiveBuffer;



// the setup function runs once when you press reset or power the board
void setup() 
{
	Serial.begin(9600);
	while (!Serial)
	{
		;
	}




	receiveBuffer = new CircularBuffer(200);

}

// the loop function runs over and over again until power down or reset
void loop() 
{
	static unsigned long previousMillis = 0;
	unsigned long currentMillis = millis();
	long interval = 3000;

	if (currentMillis - previousMillis >= interval) 
	{
		// save the last time you blinked the LED
		previousMillis = currentMillis;
		digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

	}

}

void serialEvent() // from Rasp, TODO: change to Serial3
{
	while (Serial.available() > 0)
	{
		receiveBuffer->push((char)Serial.read());
	}
}