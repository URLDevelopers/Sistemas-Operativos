#include "stdafx.h"
#include "ObserverKernel.h"

#pragma region Operaciones

///<summary>Funcion a llamar cuando el quantum de un proceso ha terminado
///<param name="lpParam">Parametro enviado en la funcion</param>
///<param name="timeOrWaitFired">Indica si el tiempo ha expirado</param></summary>
void CALLBACK timerRoutine(PVOID lpParam, BOOLEAN timerOrWaitFired)
{
	if (NULL != lpParam)
	{
		PCB *pcb = (PCB*)lpParam;
		Kernel *kernel = pcb->getKernel();
		printf("0 - Kernel\n");
		pcb->update();
		kernel->nextProcess();
		kernel->currentProcess()->update();
		SetEvent(pcb->gDoneEvent);
	}
}

#pragma endregion

#pragma region Comportamientos de Ejecucion

#pragma region ExecutionBehavior

ExecutionBehavior::ExecutionBehavior(){}

ExecutionBehavior::~ExecutionBehavior() {}

void ExecutionBehavior::execute() {}

#pragma endregion

#pragma region NewProcessBehavior

NewProcessBehavior::NewProcessBehavior(PCB *pcb)
{
	this->pcb = pcb;
}

NewProcessBehavior::~NewProcessBehavior() 
{
	this->pcb = NULL;
}

void NewProcessBehavior::execute()
{
	for (int i = 0; i < REGS_SIZE; i++)
	{
		this->pcb->memory[i] = 0;
	}
	this->pcb->status = READY;
	this->pcb->setExecutionBehavior(new ReadyBehavior(this->pcb));
}

#pragma endregion

#pragma region ReadyBehavior

ReadyBehavior::ReadyBehavior(PCB *pcb)
{
	this->pcb = pcb;
}

ReadyBehavior::~ReadyBehavior()
{
	this->pcb = NULL;
}

void ReadyBehavior::execute()
{
	ResumeThread(this->pcb->handle);
	this->pcb->setExecutionBehavior(new RunningBehavior(this->pcb));
	createTimer();
	this->pcb->status = RUNNING;
}

void ReadyBehavior::createTimer()
{
	HANDLE hTimer = NULL;
	HANDLE hTimerQueue = NULL;

	this->pcb->gDoneEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	hTimerQueue = CreateTimerQueue();

	CreateTimerQueueTimer(&hTimer, hTimerQueue,
		(WAITORTIMERCALLBACK)timerRoutine, this->pcb, QUANTUM, 0, 0);

	WaitForSingleObject(this->pcb->gDoneEvent, INFINITE);

	CloseHandle(this->pcb->gDoneEvent);

	DeleteTimerQueue(hTimerQueue);
}

#pragma endregion

#pragma region SuspendBehavior

SuspendBehavior::SuspendBehavior(PCB *pcb)
{
	this->pcb = pcb;
}

SuspendBehavior::~SuspendBehavior()
{
	this->pcb = NULL;
}

void SuspendBehavior::execute()
{
	ResumeThread(this->pcb->handle);
	this->pcb->status = READY;
	this->pcb->setExecutionBehavior(new ReadyBehavior(this->pcb));
}

#pragma endregion

#pragma region RunningBehavior

RunningBehavior::RunningBehavior(PCB *pcb)
{
	this->pcb = pcb;
}

RunningBehavior::~RunningBehavior()
{
	this->pcb = NULL;
}

void RunningBehavior::execute()
{
	SuspendThread(this->pcb->handle);
	this->pcb->status = READY;
	this->pcb->setExecutionBehavior(new SuspendBehavior(this->pcb));
}

#pragma endregion

#pragma region DoneBehavior

DoneBehavior::DoneBehavior(PCB *pcb)
{
	this->pcb = pcb;
}

DoneBehavior::~DoneBehavior()
{
	this->pcb = NULL;
}

void DoneBehavior::execute()
{
	TerminateThread(this->pcb->handle, 0);
	this->pcb->getKernel()->removeObserver(*(PCB*)this->pcb);
	this->pcb->status = DONE;
	this->pcb->setExecutionBehavior(NULL);
}

#pragma endregion

#pragma endregion

#pragma region PCB

PCB::PCB(LPTHREAD_START_ROUTINE function, LPVOID param, Kernel *kernel)
{
	this->kernel = kernel;
	handle = CreateThread(NULL, 0, function, param, 0, 0);
	SuspendThread(handle);
	this->executor = new NewProcessBehavior(this);
}

PCB::~PCB()
{

}

void PCB::update()
{
	if (this->executor != NULL)
		this->executor->execute();
}

void PCB::setExecutionBehavior(ExecutionBehavior *execution)
{
	this->executor = execution;
}

Kernel *PCB::getKernel()
{
	return this->kernel;
}

PCB &PCB::operator=(const PCB &pcb)
{
	this->status = pcb.status;
	for (int i = 0; i < REGS_SIZE; i++)
		this->memory[i] = pcb.memory[i];
	this->handle = handle;
	return *this;
}

int PCB::operator==(const PCB &pcb) const
{
	return this->getId() != pcb.getId() || this->status != pcb.status;
}

int PCB::operator<(const PCB &pcb) const
{
	return this->getId() < pcb.getId();
}

int PCB::getId() const
{
	return GetThreadId(this->handle);
}

#pragma endregion

#pragma region Kernel

Kernel::Kernel()
{
	this->observers = new list<PCB*>();
	this->current = this->observers->begin();
}

Kernel::~Kernel(){}

void Kernel::registerObserver(Observer &observer)
{
	PCB *pcb = (PCB*)&observer;
	this->observers->push_back(pcb);
}

void Kernel::removeObserver(Observer &observer)
{
	PCB *pcb = (PCB*)&observer;
	this->observers->remove(pcb);
}

void Kernel::notifyObservers()
{
	(*current)->update();
}

void Kernel::runAllProcesses()
{
	this->current = this->observers->begin();
	(*current)->update();
	while (!GetAsyncKeyState('F'))
	{
		PCB *pcb = currentProcess();
		if (pcb->status == READY)
			pcb->update();
		else
			nextProcess();
	}
}

void Kernel::nextProcess()
{
	current++;
	if (current == observers->end())
		current = observers->begin();
}

PCB *Kernel::currentProcess()
{
	return *current;
}

#pragma endregion