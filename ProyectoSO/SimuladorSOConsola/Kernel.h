#include "PCB.h"
#include "Thread.h"
//#include <stdlib.h>

#define SIZE 10

#define NEW_PROCESS 1
#define	READY 2
#define RUNNING	3
#define	BLOCKED 4
#define SUSPENDED 5
#define	DONE 6
#define QUANTUM 3

class Kernel
{
private:

	int ThreadID;
	int SizeTable;
	Thread Hilos;
	

public:
	PCB *HeadTable;
	PCB *TailTable;

	Kernel();
	~Kernel();

	bool RegistrarPCB(void *Function1);
	void RunCore();
	void ShutDown();

	int GetId();
	bool LiberarPCB(PCB *nuevo);

};

