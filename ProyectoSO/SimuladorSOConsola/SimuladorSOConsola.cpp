// SimuladorSOConsola.cpp: archivo de proyecto principal.

#include "stdafx.h"
#include <iostream>
#include "Kernel.h"


using namespace std;

static void Function1(int parametro)
{
	while (true)
	{
		cout << "Proceso ID: " << parametro << "--Funcion1" << endl;
	}
}

static void Function2(int parametro)
{
	while (true)
	{
		cout << "Proceso ID: " << parametro << "--Funcion2" << endl;
	}
}

int main()	//Thread one
{

	Kernel core;
	core.RegistrarPCB(&Function1);
	core.RegistrarPCB(&Function2);
	core.RunCore();	//Thread Two

    return 0;
}
