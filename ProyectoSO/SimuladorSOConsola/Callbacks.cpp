#include "stdafx.h"
#include "Callbacks.h"
#include <iostream>

using namespace std;

int ClassA::Funcion2(int parametro)
{
	cout << "Funcion 2" << endl;
	cout << "Parametro : " << parametro << endl;
	return parametro;
}

void ClassB::SetCallback3(int(*&funcion)(int))
{
	funcion = &ClassB::Funcion3;
}

int ClassB::Funcion3(int par) //Private function
{
	cout << "Funcion 3" << endl;
	cout << "Parametro: " << par << endl;
	return par;
}