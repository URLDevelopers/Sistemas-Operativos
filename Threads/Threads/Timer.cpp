#include "stdafx.h"
#include "Timer.h"

void Timer::start()
{
	beginTime = clock();
}

unsigned long Timer::elapsedTime()
{
	return ((unsigned long)clock() - beginTime) / CLOCKS_PER_SEC;
}

bool Timer::isTimeOut(unsigned long seconds)
{
	return seconds >= elapsedTime();
}

Timer::~Timer()
{
	beginTime = 0;
}
