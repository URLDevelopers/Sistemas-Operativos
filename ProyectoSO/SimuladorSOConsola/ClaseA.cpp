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
	cout << "Funcion 2" << endl;
	cout << "Parametro : " << parametro << endl;
	return parametro;
}