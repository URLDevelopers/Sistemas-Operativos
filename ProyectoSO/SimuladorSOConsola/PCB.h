#pragma once
#include <iostream>
#include <Windows.h>
#include <string.h>

using namespace std;

#define REGS_SIZE 12

class PCB
{
private:
	int Id;
	int status;
	void *proceso;
	PCB *Siguiente;
	PCB *Anterior;

public:
	PCB(int id, void *process, int status);

	~PCB();
	int GetId();

	void *GetProceso();

	int GetEstado();

	void SetEstado(int estado);

	void SetSiguiente(PCB *next);

	void SetAnterior(PCB *siguiente);

	PCB *GetSiguiente();

	PCB *GetAnterior();
};

