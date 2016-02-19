#include <time.h>

#pragma once
class Timer
{
private:
	unsigned long beginTime;
public:
	void start();

	unsigned long elapsedTime();

	bool isTimeOut(unsigned long seconds);

	~Timer();
};


