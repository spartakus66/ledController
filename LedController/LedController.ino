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
	led[0] = new Led(LED_BUILTIN);

	led[1] = new Led(LED_BAR_1);
	led[2] = new Led(LED_BAR_2);
	led[3] = new Led(LED_BAR_3);
	led[4] = new Led(LED_BAR_4);
	led[5] = new Led(LED_BAR_5);
	led[6] = new Led(LED_BAR_6);
	led[7] = new Led(LED_BAR_7);
	led[8] = new Led(LED_BAR_8);
	led[9] = new Led(LED_BAR_9);

	ledPool = new LedPool();

	ledPool->add(led[2], 1);

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