#include "stdafx.h"
#include "Timer.h"


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
	return ((unsigned long)clock() - begTime) / (CLOCKS_PER_SEC / 1000);
}

bool Timer::isTimeout(unsigned long milseconds)
{
	return milseconds >= elapsedTime();
}

