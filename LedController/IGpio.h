#ifndef I_GPIO_H_
#define I_GPIO_H_

// interface
struct IGpio
{
	virtual void set() = 0;
	virtual void reset() = 0;
	virtual void toggle() = 0;
	virtual void setState(bool newState) = 0;
};
#endif // !I_GPIO_H_