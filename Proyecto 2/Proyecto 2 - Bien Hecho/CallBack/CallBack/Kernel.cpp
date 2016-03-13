#include "stdafx.h"
#include "Kernel.h"
#include <iostream>
#include "ClassA.h"
#include "ClassB.h"
#include <ctime>
#include "Timer.h"

using namespace std;

#define MOD_KERNEL 0
#define MOD_USER 1
#define QUANTUM 3000

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

//Funcion 1 Proyecto 3
int Kernel::StaticFunction0()
{
	Timer t;
	unsigned long quantum = QUANTUM;
	t.Start();
	while (true)
	{
		if (t.elapsedTime() >= quantum)
		{
			return 0;
		}
		cout << "0-Kernel" << endl;
	}
	return 0;
}

//Funcion 2 Proyecto 3
int Kernel::StaticFunction1()
{
	Timer t;
	unsigned long quantum = QUANTUM;
	t.Start();
	while (true)
	{
		if (t.elapsedTime() >= quantum)
		{
			return 0;
		}
		cout << "1-Fun1" << endl;
	}
	return 0;
}

//Funcion 3 Proyecto 3
int Kernel::StaticFunction2()
{
	Timer t;
	unsigned long quantum = QUANTUM;
	t.Start();
	while (true)
	{
		if (t.elapsedTime() >= quantum)
		{
			return 0;
		}
		cout << "2-Fun2" << endl;
	}
	return 0;
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
	cout << "El proceso " << id_aux << " se esta eliminando." << endl;
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
	cout << "El proceso " << id_aux << " se ha eliminando." << endl;
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
	}
}

void Kernel::EjecutarSistemaOperativo()
{
	short reg[12];
	int ip;

	//Proyecto 3
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
			mov eax, [esp]
			mov ip, eax
	}
	SolicitarRegistro(new PCB(this->GetID(), (int*)&StaticFunction0, NUEVO, reg, ip, MOD_KERNEL));
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
			mov eax, [esp]
			mov ip, eax
	}
	SolicitarRegistro(new PCB(this->GetID(), (int*)&StaticFunction1, NUEVO, reg, ip, MOD_USER));
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
			mov eax, [esp]
			mov ip, eax
	}
	SolicitarRegistro(new PCB(this->GetID(), (int*)&StaticFunction2, NUEVO, reg, ip, MOD_USER));

	cout << endl;
	EjecutarProcesos();
	this->EjecutarSistemaOperativo();
}
