// Kernel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ObserverKernel.h"
#include <iostream>
#include <Windows.h>

#define SLEEP_TIME 200

using namespace std;

DWORD WINAPI f1(LPVOID lpParameter)
{
	while (1)
	{
		printf("1 - Func1\n");
		Sleep(SLEEP_TIME);
	}
	return 0;
}

DWORD WINAPI f2(LPVOID lpParameter)
{
	while (1)
	{
		printf("2 - Func2\n");
		Sleep(SLEEP_TIME);
	}
}

DWORD WINAPI f3(LPVOID lpParameter)
{
	while (1)
	{
		printf("3 - Func3\n");
		Sleep(SLEEP_TIME);
	}
}

int main()
{
	system("color f0");

	Kernel *kernel = new Kernel();

	PCB pcb1(f1, NULL, kernel);
	PCB pcb2(f2, NULL, kernel);
	PCB pcb3(f3, NULL, kernel);

	kernel->registerObserver(pcb1);
	kernel->registerObserver(pcb2);
	kernel->registerObserver(pcb3);

	kernel->runAllProcesses();

	//system("pause >nul");
    return 0;
}

