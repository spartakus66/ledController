#ifndef LED_POOL_H_
#define LED_POOL_H_

#include "Led.h"

class LedPool
{

public:

	LedPool():ledsCnt(sizeof(int)*8)
	{
		leds = new Led*[ledsCnt];
		for (int i = 0; i < ledsCnt; i++)
			leds[i] = 0;
	}

	~LedPool()
	{
	}

	void add(Led *led, int bitPosition)
	{
		if ((bitPosition < 0) || (bitPosition > ledsCnt))
			return;
		
		leds[bitPosition] = led;
	}

	void setNewState(int newVal)
	{
		for(int i = 0;i<ledsCnt;i++)
		leds[0]->setState(1);
	}

private:
	Led **leds;
	int ledsCnt;

};

#endif // !LED_POOL_H_