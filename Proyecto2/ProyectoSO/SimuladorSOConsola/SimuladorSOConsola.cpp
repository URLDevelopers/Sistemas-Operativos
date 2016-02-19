// SimuladorSOConsola.cpp: archivo de proyecto principal.

#include "stdafx.h"
#include <iostream>
#include "ClaseA.h"
#include "Kernel.h"

using namespace std;

static int Funcion1(int parametro)
{
	cout << "Proceso 1 -> " << " Id PCB: " << parametro << endl;
	return parametro;
}

int main()
{
	int(*callback1)(int) = &Funcion1;
	int(*callback2)(int) = &ClassA::Funcion2;
	int(*callback3)(int) = NULL;

	Kernel *core = new Kernel();
	core->EjecutarCore(callback1, callback2, callback3);

    return 0;
}
