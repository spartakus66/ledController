#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#include <string.h>

class CircularBuffer
{

public:

	CircularBuffer::CircularBuffer(int size)
	{
		buff = new char[size];
		pHead = pTail = buff;
		pEnd = &buff[size - 1];
		_actualSize = 0;
	}

	CircularBuffer::~CircularBuffer()
	{
	}

	int CircularBuffer::push(char inChar)
	{
		char *pNext;
		pNext = pHead + 1;
		if (pNext > pEnd)
			pNext = buff;

		if (pNext == pTail)
			return -1;

		*pHead = inChar;
		pHead = pNext;
		_actualSize++;
		return 0;
	}

	char CircularBuffer::pop()
	{
		if (pHead == pTail)
			return 0x0B;
		char *pNext;
		pNext = pTail + 1;

		if (pNext > pEnd)
			pNext = buff;

		char *temp = pTail;
		pTail = pNext;
		_actualSize--;
		return *temp;
	}

	char* CircularBuffer::getTailAddress()
	{
		return pTail;
	}

	char* CircularBuffer::getHeadAddress()
	{
		return pHead;
	}

	bool CircularBuffer::containsData()
	{
		if (pHead == pTail)
			return false;
		return true;
	}

	int CircularBuffer::getSize()
	{
		return _actualSize;
	}

	void CircularBuffer::deleteAllData()
	{
		for (int i = 0; i < _actualSize; i++)
		{
			pop();
		}
		_actualSize = 0;
		pHead = pTail;
	}


private:
	char *pHead, *pTail, *pEnd;
	char *buff;
	int _actualSize;
};


#endif // !CIRCULAR_BUFFER_H_