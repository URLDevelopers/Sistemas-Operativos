#include "ObserverPattern.h"
#include <cstdlib>
#include <list>
#include <iostream>
#include <Windows.h>

using namespace std;

#pragma region Constant Definition

#define MAX 10 //La cantidad maxima de procesos

#define REGS_SIZE 12 //Tamaño de la memoria utilizada para simular al proceso

//DEFINICION DE CONSTANTES PARA ESTADOS DEL PROCESO
//NOTA: No todas las constantes se utilizan por ahora
#define RUNNING 1 //El proceso se esta ejecutando
#define BLOCKED 2 //El proceso se encuentra bloqueado
#define READY 3 //El proceso se encuentra listo para su ejecucion
#define SUSPENDED 4 //El proceso se ha suspendido
#define WAITING 5
#define DONE 6
#define NEW_PROCESS 7
#define READY_AND_SUSPENDED 8 //Listo y suspendido
#define BLOCKED_AND_SUSPENDED 9 //Bloqueado y suspendido

#define SUCCESSFUL 0 //Resultado exitoso ->UTILIZADA EN TODAS LAS FUNCIONES<-

//DEFINICION DE CONSTANTES DEL RESULTADO DE AGREGAR UN PROCESO
#define UNAVAILABLE 1 //Posicion no disponible para agregar al proceso
#define OUT_OF_SPACE 2 //La cantidad de procesos agregados ha sido alcanzada
#define OUT_OF_RANGE 3 //El indice para agregar ha sido sobrepasado

//DEFINICION DE CONSTANTES DEL RESULTADO DE CORRER UN PROCESO
//TODO: Pueden existir mas casos, revisar. Quizas sea mejor retornar el valor de status en el pcb
#define PROCESS_IS_NULL 1 //No hay proceso en esa posicion
#define PROCESS_IS_DONE 2 //El proceso ha sido terminado y desea ejecutarse
#define PROCESS_NOT_FOUND 3 //El proceso no ha sido encontrado

#define REGS_NUM 9
#define EXTRA_REGS 3
#define TOTAL_REGS (REGS_NUM + EXTRA_REGS);

#define QUANTUM 3000

#pragma endregion

#pragma once

#pragma region Classes Predefinition

class ExecutionBehavior;

class NewProcessBehavior;

class SuspendBehavior;

class DoneBehavior;

class RunningBehavior;

class PCB;

class Kernel;

#pragma endregion

///<summary>Interfaz -clase abstracta- del comportamiento de ejecucion (Ejecucion del automata de Estado Finito)</summary>
class ExecutionBehavior
{
protected:
	///<summary>Bloque de control de procesos al que pertenece el comportamiento</summary>
	PCB *pcb;
public:
	///<summary>Constructor</summary>
	ExecutionBehavior();

	///<summary>Destructor vitual</summary>
	virtual ~ExecutionBehavior() = 0;

	///<summary>Realiza el cambio de estado y manipula el proceso segun el estado</summary>
	virtual void execute() = 0;
};

///<summary>Comportamiento de Nuevo Proceso</summary>
class NewProcessBehavior : public ExecutionBehavior
{
public:
	///<summary>Constructor
	///<param name="pcb">Bloque de control de procesos al cual pertenece el identificador</param></summary>
	NewProcessBehavior(PCB *pcb);

	///<summary>Destructor no virtual</summary>
	~NewProcessBehavior();

	///<summary>Cambia el proceso a listo</summary>
	void execute();
};

///<summary>Comportamiento de Proceso Listo</summary>
class ReadyBehavior : public ExecutionBehavior
{
private:
	///<summary>Crea el temporizador para manipular el quantum de proceso</summary>
	void createTimer();
public:
	///<summary>Constructor
	///<param name="pcb">Bloque de control de procesos al cual pertenece el identificador</param></summary>
	ReadyBehavior(PCB *pcb);

	///<summary>Destructor no virtual</summary>
	~ReadyBehavior();

	///<summary>Cambia el proceso a En Ejecucion</summary>
	void execute();
};

///<summary>Comportamiento de Suspension de proceso</summary>
class SuspendBehavior : public ExecutionBehavior
{
public:
	///<summary>Constructor
	///<param name="pcb">Bloque de control de procesos al cual pertenece el identificador</param></summary>
	SuspendBehavior(PCB *pcb);

	///<summary>Destructor no virtual</summary>
	~SuspendBehavior();

	///<summary>Regresa al proceso a Listo</summary>
	void execute();
};

class DoneBehavior : public ExecutionBehavior
{
public:
	///<summary>Constructor
	///<param name="pcb">Bloque de control de procesos al cual pertenece el identificador</param></summary>
	DoneBehavior(PCB *pcb);

	///<summary>Destructor no virtual</summary>
	~DoneBehavior();

	///<summary>Termina el proceso (final del automata)</summary>
	void execute();
};

///<summary>Comportamiento de Proceso En Ejecucion</summary>
class RunningBehavior : public ExecutionBehavior
{
public:
	///<summary>Constructor
	///<param name="pcb">Bloque de control de procesos al cual pertenece el identificador</param></summary>
	RunningBehavior(PCB *pcb);

	///<summary>Destructor no virtual</summary>
	~RunningBehavior();

	///<summary>Cambia el proceso a Suspendido</summary>
	void execute();
};

///<summary>Bloque de Control de Proceso, implenta Observer</summary>
class PCB : public Observer
{
private:
	///<summary>Kernel al que pertenece el PCB</summary>
	Kernel *kernel;
	///<summary>Ejecutador de proceso</summary>
	ExecutionBehavior *executor;
public:
	///<summary>Describe el estadod de un proceso</summary>
	int status;
	///<summary>Registros de memoria</summary>
	int memory[REGS_SIZE];
	///<summary>Manejador de hilo</summary>
	HANDLE handle;
	///<summary>Manejador del Temporizador</summary>
	HANDLE gDoneEvent;

	///<summary>Constructor de PCB
	///<param name="function">Funcion que simula el proceso</param>
	///<param name="param">Parametro a enviar en la funcion</param>
	///<param name="kernel">Puntero al Kernel que contiene el PCB</param></summary>
	PCB(LPTHREAD_START_ROUTINE function, LPVOID param, Kernel *kernel);

	///<summary>Destructor</summary>
	~PCB();

	///<summary>Retorna el identificador de proceso</summary>
	int getId() const;

	///<summary>Hereda de Observer
	///<para>Mueve al siguiente estado el PCB</para></summary>
	void update();

	///<summary>Establece el comportamiento a ejecutar
	///<param name="executor">Estado del automata al que se quiere proceder en la siguiente iteracion</param></summary>
	void setExecutionBehavior(ExecutionBehavior *execution);

	///<summary>Retorna el kernel al cual pertenece el PCB</summary>
	Kernel *getKernel();

	///<summary>Operador '='<para>asigna un PCB a otro</para></summary>
	PCB &operator=(const PCB &pcb);

	///<summary>Operador '=='<para>Compara la igualdad entre dos PCB's</para></summary>
	int operator==(const PCB &pcb) const;

	///<summary>Operador de menor<para>Determina si el valor del PCB es menor a otro</para></summary>
	int operator<(const PCB &pcb) const;
};

class Kernel : public Subject
{
private:
	///<summary>Lista de observadores (PCB's)</summary>
	list<PCB*> *observers;
	///<summary>Iterador del PCB que contiene el proceso actual</summary>
	list<PCB*>::iterator current;
public:
	///<summary>Constructor no virtual</summary>
	Kernel();
	///<summary>Desctructor no virtual</summary>
	~Kernel();

	///<summary>Agrega un nuevo observador (debe ser un PCB)
	///<param name="observer">PCB a agregar</param></summary>
	void registerObserver(Observer &observer);

	///<summary>Elimina al observador (debe ser un PCB)
	///<param name="observer">PCB a remover</param></summary>
	void removeObserver(Observer &observer);

	///<summary>Norifica a los observadores desplazarse al siguiente estado de su automata (normalmente, solo al actual)</summary>
	void notifyObservers();

	///<summary>Ejecuta todos los procesos (asignando un tiempo de ejecucion a cada uno)
	///<para>Ver el macro de QUANTUM definido en Kernel.h para conocer el tiempo uniforme asignado a cada proceso</para></summary>
	void runAllProcesses();

	///<summary>El proceso actual se convierte en el siguiente</summary>
	void nextProcess();

	///<summary>Retorna el PCB que contiene al proceso actual</summary>
	PCB *currentProcess();
};

