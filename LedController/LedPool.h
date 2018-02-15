#ifndef LED_POOL_H_
#define LED_POOL_H_

#include "Led.h"

#define LED_QUANTITY 10

class LedPool
{

public:

	LedPool()
	{
	}

	~LedPool()
	{
	}

	void add(Led *led, int bitPosition)
	{
		if (bitPosition <= LED_QUANTITY && bitPosition >= 0)
			ledArr[bitPosition] = led;
	}

	void setNewState(int newVal)
	{
		**ledArr = newVal;
	}

private:
	Led *ledArr[LED_QUANTITY];

};

#endif // !LED_POOL_H_