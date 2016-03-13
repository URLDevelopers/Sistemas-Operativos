#pragma once
#include <time.h>

class Timer
{
public:
	Timer();
	~Timer();
	
	unsigned long elapsedTime();

	time_t begTime;
	void Start();

	bool isTimeout(unsigned long milsec);

};

