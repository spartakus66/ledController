#ifndef LED_H_
#define LED_H_

class Led : IGpio
{
public:

	Led(int pinNumber):pinNumber(pinNumber)
	{
		pinMode(pinNumber, HIGH);
	}

	~Led()
	{
	}

	void set()
	{
		digitalWrite(pinNumber, HIGH);
	}

	void reset()
	{
		digitalWrite(pinNumber, LOW);
	}

	void toggle()
	{
		digitalWrite(pinNumber, !digitalRead(pinNumber));
	}

	void setState(bool state)
	{
		digitalWrite(pinNumber, state);
	}
private:
	int pinNumber;
};

#endif // !LED_H_