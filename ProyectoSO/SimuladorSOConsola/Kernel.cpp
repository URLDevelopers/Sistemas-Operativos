#include "stdafx.h"
#include "Kernel.h"
#include <iostream>
#include "ClaseA.h"
#include "ClaseB.h"

using namespace std;

Kernel::Kernel()
{
	Id = 0;
	Table = NULL;
	SizeCore = 0;
}


Kernel::~Kernel()
{
	Id = 0;
	SizeCore = 0;
	Table = NULL;
}

//Solicitud PCB
bool Kernel::RegistrarPCB(PCB * nuevo)
{
	if (SizeCore >= SIZE)
	{
		return false;
	}
	if (Table == NULL)
	{
		Table = nuevo;
		Table->SetSiguiente(Table);
		Table->SetAnterior(Table);
	}
	else
	{
		nuevo->SetSiguiente(Table);
		nuevo->SetAnterior(Table->GetAnterior());
		Table->GetAnterior()->SetSiguiente(nuevo);
		Table->SetAnterior(nuevo);
		Table = nuevo;
	}
	SizeCore++;
	return true;
}

int Kernel::GetId()
{
	Id++;
	return Id;
}

bool Kernel::LiberarPCB(PCB *nodo)
{
	if (SizeCore == 1)
	{
		if (Table == nodo)
		{
			Table->~PCB();
			Table = NULL;
			SizeCore--;
			return true;
		}
		return false;
	}
	else
	{
		PCB *aux = Table;
		for (int i = 0; i < SizeCore; i++)
		{
			if (aux == nodo)
			{
				aux->GetAnterior()->SetSiguiente(aux->GetSiguiente());
				aux->GetSiguiente()->SetAnterior(aux->GetAnterior());
				SizeCore--;
				if (aux == Table)
				{
					Table = Table->GetSiguiente();
				}
				aux->~PCB();
				return true;
			}
			aux = aux->GetSiguiente();
		}
		return false;
	}
}

void Kernel::ActivarPCB(PCB *nodo)
{
	int *funcion = nodo->GetProceso();
	typedef int(*Metodo)(int);
	Metodo RealizarFuncion = (Metodo)*(&funcion);
	nodo->SetEstado(EJECUCION);
	RealizarFuncion(nodo->GetId());
	nodo->SetEstado(TERMINADO);
}

void Kernel::EjecutarCore(int(*cb1)(int), int(*cb2)(int), int(*cb3)(int))
{
	ClassB::SetCallback3(cb3);
	Kernel *Core = new Kernel();
	char ej = '1';
	while (ej == '1')
	{
		system("cls");
		PCB *pcb1 = new PCB(Core->GetId(), (int*)cb1, NUEVO);
		PCB *pcb2 = new PCB(Core->GetId(), (int*)cb2, NUEVO);
		PCB *pcb3 = new PCB(Core->GetId(), (int*)cb3, NUEVO);
		RegistrarPCB(pcb1);
		RegistrarPCB(pcb2);
		RegistrarPCB(pcb3);
		ActivarPCB(pcb1);
		ActivarPCB(pcb2);
		ActivarPCB(pcb3);
		LiberarPCB(pcb1);
		LiberarPCB(pcb2);
		LiberarPCB(pcb3);
		cin >> ej;
		if (ej != '1')
		{
			break;
		}
	}
}

void Kernel::assembler()
{
	__asm
	{
		mov al, 2
		mov dx, ax
	}
}