// PROYECTO2.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;
#define TAMANIO 10//TAMANIO DE LA TABLA

#pragma region FASE1
static int function(int param) {
	cout << "Parametro: " << param << " Funcion: 1" << endl;
	return 1;
}
#pragma region CLASES
class AClass
{
public:

	static int function(int param) {
		cout << "Parametro: " << param << " Funcion: 2" << endl;
		return 2;
	}
};

class  BClass : public AClass
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
#pragma endregion
typedef int(*MyCallBack)(int);
#pragma endregion
class PCB 
{
public:
	int llave;
	BClass *k;
	string estado;
	PCB(int,string);
	~PCB();
private:


};

PCB::PCB(int llave,string est)
{
	this->llave = llave;
	this->estado = est;
	//this->*k = new BClass;
}
PCB::~PCB()
{
	this->llave =  NULL;
	this->estado = "";
}
class KERNEL
{
public:
	int contador;
	PCB *pcb[TAMANIO];
	KERNEL();
	~KERNEL();
	
private:
	bool VALIDO(int i) {
		if (i < NULL || i >= TAMANIO)
		{
			return -1;
		}
		if (this->pcb[i] != NULL && (this->pcb[i]->estado != "HECHO"))
		{
			return -2;
		}
		else if (this->pcb[i] != NULL && !(this->pcb[i]->estado != "HECHO"))
		{
			//dotro coso
			return 9;
		}
		if (contador >= TAMANIO)
		{
			return 2;
		}
		else
			return 0;
	}
};

KERNEL::KERNEL()
{
}

KERNEL::~KERNEL()
{
}
int main()
{
	//toma de valores
	int* PCB[10];
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

	PCB[0] = (int*)&m1;
	PCB[1] = (int*)&m2;
	PCB[2] = (int*)&m;

	b->direc(m);
	m1(valor1);

	m2(valor2);
	(b->*m)(valor3);
	system("PAUSE...");
	return 0;
}