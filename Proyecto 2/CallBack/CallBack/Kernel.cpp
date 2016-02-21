#include "stdafx.h"
#include "Kernel.h"
#include <iostream>
#include "ClassA.h"
#include "ClassB.h"

using namespace std;

Kernel::Kernel()
{
	ID = 0;
	Table = NULL;
	LongCol = 0;
}


Kernel::~Kernel()
{
	ID = LongCol = 0;
	Table = NULL;
}

//Solicitar registro disponible de PCB
bool Kernel::SolicitarRegistro(PCB * nuevo)
{
	if (LongCol >= LONG)
	{
		return false;
	}
	if (Table == NULL)
	{
		Table = nuevo;
		Table->SetNext(Table);
		Table->SetPrev(Table);
	}
	else
	{
		nuevo->SetNext(Table);
		nuevo->SetPrev(Table->GetPrev());
		Table->GetPrev()->SetNext(nuevo);
		Table->SetPrev(nuevo);
		Table = nuevo;
	}
	LongCol++;
	return true;
}

int Kernel::GetID()
{
	ID++;
	return ID;
}

//Liberar el Registro disponible PCB
bool Kernel::LiberarRegistro(PCB *nodo)
{
	if (LongCol == 1)
	{
		if (Table == nodo)
		{
			Table->~PCB();
			Table = NULL;
			LongCol--;
			return true;
		}
		return false;
	}
	else
	{
		PCB *aux = Table;
		for (int i = 0; i < LongCol; i++)
		{
			if (aux == nodo)
			{
				aux->GetPrev()->SetNext(aux->GetNext());
				aux->GetNext()->SetPrev(aux->GetPrev());
				LongCol--;
				if (aux == Table)
				{
					Table = Table->GetNext();
				}
				aux->~PCB();
				return true;
			}
			aux = aux->GetNext();
		}
		return false;
	}
}

//Llamada a callback activo
void Kernel::ActivarPCB(PCB *nodo)
{
	int *funcion = nodo->GetInstruccion();
	typedef int(*Metodo)(int);
	Metodo RealizarFuncion = (Metodo)*(&funcion);
	nodo->SetEstado(EJECUCION);
	RealizarFuncion(nodo->GetId());
	nodo->SetEstado(TERMINADO);
}

void Kernel::EjecutarSistemaOperativo(int(*cb1)(int), int(*cb2)(int), int(*cb3)(int))
{
	ClassB::SetCB3(cb3);
	Kernel *Core = new Kernel();
	char ej = '1';
	while (ej=='1')
	{
		system("cls");
		PCB *pcb1 = new PCB(Core->GetID(), (int*)cb1, NUEVO);
		PCB *pcb2 = new PCB(Core->GetID(), (int*)cb2, NUEVO);
		PCB *pcb3 = new PCB(Core->GetID(), (int*)cb3, NUEVO);
		SolicitarRegistro(pcb1);
		SolicitarRegistro(pcb2);
		SolicitarRegistro(pcb3);
		ActivarPCB(pcb1);
		ActivarPCB(pcb2);
		ActivarPCB(pcb3);
		LiberarRegistro(pcb1);
		LiberarRegistro(pcb2);
		LiberarRegistro(pcb3);
		cin >> ej;
		if (ej != '1')
		{
			break;
		}
	}
}

//Assembler
int Kernel::assembler()
{
	int16_t x = 0;
	__asm
	{
		mov ax, 10d
		mov x, ax
	}
	return x;
}