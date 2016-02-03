// CallBacks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

static int function1(int param)
{
	cout << "Parametro: " << param << "\n";
	cout << "Funcion: " << 1 << "\n";
	return 1;
}

class ClassA
{
public:
	static int function2(int param);
};

int ClassA::function2(int param)
{
	cout << "Parametro: " << param << "\n";
	cout << "Funcion: " << 2 << "\n";
	return 2;
}

class ClassB
{
public:
	static void setCallBack(int (ClassB::*&cb)(int));
private:
	int function3(int param);
};

int ClassB::function3(int param)
{
	cout << "Parametro: " << param << "\n";
	cout << "Funcion: " << 3 << "\n";
	return 3;
}

void ClassB::setCallBack(int (ClassB::*&cb)(int))
{
	cb = &ClassB::function3;
}

int main()
{
	int(*callback1)(int) = &function1;
	int(*callback2)(int) = &ClassA::function2;
	ClassB *obj = new ClassB();
	int (ClassB::*callback3)(int);
	ClassB::setCallBack(callback3);

	callback1(1);
	callback2(2);
	(obj->*callback3)(3);

	system("pause >nul");
    return 0;
}