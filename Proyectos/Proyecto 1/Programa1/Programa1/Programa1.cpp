// Programa1.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

class claseA
{
public:
	static int function(int param)
	{
		printf("Funcion 2: estatica en clase A\n");
		printf(" - Se mando el valor: %d\n", param);
		return param;
	}
};

class claseB
{

	public:
		static void calling_function(int (claseB::*&mem)(int))
		{
			mem = &function;
		}

	private:
		int function(int param)
		{
			printf("Funcion 3: privada en clase B\n");
			printf(" - Se mando el valor: %d\n", param);
			return param;
		}
};

static int function(int param)
{
	printf("Funcion 1: estatica de todo el programa\n");
	printf(" - Se mando el valor: %d\n", param);
	return param;
}


void initializateArray(void *theArray[])
{
	for (int i = 0; i < 10; i++)
	{
		theArray[i] = NULL;
	}
}

void setPosition(int (*param)(int),void *theArray[]) {

	for (int i = 0; i < 10; i++)
	{
		if (theArray[i] == NULL) {
			theArray[i] = param;
			return;
		}
	}
}

void recorreVector(void *theArray[])
{
	int(*auxCallback) (int);
	for (int i = 0; i < 10; i++)
	{
		if (theArray[i] != NULL)
		{
			auxCallback = (int(*)(int))theArray[i];
			auxCallback((i+1) * 10);
			theArray[i] = NULL;
		}
	}
}

void *vector[10];

int main()
{

	int(*PrimerCallback) (int);
	int(*SegundoCallback) (int);
	int(claseB::*TercerCallback) (int);

	/*PrimerCallback = &function;
	PrimerCallback(10);

	SegundoCallback = &claseA::function;
	SegundoCallback(20);
	
	claseB::calling_function(TercerCallback);
	claseB *objeto = new claseB();
	(objeto->*TercerCallback)(30);
	*/
	initializateArray(vector);
	
	setPosition(&function,vector);
	setPosition(&claseA::function,vector);

	recorreVector(vector);
	//setPosition(&function);
	//PrimerCallback = (int(*)(int))vector[0];
	//PrimerCallback(11);

    return 0;
}