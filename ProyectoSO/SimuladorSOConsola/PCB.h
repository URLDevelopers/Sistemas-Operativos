#include "RegistrosCPU.h"
#pragma once
class PCB
{
	enum Estado
	{
		nuevo = 1,
		enEjecucion = 2,
		enEspera = 3,
		preparado = 4,
		terminado =5
	};

public:
	PCB()
	{
		this->IdEstado = nuevo;
		
	}

	~PCB()
	{
	}

	int IdPCB;
	int IdEstado;
	int* ContadorPrograma;
	int* Proceso;
	PCB* Siguiente;
	double tiempoReal; 
	RegistrosCPU RegistrosCPU;
};

