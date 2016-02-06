#include "stdafx.h"
#include "ClassB.h"


ClassB::ClassB()
{
	
}

void ClassB::SetCB3(int(ClassB::*&fun)(int))
{
	fun = &ClassB::Funcion3;
}

int ClassB::Funcion3(int par) //Private function
{
	return par;
}

ClassB::~ClassB()
{
}
