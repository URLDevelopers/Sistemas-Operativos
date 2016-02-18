#pragma once
#include "PCB.h"
#include <stdlib.h>

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
	PCB *Table;

	int GetID();

	bool SolicitarRegistro(PCB *nuevo);
	
	bool LiberarRegistro(PCB *nuevo);

	void ActivarPCB(PCB *nodo);

	int PCBActivo;

	void EjecutarSistemaOperativo(int (*cb1)(int), int(*cb2)(int), int(*cb3)(int));

	void assembler();

private:

	int ID;

	int LongCol;
	





};

