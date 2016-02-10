#pragma once
#include "PCB.h"


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

	//Tabla de PCB
	PCB *Tabla[LONG];

	int GetID();

	bool SolicitarRegistro(PCB *nuevo);
	
	bool LiberarRegistro(int pos);
	
	bool LiberarRegistro(PCB *nuevo);

	void ActivarPCB(int pos);

	int PCBActivo;

private:

	int ID;

	




};

