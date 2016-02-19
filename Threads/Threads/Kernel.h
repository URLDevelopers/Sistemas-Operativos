#include <Windows.h>
#include <iostream>
#include "Timer.h"

using namespace std;

#pragma once

#pragma region

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

#define QUANTUM 1

#pragma endregion

class PCB
{
private:
public:
	int status;
	int memory[REGS_SIZE];
	HANDLE handle;

	PCB(int status, LPTHREAD_START_ROUTINE function, LPVOID param);

	~PCB();

	int getId();

	int suspend();

	int suspend(int status);

	int resume();

	void changeStatus(int status);

	int admit();
};

class Kernel
{
private:

	///<summary>Valida si un proceso nuevo puede ser agregado en la posicion
	///</param name = "index">Indice en que se quiere insertar el proceso</param>
	///<para><returns>Entero que inidica el resultado</returns></para></summary>
	int validateNewProcess(int index);

	///<summary>Corre un proceso al recibir el PCB
	///<param name = "pcb">Puntero al Bloque de Control de Proceso</param></summary>
	static void runProcess(PCB *pcb);

	///<summary>Valida si un proceso puede ser ejecutado
	///<param name = "current">PCB con el proceso a validar</param>
	///<para><returns>Retorna el entero del resultado validado</returns></para></summary>
	static int validateProccess(PCB *current);

	///<summary>Retorna el primer indice disponible para almacenar un nuevo PCB
	///<para><returns>Si el resultado es -1, no hay indices dentro del arreglo</returns></para></summary>
	int firstAvailableIndex();

	///<summary>Busca el PCB segun su id
	///<param name = "id">Identificador de proceso</param>
	///<para><returns>Retorna el PCB (NULL indica que no lo hizo)</returns></para></summary>
	PCB *getProcessById(int id);

	///<summary>Retorna el indice del proceso segun su id
	///<param name = "id">El identificador del proceso a retornar</param>
	///<para><returns>Si el resultado es -1, el proceso con dicho identificador no se encuentra en la tabla</retruns></para></summary>
	int getProcessIndex(int id);

public:
	Timer timer;

	///<summary>Tabla de Control de Procesos<para>El tamaño se indica segun el valor de MAX
	///<seealso>#define MAX 10</seealso></para></summary>
	PCB *pcb[MAX];

	///<summary>Contador de procesos</summary>
	int count;

	Kernel();

	~Kernel();

	///<summary>Agrega un proceso a la Tabla de Control de Procesos en la ultima posicion disponible
	///<param name = "function">Puntero a la funcion a agregar</param>
	///<param name = "param">Parametro a utilizar dentro de la funcion</param>
	///<para><returns>Retorna el resultado de agregar el proceso</returns></para><para>
	///<seealso>Kernel::validateNewProcess</seealso></para></summary>
	int addProcess(LPTHREAD_START_ROUTINE function, LPVOID param);

	///<summary>Agrega un proceso a la Tabla de Control de Procesos en el indice establecido
	///<param name = "function">Puntero a la funcion a agregar</param>
	///<param name = "param">Parametro a utilizar dentro de la funcion</param>
	///<param name = "index">Indice en el que se desea insertar el proceso</param>
	///<para><returns>Retorna el resultado de agregar el proceso</returns></para><para>
	///<seealso>Kernel::validateNewProcess</seealso></para></summary>
	int addProcess(LPTHREAD_START_ROUTINE function, LPVOID param, int index);

	///<summary>Ejecuta el proceso en el indice establecido
	///<param name = "index">Indice donde se encuentra el proceso</param></summary>
	///<para><returns>Resultado de la ejecucion del proceso</returns></para>
	int runProcessAt(int index);

	///<summary>Ejecuta el proceso en el indice establecido
	///<param name = "id">Id del proceso a ejecutar</param></summary>
	///<para><returns>Resultado de la ejecucion del proceso</returns></para>
	int runProcessById(int id);

	///<summary>Ejecuta todos los procesos en la Tabla de Control de Procesos
	///<para><returns>Resultado de la ejecucion de todos los procesos</returns></para>
	int runAllProcesses(LPTHREAD_START_ROUTINE function, Kernel *kernel);

	///<summary>Elimina un proceso en el indice indicado
	///<param name = "index">El valor de la posicion a eliminar</param>
	///<para><returns>Retorna el resultado de eliminar el proceso</returns></para></summary>
	int killProcessAt(int index);

	///<summary>Elimina el proceso segun su id
	///<param name = "id">El identificador del proceso a eliminar</param>
	///<para><returns>Retorna el resultado de la eliminacion del proceso</returns></para></summary>
	int killProcessById(int id);
};

