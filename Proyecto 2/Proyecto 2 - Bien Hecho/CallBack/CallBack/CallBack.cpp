// CallBack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ClassA.h"
#include "ClassB.h"
#include "Kernel.h"

using namespace std;

//Funcion no. 1 estatica en todo el programa
static int Funcion1(int par)
{
	cout << "Funcion 1" << endl;
	cout << "Parametro recibido: " << par << endl;
	return par;
}


int main()
{
	cout << "Grupo 6" << endl;
	//Callbacks

	int(*callback1)(int) = &Funcion1;
	int(*callback2)(int) = &ClassA::Funcion2;
	int(*callback3)(int) = NULL;

	Kernel *Core = new Kernel();
	Core->EjecutarSistemaOperativo(callback1, callback2, callback3);

    return 0;
}

