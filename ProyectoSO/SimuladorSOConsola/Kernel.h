#include "PCB.h"
#include <stdlib.h>

class Kernel
{

#define SIZE 10

#define LIBRE 0
#define NUEVO 1
#define ESPERA 2
#define EJECUCION 3
#define TERMINADO 4
#define DORMIDO 5

public:
	Kernel();
	~Kernel();

	PCB *Table;
	int GetId();
	bool RegistrarPCB(PCB *nuevo);
	bool LiberarPCB(PCB *nuevo);
	void ActivarPCB(PCB *nodo);
	int PCBActivo;
	void EjecutarCore(int(*cb1)(int), int(*cb2)(int), int(*cb3)(int));
	void assembler();

private:

	int Id;
	int SizeCore;
};

