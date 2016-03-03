#include "stdafx.h"
#include "Timer.h"
#include <time.h>


Timer::Timer()
{
}


Timer::~Timer()
{
}

void Timer::Start()
{
	begTime = clock();
}

unsigned long Timer::elapsedTime()
{
	return ((unsigned long)clock() - begTime) / CLOCKS_PER_SEC;
}

bool Timer::isTimeout(unsigned long seconds)
{
	return seconds >= elapsedTime();
}
