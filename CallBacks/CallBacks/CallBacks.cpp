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

int *DATA;

int main()
{
	typedef int(*CallBack)(int);
	typedef int(ClassB::*CallBackB)(int);

	DATA = 0;
	CallBack callback1 = &function1;
	CallBack callback2 = &ClassA::function2;
	ClassB *obj = new ClassB();
	CallBackB callback3;
	ClassB::setCallBack(callback3);

	callback1(1);
	callback2(2);
	(obj->*callback3)(3);

	int *vec[10];
	vec[0] = (int*)&callback1;
	vec[1] = (int*)&callback2;
	vec[2] = (int*)&callback3;

	CallBack cb1 = (CallBack)**(&vec[0]);
	CallBack cb2 = (CallBack)**(&vec[1]);
	CallBackB *x = (CallBackB*)(vec[2]);
	cb1(4);
	cb2(5);
	(obj->**x)(6);

	system("pause >nul");
    return 0;
}