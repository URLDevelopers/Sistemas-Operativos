// Threads.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "Kernel.h"

#define SLEEP_TIME 1000
#define REGS_SIZE 16
#define REGS_NUM 9
#define SUCCESSFUL 0

using namespace std;

DWORD WINAPI f1(LPVOID lpParameter)
{
	while (1)
	{
		cout << "1 - Func1\n";
		Sleep(SLEEP_TIME);
	}
	return 0;
}

DWORD WINAPI f2(LPVOID lpParameter)
{
	while (1)
	{
		cout << "2 - Func2\n";
		Sleep(SLEEP_TIME);
	}
}

//DWORD WINAPI kernelProcess(LPVOID param)
//{
//	Kernel *k = (Kernel*)param;
//	int i = 0;
//	while (!GetAsyncKeyState('F'))
//	{
//		if (k->pcb[i] != NULL)
//			switch (k->pcb[i]->status)
//			{
//			case RUNNING:
//				if (QUANTUM <= k->timer.elapsedTime())
//				{
//					k->pcb[i]->suspend(READY);
//					i = (i + 1) % MAX;
//				}
//				break;
//			case SUSPENDED:
//			case READY:
//				k->pcb[i]->resume();
//				k->timer.start();
//				break;
//			case DONE:
//				k->killProcessAt(i);
//				break;
//			case NEW_PROCESS:
//				k->pcb[i]->admit();
//				k->timer.start();
//				break;
//			}
//		else
//			i = (i + 1) % MAX;
//	}
//	return 0;
//}

int main()
{
	system("color f0");
	Kernel *kernel = new Kernel();
	kernel->addProcess(f1, NULL);
	kernel->addProcess(f2, NULL);

	kernel->runAllProcesses();
	
    return 0;
}

