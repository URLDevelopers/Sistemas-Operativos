#include "stdafx.h"
#include "ClaseA.h"
#include <iostream>

using namespace std;

ClassA::ClassA()
{
}

ClassA::~ClassA()
{
}

int ClassA::Funcion2(int parametro)
{
	cout << "Proceso 2 -> " << " Id PCB: " << parametro << endl;
	return parametro;
}