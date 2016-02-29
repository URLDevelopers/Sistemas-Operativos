#pragma once
#include "PCB.h"
#include <stdlib.h>
#include <Windows.h>
class Kernel
{
	//Variables
#define LONG 10

	//Estados
#define NUEVO 1
#define ESPERA 2
#define EJECUCION 3
#define TERMINADO 4
#define DORMIDO 5
#define LIBRE 0

public:
	Kernel();
	~Kernel();

	//Tabla
	PCB *Head, *Tail;

	static int StaticFunction1();

	static int StaticFunction2();

	int GetID();

	bool SolicitarRegistro(PCB *nuevo);
	
	bool LiberarRegistro();

	void ActivarPCB();

	void EjecutarSistemaOperativo(int (*cb1)(int), int(*cb2)(int), int(*cb3)(int));
	
	void EjecutarProcesos();

private:

	int ID;
	int LongCol;
	
	





};

