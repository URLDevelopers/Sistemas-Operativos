// TareaCallbacks.cpp: archivo de proyecto principal.
#include "stdafx.h"
#include <iostream>
using namespace std;
using namespace System;

//type (*nombre) (typearameters)
int (*callback1) (int);
int (*callback2) (int);
int (*callback3) (int);

static int functionA(int parameter)
{
	cout << "function no. 1: " << parameter << endl;
	return 0;
}

public class classA
{
	public : static int functionB(int parameter)
	{
		cout << "function no. 2: " << parameter << endl;
		return 0;
	}
};

public class classB
{
	public: static int getfunctionC(int parameter) {
		return functionC(parameter);
	}

	private: static int functionC(int parameter)
	{
		cout << "function no. 3: " << parameter << endl;
		return 0;
	}
};

int main()
{
	callback1 = &functionA;
	callback1(1);
	classA clsa;
	callback2 = &(clsa.functionB);
	callback2(2);
	classB clsb;
	callback3 = &(clsb.getfunctionC);
	callback3(3);
	
	Console::ReadLine();
    return 0;
}
