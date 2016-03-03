#include "stdafx.h"
#include "Kernel.h"
#include <iostream>
#include <conio.h>

using namespace std;

Kernel::Kernel()
{
	ThreadID = 0;
	HeadTable = NULL;
	TailTable = NULL;
	SizeTable = 0;
}


Kernel::~Kernel()
{
	ThreadID = 0;
	SizeTable = 0;
	HeadTable->~PCB();
	TailTable->~PCB();
}


bool Kernel::RegistrarPCB(void *Function1)
{
	ThreadID++;
	PCB *nuevo = new PCB(ThreadID, (int*)Function1, NEW_PROCESS);
	if (SizeTable >= SIZE)
	{
		return false;
	}
	if (HeadTable == NULL)
	{
		HeadTable = nuevo;
		HeadTable->SetEstado(READY);
		HeadTable->SetSiguiente(HeadTable);
		HeadTable->SetAnterior(HeadTable);
	}
	else
	{
		nuevo->SetSiguiente(HeadTable);
		nuevo->SetAnterior(HeadTable->GetAnterior());
		HeadTable->GetAnterior()->SetSiguiente(nuevo);
		HeadTable->SetAnterior(nuevo);
		HeadTable = nuevo;
		HeadTable->SetEstado(READY);
	}
	SizeTable++;
	return true;
}

void Kernel::RunCore()
{
	int         KeyInfo;
	PCB *aux = HeadTable;

	do
	{
		cout << "Thread ID: " << 0 << "--Funcion1" << endl;

		KeyInfo = _getch();
		if (SizeTable > 0 && aux->GetEstado == READY)
		{
			aux->SetEstado(RUNNING);
			Hilos.CreateThread(aux->GetId, aux->GetProceso);

			aux = aux->GetSiguiente();
		}
	} while (tolower(KeyInfo) != 'f');

	ShutDown();
}

void Kernel::ShutDown(void) // Shut down threads 
{
	while (ThreadID > 0)
	{
		// Tell thread to die.
		ThreadID--;
	}

	// Clean up display when done
	Hilos.ClearScreen();
}

int Kernel::GetId()
{
	return 0;
}

bool Kernel::LiberarPCB(PCB *nodo)
{
	if (SizeTable == 1)
	{
		if (HeadTable == nodo)
		{
			HeadTable->~PCB();
			HeadTable = NULL;
			SizeTable--;
			return true;
		}
		return false;
	}
	else
	{
		PCB *aux = HeadTable;
		for (int i = 0; i < SizeTable; i++)
		{
			if (aux == nodo)
			{
				aux->GetAnterior()->SetSiguiente(aux->GetSiguiente());
				aux->GetSiguiente()->SetAnterior(aux->GetAnterior());
				SizeTable--;
				if (aux == HeadTable)
				{
					HeadTable = HeadTable->GetSiguiente();
				}
				aux->~PCB();
				return true;
			}
			aux = aux->GetSiguiente();
		}
		return false;
	}
}
