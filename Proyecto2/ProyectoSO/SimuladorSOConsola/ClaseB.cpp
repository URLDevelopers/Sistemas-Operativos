#include "stdafx.h"
#include "ClaseB.h"
#include <iostream>

using namespace std;

ClassB::ClassB()
{

}

void ClassB::SetCallback3(int(*&funcion)(int))
{
	funcion = &ClassB::Funcion3;
}

int ClassB::Funcion3(int par) //Private function
{
	cout << "Proceso 3 -> " << " Id PCB: " << par << endl;
	return par;
}

ClassB::~ClassB()
{
}
