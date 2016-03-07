#include "stdafx.h"
#include "Kernel.h"

PCB::PCB(int status, LPTHREAD_START_ROUTINE function, LPVOID param)
{
	this->status = status;
	this->handle = CreateThread(NULL, 0, function, param, 0, 0);
	changeStatus(status);
	for (int i = 0; i < REGS_SIZE; i++)
		this->memory[i] = 0;
}

PCB::~PCB()
{
	this->status = 0;
	TerminateProcess(handle, 0);
	for (int i = 0; i < REGS_SIZE; i++)
		this->memory[i] = 0;
}

int PCB::getId()
{
	return GetThreadId(handle);
}

int PCB::suspend()
{
	int *aux = this->memory;
	//_asm
	//{
	////	PUSHFD;
	////	PUSHAD;
	////	MOV EAX, aux;
	////	/*MOV[EAX], CS;
	////	ADD EAX, 4;*/
	////	MOV[EAX], DS;
	////	ADD EAX, 4;
	////	MOV[EAX], ES;
	////	ADD EAX, 4;
	////	MOV[EAX], SS;
	////	ADD EAX, 4;
	////	MOV ECX, REGS_NUM;
	////beginLoop:
	////	POP[EAX];
	////	ADD EAX, 2;
	////	POP[EAX];
	////	ADD EAX, 2;
	////	LOOP beginLoop;
	//	PUSH EAX;
	//	MOV EAX, aux;
	//	MOV[EAX], EBX;
	//	ADD EAX, 4;
	//	MOV[EAX], ECX;
	//	ADD EAX, 4;
	//	MOV[EAX], EDX;
	//	ADD EAX, 4;
	//	POP[EAX];
	//}
	changeStatus(SUSPENDED);
	return SUCCESSFUL;
}

int PCB::suspend(int status)
{
	int *aux = this->memory;
	//_asm
	//{
	////	PUSHFD;
	////	PUSHAD;
	////	MOV EAX, aux;
	////	/*MOV[EAX], CS;
	////	ADD EAX, 4;*/
	////	MOV[EAX], DS;
	////	ADD EAX, 4;
	////	MOV[EAX], ES;
	////	ADD EAX, 4;
	////	MOV[EAX], SS;
	////	ADD EAX, 4;
	////	MOV ECX, REGS_NUM;
	////beginLoop:
	////	POP[EAX];
	////	ADD EAX, 2;
	////	POP[EAX];
	////	ADD EAX, 2;
	////	LOOP beginLoop;
	//	PUSH EAX;
	//	MOV EAX, aux;
	//	MOV[EAX], EBX;
	//	ADD EAX, 4;
	//	MOV[EAX], ECX;
	//	ADD EAX, 4;
	//	MOV[EAX], EDX;
	//	ADD EAX, 4;
	//	POP[EAX];
	//}
	changeStatus(status);
	return SUCCESSFUL;
}

int PCB::resume()
{
	int *aux = this->memory;
	int begin = (REGS_NUM + EXTRA_REGS) * sizeof(int);
	//__asm
	//{
	////	MOV EAX, aux;
	////	ADD EAX, begin;
	////	MOV ECX, REGS_NUM + 1;
	////	/*PUSH ESP;
	////	PUSH ESI;
	////	PUSH EDI;
	////	PUSH EBP;*/
	////loopBegin:
	////	PUSH[EAX];
	////	SUB EAX, 4;
	////	LOOP loopBegin;
	////	POPAD;
	////	POPFD;
	////	/*POP EBP;
	////	POP EDI;
	////	POP ESI;
	////	POP ESP;*/
	////	PUSH EAX;
	////	/*MOV EBP, EDI;*/
	////	MOV EAX, aux;
	////	ADD EAX, 4;
	////	MOV[EAX], SS;
	////	ADD EAX, 4;
	////	MOV[EAX], ES;
	////	ADD EAX, 4;
	////	MOV[EAX], DS;
	////	POP EAX;
	//	MOV EAX, aux;
	//	MOV EBX, [EAX];
	//	ADD EAX, 4;
	//	MOV ECX, [EAX];
	//	ADD EAX, 4;
	//	MOV EDX, [EAX];
	//	ADD EAX, 4;
	//	MOV EAX, [EAX];
	//}
	changeStatus(RUNNING);
	return SUCCESSFUL;
}

void PCB::changeStatus(int status)
{
	int previousStatus = this->status;
	this->status = status;
	switch (status)
	{
	case BLOCKED:
	case READY:
	case SUSPENDED:
	case WAITING:
	case READY_AND_SUSPENDED:
	case BLOCKED_AND_SUSPENDED:
	case NEW_PROCESS:
		SuspendThread(handle);
		break;
	case RUNNING:
		ResumeThread(handle);
		break;
	case DONE:
		TerminateThread(handle, 0);
		break;
	default:
		cout << "Estado: " << status << " no reconocido. Estado no actualizado\n";
		this->status = previousStatus;
		break;
	}
}

int PCB::admit()
{
	for (int i = 0; i < REGS_SIZE; i++)
		this->memory[i] = 0;
	ResumeThread(handle);
	this->status = RUNNING;
	return SUCCESSFUL;
}

Kernel::Kernel()
{
	this->count = this->currentPCB = 0;
	for (int i = 0; i < MAX; i++)
		this->pcb[i] = NULL;
}

Kernel::~Kernel()
{
	for (int i = 0; i < MAX; i++)
		if (pcb[i] != NULL)
		{
			killProcessAt(i);
			pcb[i] = NULL;
		}
	this->count = 0;
}

int Kernel::validateNewProcess(int index)
{
	if (index >= MAX || index < 0)
		return OUT_OF_RANGE;
	if (this->pcb[index] != NULL)
	{
		if (this->pcb[index]->status != DONE)
			return UNAVAILABLE;
		else
			killProcessAt(index);
	}
	if (count >= MAX)
		return OUT_OF_SPACE;
	return SUCCESSFUL;
}

void Kernel::runProcess(PCB *pcb)
{
	cout << "Proceso iniciado con id: " << pcb->getId() << "\n";
	pcb->resume();
}

int Kernel::validateProccess(PCB *current)
{
	if (current == NULL)
		return PROCESS_IS_NULL;
	if (current->status == DONE)
		return PROCESS_IS_DONE;
	return SUCCESSFUL;
}

int Kernel::firstAvailableIndex()
{
	int i = 0;
	while (i < MAX)
	{
		if (this->pcb[i] == NULL)
			return i;
		else if (this->pcb[i]->status == DONE)
		{
			killProcessAt(i);
			return i;
		}
		i++;
	}
	return -1;
}

PCB *Kernel::getProcessById(int id)
{
	for (int i = 0; i < MAX; i++)
		if (pcb[i] != NULL && pcb[i]->getId() == id)
			return pcb[i];
	return NULL;
}

int Kernel::getProcessIndex(int id)
{
	for (int i = 0; i < MAX; i++)
		if (pcb[i] != NULL && pcb[i]->getId() == id)
			return i;
	return -1;
}

int Kernel::addProcess(LPTHREAD_START_ROUTINE function, LPVOID param)
{
	int index = firstAvailableIndex();
	return addProcess(function, param, index);
}

int Kernel::addProcess(LPTHREAD_START_ROUTINE function, LPVOID param, int index)
{
	int result = validateNewProcess(index);
	if (result != SUCCESSFUL)
		return result;
	PCB *pcb = new PCB(NEW_PROCESS, function, param);
	this->pcb[index] = pcb;
	count++;
	return SUCCESSFUL;
}

int Kernel::runProcessAt(int index)
{
	if (index >= MAX || index < 0)
		return OUT_OF_RANGE;
	PCB *current = this->pcb[index];
	int result = validateProccess(current);
	if (result != SUCCESSFUL)
		return result;
	runProcess(current);
	current->status = RUNNING;
	return SUCCESSFUL;
}

int Kernel::runProcessById(int id)
{
	PCB *current = getProcessById(id);
	int result = validateProccess(current);
	if (result != SUCCESSFUL)
		return result;
	runProcess(current);
	return SUCCESSFUL;
}

PCB *Kernel::getCurrentPCB()
{
	return pcb[currentPCB];
}

int Kernel::nextPCB()
{
	return currentPCB = (currentPCB + 1) % MAX;
}

DWORD WINAPI kernelProcess(LPVOID param)
{
	Kernel *k = (Kernel*)param;
	int i = 0;
	while (!GetAsyncKeyState('F'))
	{
		if (k->pcb[i] != NULL)
			switch (k->pcb[i]->status)
			{
			case RUNNING:
				if (QUANTUM <= k->timer.elapsedTime())
				{
					printf("0 - Kernel\n");
					k->pcb[i]->suspend(READY);
					i = (i + 1) % MAX;
				}
				break;
			case SUSPENDED:
			case READY:
				k->pcb[i]->resume();
				k->timer.start();
				break;
			case DONE:
				k->killProcessAt(i);
				break;
			case NEW_PROCESS:
				k->pcb[i]->admit();
				k->timer.start();
				break;
			}
		else
			i = (i + 1) % MAX;
	}
	return 0;
}

void CALLBACK timerRoutine(PVOID lpParam, BOOLEAN timerOrWaitFired)
{
	if (NULL != lpParam)
	{
		Kernel *kernel = (Kernel*)lpParam;
		printf("0 - Kernel\n");
		PCB *pcb = kernel->getCurrentPCB();
		if (pcb != NULL && pcb->status == RUNNING)
		{
			pcb->suspend();
			kernel->nextPCB();
		}
		else
		{
			kernel->nextPCB();
		}
		
		SetEvent(kernel->gDoneEvent);
	}
}

int Kernel::runAllProcesses()
{
	//HANDLE handle = CreateThread(NULL, 0, kernelProcess, this, 0, 0);
	//WaitForSingleObject(handle, 0);
	while (!GetAsyncKeyState('F'))
	{
		PCB *pcb = getCurrentPCB();
		if (NULL != pcb)
		{
			switch (pcb->status)
			{
			case SUSPENDED:
			case READY:
				pcb->resume();
				createTimer();
				break;
			case DONE:
				this->killProcessAt(currentPCB);
				break;
			case NEW_PROCESS:
				pcb->admit();
				createTimer();
				break;
			default:
				break;
			}
		}
		else
		{
			this->nextPCB();
		}
	}
	//system("pause >nul");
	return SUCCESSFUL;
}

void Kernel::createTimer()
{
	HANDLE hTimer = NULL;
	HANDLE hTimerQueue = NULL;

	gDoneEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	hTimerQueue = CreateTimerQueue();

	CreateTimerQueueTimer(&hTimer, hTimerQueue, 
		(WAITORTIMERCALLBACK)timerRoutine, this, QUANTUM, 0, 0);

	WaitForSingleObject(gDoneEvent, INFINITE);

	CloseHandle(gDoneEvent);

	DeleteTimerQueue(hTimerQueue);
}

int Kernel::killProcessAt(int index)
{
	if (index >= MAX || index < 0)
		return OUT_OF_RANGE;
	if (this->pcb[index] == NULL)
		return PROCESS_IS_NULL;
	count--;
	this->pcb[index]->~PCB();
	this->pcb[index] = NULL;
	return SUCCESSFUL;
}

int Kernel::killProcessById(int id)
{
	int index = getProcessIndex(id);
	if (index < 0)
		return PROCESS_NOT_FOUND;
	killProcessAt(index);
	return SUCCESSFUL;
}

Kernel &Kernel::operator+=(const LPTHREAD_START_ROUTINE &function)
{
	this->pcb[count++] = new PCB(NEW_PROCESS, function, NULL);
	return *this;
}



