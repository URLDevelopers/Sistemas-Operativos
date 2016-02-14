#include "stdafx.h"
#include "Kernel.h"
#include <cstdlib>
#include <list>
#include "ClassA.h"
#include "ClassB.h"

using namespace std;

Kernel::Kernel()
{
	ID = 0;
	Table = NULL;
}


Kernel::~Kernel()
{
}

//Solicitar registro disponible de PCB
bool Kernel::SolicitarRegistro(PCB * nuevo)
{
	if (Table == NULL)
	{
		Table = nuevo;
	}
	else
	{
		nuevo->SetNext(Table);
		Table->SetPrev(nuevo);
		Table = nuevo;

	}
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
	return true;
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

void Kernel::EjecutarSistemaOperativo()
{

}