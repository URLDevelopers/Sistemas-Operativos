// CallBack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ClassA.h"
#include "ClassB.h"

using namespace std;

//Funcion no. 1 estatica en todo el programa
static int Funcion1(int par)
{
	return par;
}

int main()
{
	cout << "Grupo 6" << endl;
	cout << endl;
	cout << "Funcion 1" << endl;
	int(*callback1)(int) = &Funcion1;
	cout << "Parametro recibido: " << callback1(1) << endl;
	cout << endl;
	cout << "Funcion 2" << endl;
	int(*callback2)(int) = &ClassA::Funcion2;
	cout << "Parametro recibido: " << callback2(2) << endl;
	cout << endl;
	cout << "Funcion 3" << endl;
	ClassB *ObjetoB = new ClassB();
	int(*callback3)(int) = &ObjetoB->AccesoFuncion3;
	cout << "Parametro recibido: " << callback3(3) << endl;
	cout << endl;
	system("pause");
    return 0;
}

