#pragma once

class Timer
{
public:
	Timer();
	~Timer();

	void Start();

	unsigned long begTime;

	unsigned long elapsedTime();
	
	bool isTimeout(unsigned long seconds);
};

