#ifndef LED_H_
#define LED_H_

class Led : IGpio
{
public:

	Led(int pinNumber):pinNumber(pinNumber)
	{
		pinMode(pinNumber, HIGH);
		reset();
	}

	~Led()
	{
	}

	void set()
	{
		state = true;
		digitalWrite(pinNumber, HIGH);
	}

	void reset()
	{
		state = false;
		digitalWrite(pinNumber, LOW);
	}

	void toggle()
	{
		if (state)
			reset();
		else
			set();
	}

	void setState(bool state)
	{
		if (state)
			set();
		else
			reset();
	}
private:
	int pinNumber;
	bool state;
};

#endif // !LED_H_