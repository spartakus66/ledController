/*
 Name:		LedController.ino
 Created:	13.02.18 16:19:15
 Author:	Krzysiek M
*/

#include "CircularBuffer.h"
#include "IGpio.h"
#include "Led.h"
#include "LedPool.h"

#define LED_BAR_10 37
#define LED_BAR_9 38
#define LED_BAR_8 39
#define LED_BAR_7 40
#define LED_BAR_6 41
#define LED_BAR_5 42

#define LED_BAR_1 57
#define LED_BAR_2 58
#define LED_BAR_3 59
#define LED_BAR_4 60

CircularBuffer *receiveBuffer;
Led *led[10];
char ledPins[] = {LED_BUILTIN,LED_BAR_1,LED_BAR_2,LED_BAR_3,LED_BAR_4,LED_BAR_5,LED_BAR_6,LED_BAR_7,LED_BAR_8,LED_BAR_9,LED_BAR_10 };
char ledMap[] = { 1,5,2,3,4,6,7,8,9,10 };
/*
Led *led2;
Led *led3;
Led *led4;
Led *led5;
Led *led6;
Led *led7;
Led *led8;
Led *led9;
Led *led10;*/
LedPool *ledPool;

void setup()
{
	receiveBuffer = new CircularBuffer(200);
	Serial.begin(9600);
	while (!Serial)
	{
		;
	}
	ledPool = new LedPool();
	for (int i = 0; i < sizeof(ledPins); i++)
		ledPool->add(new Led(ledPins[i]), ledMap[i]);
}

void loop()
{
	static unsigned long previousMillis = 0;
	unsigned long currentMillis = millis();
	long interval = 500;
	char readCommandArr[20];

	if (currentMillis - previousMillis >= interval)
	{
		previousMillis = currentMillis;
		led[0]->toggle();
	}

	while (receiveBuffer->containsData())
	{
		static int buffId = 0;
		char inChar = receiveBuffer->pop();
		if (inChar != '\r')
			if (inChar == '\n' && buffId > 0)
			{
				parseCommand(readCommandArr);
				buffId = 0;
				for (int i = 0; i < buffId; i++)
					readCommandArr[i] = NULL;
			}
			else readCommandArr[buffId++] = inChar;
	}

}

void parseCommand(char *readCommandArr)
{
	switch (readCommandArr[0])
	{
	case 'A':
		
		ledPool->add(led[(int)readCommandArr[1]], (int)readCommandArr[2]);
		Serial.println("OK");
		break;

	case 'S':
		ledPool->setNewState(atoi(&readCommandArr[1]));
		Serial.println("OK");
		break;

	default:
		Serial.println("Nie rozpoznano komendy");
		break;
	}

}

void serialEvent()
{
	while (Serial.available() > 0)
	{
		receiveBuffer->push((char)Serial.read());
	}
}