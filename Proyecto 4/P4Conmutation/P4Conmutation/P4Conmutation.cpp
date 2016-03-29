// P4Conmutation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Timer.h"
#include "Kernel.h"
#include <conio.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	Kernel *SO = new Kernel();
	SO->ExecuteSO();
	return 0;
}

