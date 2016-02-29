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

using namespace std;

//Funcion no. 1 estatica en todo el programa
static int Funcion1(int par)
{
	cout << "Funcion 1" << endl;
	cout << "Parametro recibido: " << par << endl;
	return par;
}

void Terminar()
{
	char x = getch();
	if (x == 'f' || x == 'F')
	{
		exit(0);
	}
}

int main()
{
	//Callbacks

	int(*callback1)(int) = &Funcion1;
	int(*callback2)(int) = &ClassA::Funcion2;
	int(*callback3)(int) = NULL;


	Kernel *Core = new Kernel();
	thread t1(Core->EjecutarSistemaOperativo);
	thread t2(Terminar);
	
	t1.join();
	t2.join();
	Core->EjecutarSistemaOperativo(callback1, callback2, callback3);

    return 0;
}

