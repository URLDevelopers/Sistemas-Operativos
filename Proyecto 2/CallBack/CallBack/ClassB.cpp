#include "stdafx.h"
#include "ClassB.h"
#include <iostream>

using namespace std;

ClassB::ClassB()
{
	
}

void ClassB::SetCB3(int(*funcion)(int))
{
	funcion = &ClassB::Funcion3;
}

int ClassB::Funcion3(int par) //Private function
{
	cout << "Funcion 3" << endl;
	cout << "Parametro recibido: " << par << endl;
	return par;
}

ClassB::~ClassB()
{
}
