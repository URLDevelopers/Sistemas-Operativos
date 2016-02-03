// PROYECTO1.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

static int function(int param) {
	cout << "Parametro: "<<param << " Funcion: 1" << endl;
	return 1;
}


class AClass
{
public:
	
    static int function(int param) {
		cout << "Parametro: " << param << " Funcion: 2" << endl;
		return 2;
	}
};

class  BClass
{
public:
	typedef int(BClass::*var)(int); 
	void direc(var &v)
	{
		v = &BClass::function;
	}
	
private:
	int function(int param) {
		cout << "Parametro: " << param << " Funcion: 3" << endl;
		return 3;
	}
};

typedef int(*MyCallBack)(int);
int main()
{
	//toma de valores
	int valor1, valor2, valor3;
	cout << "Ingrese valor 1" << endl;
	cin >> valor1;
	cout << "Ingrese valor 2" << endl;
	cin >> valor2;
	cout << "Ingrese valor 3" << endl;
	cin >> valor3;

	MyCallBack m1 = NULL, m2 = NULL;
	m1 = &function;
	m2 = &AClass::function;
	BClass* b = new  BClass;
	BClass::var m = NULL;
	b->direc(m);
	m1(valor1);
	m2(valor2);
	(b->*m)(valor3);
	system("PAUSE...");
	return 0;
}

