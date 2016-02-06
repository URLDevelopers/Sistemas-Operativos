// CallBack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ClassA.h"
#include "ClassB.h"

using namespace std;

void *Table [10];


//Funcion no. 1 estatica en todo el programa
static int Funcion1(int par)
{
	return par;
}

bool RegistroDisponible(int pos)
{
	if (Table[pos] == 0)
	{
		return true;
	}
	return false;
}

void LiberarRegistro(int pos)
{
	Table[pos] = 0;
}

int main()
{
	cout << "Grupo 6" << endl;

	cout << endl;
	system("pause");
    return 0;
}

