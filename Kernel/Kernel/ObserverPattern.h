#pragma once

class Observer
{
public:
	Observer();

	virtual ~Observer() = 0;

	virtual void update() = 0;
};

class Subject
{
public:
	Subject();

	virtual ~Subject() = 0;

	virtual void registerObserver(Observer &observer) = 0;

	virtual void removeObserver(Observer &observer) = 0;

	virtual void notifyObservers() = 0;
};
