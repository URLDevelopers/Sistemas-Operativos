#include "stdafx.h"
#include "ClassB.h"


ClassB::ClassB()
{
	
}

int ClassB::Funcion3(int par)
{
	return par;
}

int ClassB::AccesoFuncion3(int par)
{
	return Funcion3(par);
}

ClassB::~ClassB()
{
}
