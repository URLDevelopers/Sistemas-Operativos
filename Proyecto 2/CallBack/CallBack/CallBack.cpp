// CallBack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ClassA.h"
#include "ClassB.h"
#include "Kernel.h"

using namespace std;

//Funcion no. 1 estatica en todo el programa
static int Funcion1(int par)
{
	cout << "Funcion 1" << endl;
	cout << "Parametro recibido: " << par << endl;
	return par;
}


int main()
{
	cout << "Grupo 6" << endl;
	//Callbacks
	int(*callback1)(int) = &Funcion1;
	int(*callback2)(int) = &ClassA::Funcion2;
	int(*callback3)(int); 
	ClassB::SetCB3(callback3);

	Kernel *Core = new Kernel();
	PCB *pcb1 = new PCB(Core->GetID(), (int*)callback1, NUEVO);
	PCB *pcb2 = new PCB(Core->GetID(), (int*)callback2, NUEVO);
	PCB *pcb3 = new PCB(Core->GetID(), (int*)callback3, NUEVO);
	Core->SolicitarRegistro(pcb1);
	Core->SolicitarRegistro(pcb2);
	Core->SolicitarRegistro(pcb3);
	Core->ActivarPCB(0);
	Core->ActivarPCB(1);
	Core->ActivarPCB(2);
	Core->LiberarRegistro(0);
	Core->LiberarRegistro(1);
	Core->LiberarRegistro(2);
	cout << endl;
	system("pause");
    return 0;
}

