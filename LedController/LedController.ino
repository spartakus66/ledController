/*
 Name:		LedController.ino
 Created:	13.02.18 16:19:15
 Author:	Krzysiek M
*/

#include "CircularBuffer.h"

#define LED_BAR_1 57
#define LED_BAR_2 58
#define LED_BAR_3 59
#define LED_BAR_4 60
#define LED_BAR_10 37
#define LED_BAR_9 38
#define LED_BAR_8 39
#define LED_BAR_7 40
#define LED_BAR_6 41
#define LED_BAR_5 42

CircularBuffer *receiveBuffer;

// the setup function runs once when you press reset or power the board
void setup() 
{
	Serial.begin(9600);
	while (!Serial)
	{
		;
	}
	pinMode(LED_BAR_1, OUTPUT);
	pinMode(LED_BAR_2, OUTPUT);
	pinMode(LED_BAR_3, OUTPUT);
	pinMode(LED_BAR_4, OUTPUT);
	pinMode(LED_BAR_5, OUTPUT);
	pinMode(LED_BAR_6, OUTPUT);
	pinMode(LED_BAR_7, OUTPUT);
	pinMode(LED_BAR_8, OUTPUT);
	pinMode(LED_BAR_9, OUTPUT);
	pinMode(LED_BAR_10, OUTPUT);
	digitalWrite(LED_BAR_1, HIGH);

	receiveBuffer = new CircularBuffer(450);

}

// the loop function runs over and over again until power down or reset
void loop() 
{
	static unsigned long previousMillis = 0;
	unsigned long currentMillis = millis();
	long interval = 500;

	if (currentMillis - previousMillis >= interval) 
	{
		// save the last time you blinked the LED
		previousMillis = currentMillis;
		digitalWrite(LED_BAR_10, !digitalRead(LED_BAR_10));
	}

}

void serialEvent() // from Rasp, TODO: change to Serial3
{
	while (Serial.available() > 0)
	{
		receiveBuffer->push((char)Serial.read());
	}
}