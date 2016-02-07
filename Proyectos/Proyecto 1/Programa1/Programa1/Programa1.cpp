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
		static int calling_function(int param)
		{
			return function(param);
		}

	private:
		static int function(int param)
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

int main()
{

	int(*PrimerCallback) (int);
	int(*SegundoCallback) (int);
	int(*TercerCallback) (int);

	PrimerCallback = &function;
	PrimerCallback(10);

	claseA clase1;
	SegundoCallback = &clase1.function;
	SegundoCallback(20);

	claseB clase2;
	TercerCallback = &clase2.calling_function;
	TercerCallback(30);
	
    return 0;
}


