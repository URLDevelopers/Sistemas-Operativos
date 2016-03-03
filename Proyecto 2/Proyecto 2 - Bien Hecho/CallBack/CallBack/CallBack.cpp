// CallBack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ClassA.h"
#include "ClassB.h"
#include "Kernel.h"
#include <ctime>
#include <thread>
#include <conio.h>
#include <Windows.h>

using namespace std;



//Funcion no. 1 estatica en todo el programa
static int Funcion1(int par)
{
	cout << "Funcion 1" << endl;
	cout << "Parametro recibido: " << par << endl;
	return par;
}

void End()
{
	while (true)
	{
		if (GetAsyncKeyState('f') & 0x8000 || GetAsyncKeyState('F') & 0x8000)
		{
			exit(0);
		}
	}
}

int main()
{
	
	Kernel *Core = new Kernel();
	//Core->EjecutarSistemaOperativo();

	thread t1(End), t2(&Kernel::EjecutarSistemaOperativo, Kernel());
	t1.join();
	t2.join();
    return 0;
}

