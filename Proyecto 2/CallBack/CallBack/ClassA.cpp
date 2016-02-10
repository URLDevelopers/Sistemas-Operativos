#include "stdafx.h"
#include "ClassA.h"
#include <iostream>

using namespace std;

ClassA::ClassA()
{
}

int ClassA::Funcion2(int par)
{
	cout << "Funcion 2" << endl;
	cout << "Parametro recibido: " << par;
	return par;
}

ClassA::~ClassA()
{
}
