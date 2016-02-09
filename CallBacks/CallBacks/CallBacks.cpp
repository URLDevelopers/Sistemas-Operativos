// CallBacks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

/**************************
* DEFINICION DE CALLBACKS *
*     (PROYECTO 1)        *
**************************/

static int function1(int param)
{
	cout << "Parametro: " << param << "\n";
	cout << "Funcion: " << 1 << "\n";
	return 1;
}

class ClassA
{
public:
	static int function2(int param);
};

int ClassA::function2(int param)
{
	cout << "Parametro: " << param << "\n";
	cout << "Funcion: " << 2 << "\n";
	return 2;
}

class ClassB
{
public:
	static void setCallBack(int (ClassB::*&cb)(int));
private:
	int function3(int param);
};

int ClassB::function3(int param)
{
	cout << "Parametro: " << param << "\n";
	cout << "Funcion: " << 3 << "\n";
	return 3;
}

void ClassB::setCallBack(int (ClassB::*&cb)(int))
{
	cb = &ClassB::function3;
}

typedef int(*CallBack)(int);
typedef int(ClassB::*CallBackB)(int);

/*****************************
* DEFINICION DE KERNEL Y PCB *
*        (PROYECTO 2)        *
*****************************/

#define MAX 10 //La cantidad maxima de procesos

//DEFINICION DE CONSTANTES PARA ESTADOS DEL PROCESO
//NOTA: No todas las constantes se utilizan por ahora
#define RUNNING 1 //El proceso se esta ejecutando
#define BLOCKED 2 //El proceso se encuentra bloqueado
#define READY 3 //El proceso se encuentra listo para su ejecucion
#define SUSPENDED 4 //El proceso se ha suspendido
#define WAITING 5
#define DONE 6
#define READY_AND_SUSPENDED (READY | SUSPENDED) //Listo y suspendido
#define BLOCKED_AND_SUSPENDED ((BLOCKED | SUSPENDED) + 2) //Bloqueado y suspendido

#define SUCCESSFUL 0 //Resultado exitoso ->UTILIZADA EN TODAS LAS FUNCIONES<-

//DEFINICION DE CONSTANTES DEL RESULTADO DE AGREGAR UN PROCESO
#define UNAVAILABLE 1 //Posicion no disponible para agregar al proceso
#define OVERFLOW 2 //La cantidad de procesos agregados ha sido alcanzada
#define OUT_OF_RANGE 3 //El indice para agregar ha sido sobrepasado

//DEFINICION DE CONSTANTES DEL RESULTADO DE CORRER UN PROCESO
//TODO: Pueden existir mas casos, revisar. Quizas sea mejor retornar el valor de status en el pcb
#define PROCESS_IS_NULL 1 //No hay proceso en esa posicion
#define PROCESS_IS_DONE 2 //El proceso ha sido terminado y desea ejecutarse
#define PROCESS_NOT_FOUND 3 //El proceso no ha sido encontrado

//TODO: Es probable que se necesite hacer un template con la clase PCB
///<summary>Process Control Block <para>Registra la informacion de un proceso</para></summary>
class PCB
{
private:
	///<summary>Representa el identificador de proceso</summary>
	int id;
public:
	///<summary>status: Estado del proceso <para>*function: Puntero a la funcion que debe ejecutar</para></summary>
	int status, *function;
	///<summary>Objeto a utilizar en caso de que la funcion no sea estatica</summary>
	ClassB *obj;

	///<summary><param name = "id">Identificador de proceso</param>
	///<param name = "status">Estado con el que se inicializa el proceso</param>
	///<param name = "callback">puntero a la funcion</param></summary>
	PCB(int id, int status, int *callback)
	{
		this->id = id;
		this->status = status;
		this->function = callback;
		this->obj = NULL;
	}

	///<summary><param name = "id">Identificador de proceso</param>
	///<param name = "status">Estado con el que se inicializa el proceso</param>
	///<param name = "callback">puntero a la funcion</param>
	///<param name = "obj">Objeto inicializado para una funcion no estatica</param></summary>
	PCB(int id, int status, int *callback, ClassB *obj)
	{
		this->id = id;
		this->status = status;
		this->function = callback;
		this->obj = obj;
	}

	~PCB()
	{
		this->id = this->status = 0;
		this->function = NULL;
		if (this->obj != NULL)
		{ //TODO: Agregar el destructor de obj, si es necesario
			this->obj = NULL;
		}
	}

	///<summary>Retorna el id del PCB</summary>
	int getId()
	{
		return this->id;
	}
};

///<summary>Kernel que lleva la tabla de procesos</summary>
class Kernel
{
private:
	///<summary>Contador de identificadores</summary>
	int id_count;	

	///<summary>Valida si un proceso nuevo puede ser agregado en la posicion
	///</param name = "index">Indice en que se quiere insertar el proceso</param>
	///<para><returns>Entero que inidica el resultado</returns></para></summary>
	int validateNewProcess(int index)
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
			return OVERFLOW;
		return SUCCESSFUL;
	}

	///<summary>Corre un proceso al recibir el PCB
	///<param name = "pcb">Puntero al Bloque de Control de Proceso</param></summary>
	static void runProcess(PCB *pcb)
	{
		int result;
		int *function = pcb->function;
		pcb->status = RUNNING;
		if (pcb->obj != NULL)
		{
			CallBackB *cb = (CallBackB*)(function);
			result = (pcb->obj->**cb)(6);
		}
		else
		{
			CallBack cb = (CallBack)*(&function);
			result = cb(7);
		}
		pcb->status = DONE;
		cout << "Proceso terminado\nId de Proceso: " << pcb->getId() << "\nValor de Retorno: " << result << "\n\n";
	}

	///<summary>Valida si un proceso puede ser ejecutado
	///<param name = "current">PCB con el proceso a validar</param>
	///<para><returns>Retorna el entero del resultado validado</returns></para></summary>
	static int validateProccess(PCB *current)
	{
		if (current == NULL)
			return PROCESS_IS_NULL;
		if (current->status == DONE)
			return PROCESS_IS_DONE;
		return SUCCESSFUL;
	}

	///<summary>Retorna el primer indice disponible para almacenar un nuevo PCB
	///<para><returns>Si el resultado es -1, no hay indices dentro del arreglo</returns></para></summary>
	int firstAvailableIndex()
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

	///<summary>Busca el PCB segun su id
	///<param name = "id">Identificador de proceso</param>
	///<para><returns>Retorna el PCB (NULL indica que no lo hizo)</returns></para></summary>
	PCB *getProcessById(int id)
	{
		for (int i = 0; i < MAX; i++)
			if (pcb[i] != NULL && pcb[i]->getId() == id)
				return pcb[i];
		return NULL;
	}

	///<summary>Retorna el indice del proceso segun su id
	///<param name = "id">El identificador del proceso a retornar</param>
	///<para><returns>Si el resultado es -1, el proceso con dicho identificador no se encuentra en la tabla</retruns></para></summary>
	int getProcessIndex(int id)
	{
		for (int i = 0; i < MAX; i++)
			if (pcb[i] != NULL && pcb[i]->getId() == id)
				return i;
		return -1;
	}
public:
	///<summary>Tabla de Control de Procesos<para>El tamaño se indica segun el valor de MAX
	///<seealso>#define MAX 10</seealso></para></summary>
	PCB *pcb[MAX];
	///<summary>Contador de procesos</summary>
	int count;

	Kernel()
	{
		this->count = this->id_count = 0;
		for (int i = 0; i < MAX; i++)
			this->pcb[i] = NULL;
	}

	~Kernel()
	{
		for (int i = 0; i < MAX; i++)
			if (pcb[i] != NULL)
			{
				killProcessAt(i);
				pcb[i] = NULL;
			}
		this->count = 0;
	}

	///<summary>Agrega un proceso a la Tabla de Control de Procesos en la ultima posicion disponible
	///<param name = "callback">Puntero a la funcion a agregar</param>
	///<para><returns>Retorna el resultado de agregar el proceso</returns></para><para>
	///<seealso>Kernel::validateNewProcess</seealso></para></summary>
	int addProcess(int *callback)
	{
		int result = validateNewProcess(count);
		if (result != SUCCESSFUL)
			return result;
		PCB *pcb = new PCB(id_count++, READY, callback);
		int index = firstAvailableIndex();
		this->pcb[index] = pcb;
		count++;
		return SUCCESSFUL;
	}

	///<summary>Agrega un proceso a la Tabla de Control de Procesos en el indice establecido
	///<param name = "callback">Puntero a la funcion a agregar</param>
	///<param name = "index">Indice en el que se desea insertar el proceso</param>
	///<para><returns>Retorna el resultado de agregar el proceso</returns></para><para>
	///<seealso>Kernel::validateNewProcess</seealso></para></summary>
	int addProcess(int *callback, int index)
	{
		int result = validateNewProcess(index);
		if (result != SUCCESSFUL)
			return result;
		PCB *pcb = new PCB(id_count++, READY, callback);
		this->pcb[index] = pcb;
		count++;
		return SUCCESSFUL;
	}

	///<summary>Agrega un proceso (no estatico) a la Tabla de Control de Procesos en la ultima posicion disponible
	///<param name = "callback">Puntero a la funcion a agregar</param>
	///<param name = "obj">Objeto inicializado para llamar a la funcion</param>
	///<para><returns>Retorna el resultado de agregar el proceso</returns></para><para>
	///<seealso>Kernel::validateNewProcess</seealso></para></summary>
	int addProcess(int *callback, ClassB *obj)
	{
		int result = validateNewProcess(count);
		if (result != SUCCESSFUL)
			return result;
		PCB *pcb = new PCB(id_count++, READY, callback, obj);
		int index = firstAvailableIndex();
		this->pcb[index] = pcb;
		count++;
		return SUCCESSFUL;
	}

	///<summary>Agrega un proceso (no estatico) a la Tabla de Control de Procesos en la ultima posicion disponible
	///<param name = "callback">Puntero a la funcion a agregar</param>
	///<param name = "index">Indice en el que se desea insertar el proceso</param>
	///<param name = "obj">Objeto inicializado para llamar a la funcion</param>
	///<para><returns>Retorna el resultado de agregar el proceso</returns></para><para>
	///<seealso>Kernel::validateNewProcess</seealso></para></summary>
	int addProcess(int *callback, ClassB *obj, int index)
	{
		int result = validateNewProcess(index);
		if (result != SUCCESSFUL)
			return result;
		PCB *pcb = new PCB(id_count++, READY, callback, obj);
		this->pcb[index] = pcb;
		index++;
		return SUCCESSFUL;
	}

	///<summary>Ejecuta el proceso en el indice establecido
	///<param name = "index">Indice donde se encuentra el proceso</param></summary>
	///<para><returns>Resultado de la ejecucion del proceso</returns></para>
	int runProcessAt(int index)
	{
		PCB *current = this->pcb[index];
		int result = validateProccess(current);
		if (result != SUCCESSFUL)
			return result;
		runProcess(current);
		return SUCCESSFUL;
	}

	///<summary>Ejecuta el proceso en el indice establecido
	///<param name = "id">Id del proceso a ejecutar</param></summary>
	///<para><returns>Resultado de la ejecucion del proceso</returns></para>
	int runProcessById(int id)
	{
		PCB *current = getProcessById(id);
		int result = validateProccess(current);
		if (result != SUCCESSFUL)
			return result;
		runProcess(current);
		return SUCCESSFUL;
	}

	///<summary>Ejecuta todos los procesos en la Tabla de Control de Procesos
	///<para><returns>Resultado de la ejecucion de todos los procesos</returns></para>
	int runAllProcesses()
	{
		for (int i = 0; i < MAX; i++)
		{
			runProcessAt(i);
			killProcessAt(i);
		}
		return SUCCESSFUL;
	}

	///<summary>Elimina un proceso en el indice indicado
	///<param name = "index">El valor de la posicion a eliminar</param>
	///<para><returns>Retorna el resultado de eliminar el proceso</returns></para></summary>
	int killProcessAt(int index)
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

	///<summary>Elimina el proceso segun su id
	///<param name = "id">El identificador del proceso a eliminar</param>
	///<para><returns>Retorna el resultado de la eliminacion del proceso</returns></para></summary>
	int killProcessById(int id)
	{
		int index = getProcessIndex(id);
		if (index < 0)
			return PROCESS_NOT_FOUND;
		killProcessAt(index);
		return SUCCESSFUL;
	}
};

int main()
{
	system("color f0");
	Kernel *kernel = new Kernel();
	kernel->addProcess((int*)&function1);
	kernel->addProcess((int*)&ClassA::function2);
	CallBackB cb;
	ClassB::setCallBack(cb);
	ClassB *obj = new ClassB();
	kernel->addProcess((int*)&cb, obj);

	kernel->runAllProcesses();

	system("pause >nul");
	kernel->~Kernel();
	return 0;
}