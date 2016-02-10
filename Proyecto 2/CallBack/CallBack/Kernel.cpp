#include "stdafx.h"
#include "Kernel.h"


Kernel::Kernel()
{
	ID = 0;
}


Kernel::~Kernel()
{
}

//Solicitar registro disponible de PCB
bool Kernel::SolicitarRegistro(PCB * nuevo)
{
	for (int i = 0; i < LONG; i++)
	{
		if (Tabla[i]->GetEstado() == LIBRE)
		{
			Tabla[i] = nuevo;
			return true;
		}
	}
	return false;
}

int Kernel::GetID()
{
	ID++;
	return ID;
}

//Liberar el Registro disponible PCB
bool Kernel::LiberarRegistro(int pos)
{
	if (pos < LONG && pos >= 0)
	{
		return false;
	}
	Tabla[pos]->~PCB();
	return true;
}

//Liberar el Registro disponible PCB
bool Kernel::LiberarRegistro(PCB *Nuevo)
{
	for (int i = 0; i < LONG; i++)
	{
		if (Tabla[i] == Nuevo)
		{
			Tabla[i]->~PCB();
			return true;
		}
	}
	return false;
}

//Llamada a callback activo
void Kernel::ActivarPCB(int pos)
{
	PCBActivo = pos;
	int *x = Tabla[PCBActivo]->GetInstruccion();
}
