#include "stdafx.h"
#include "Kernel.h"
#include <iostream>
#include "ClassA.h"
#include "ClassB.h"

using namespace std;

//Constructor
Kernel::Kernel()
{
	this->ID = 0;
	this->Head = NULL;
	this->Tail = NULL;
	this->LongCol = 0;
}

//Destructor
Kernel::~Kernel()
{
	this->ID = this->LongCol = 0;
	this->Head = NULL;
	this->Tail = NULL;
}

//Solicitar registro disponible de PCB
bool Kernel::SolicitarRegistro(PCB * nuevo)
{
	if (this->LongCol >= LONG)
	{
		return false;
	}
	if (this->Head == NULL)
	{
		this->Head = nuevo;
		this->Tail = nuevo;
	}
	else
	{
		nuevo->SetNext(Head);
		Head->SetPrev(nuevo);
		this->Head = nuevo;
	}
	cout << "El proceso " << nuevo->GetId() << " se ha creado." << endl;
	this->LongCol++;
	return true;
}

//Obtener un ID
int Kernel::GetID()
{
	this->ID++;
	return this->ID;
}

//Liberar el Registro disponible PCB
bool Kernel::LiberarRegistro()
{
	Sleep(1000);
	int id_aux = this->Tail->GetId();
	cout << "El proceso" << id_aux << " se esta eliminando." << endl;
	PCB *aux = this->Tail;
	if (this->Tail == this->Head)
	{
		this->Tail = NULL;
		this->Head = NULL;
	}
	else
	{
		this->Tail = this->Tail->GetPrev();
		this->Tail->SetNext(NULL);
	}
	this->LongCol--;
	aux->~PCB();
	aux = NULL;
	Sleep(1000);
	cout << "El proceso" << id_aux << " se ha eliminando." << endl;
	cout << endl;
	return true;
}

//Llamada a callback activo
void Kernel::ActivarPCB()
{
	int *funcion = this->Tail->GetInstruccion();
	typedef int(*Metodo)(int);
	Metodo RealizarFuncion = (Metodo)*(&funcion);
	this->Tail->SetEstado(EJECUCION);
	Sleep(1000);
	cout << "Estado del proceso " << this->Tail->GetId() << ": En Ejecucion" << endl;
	Sleep(1000);
	cout << endl;
	RealizarFuncion(this->Tail->GetId());
	cout << endl;
	this->Tail->SetEstado(TERMINADO);
	cout << "Estado del proceso " << this->Tail->GetId() << ": Terminado" << endl;
}

//Ejecutar todos los procesos del SO
void Kernel::EjecutarProcesos()
{
	
	while (LongCol > 0)
	{
		ActivarPCB();
		LiberarRegistro();
		if (Tail != NULL)
		{
			cout << "Para ejecutar el siguiente proceso presione enter ..." << endl;
		}
		else
		{
			cout << "Ya no existen mas procesos, presione una tecla para continuar..." << endl;
		}
		getchar();
	}
}

//Obtener los valores de los registros
void Kernel::ObtenerRegistros(short *reg)
{
	//Obtener registros
	__asm {
		mov reg[0], ax
			mov reg[1], bx
			mov reg[2], cx
			mov reg[3], dx
			mov reg[4], si
			mov reg[5], di
			mov reg[6], sp
			mov reg[7], bp
			mov reg[8], ds
			mov reg[9], cs
			mov reg[10], ss
			mov reg[11], es
	}
}

void Kernel::EjecutarSistemaOperativo(int(*cb1)(int), int(*cb2)(int), int(*cb3)(int))
{
	
	ClassB::SetCB3(cb3);
	Kernel *Core = new Kernel();
	system("cls");
	
	short reg[12];
	//PCB1
	ObtenerRegistros(reg);
	SolicitarRegistro(new PCB((int*)cb1, NUEVO, reg));
	//PCB2
	ObtenerRegistros(reg);
	SolicitarRegistro(new PCB((int*)cb2, NUEVO, reg));
	//PCB3
	ObtenerRegistros(reg);
	SolicitarRegistro(new PCB((int*)cb3, NUEVO, reg));

	cout << endl;
	cout << "Presione una tecla para ejecutar los procesos..." << endl;
	getchar();
	system("cls");
	EjecutarProcesos();
}
