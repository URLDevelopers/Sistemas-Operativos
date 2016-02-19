// Proyecto2SistemasOperativosGrupo5.cpp : Defines the entry point for the console application.
//



#include "stdafx.h"
#include "conio.h"
#include <iostream>
using namespace std;



//PROYECTO 1. CALLBACKS

static int funcion1(int param)
{
	//Funcion 1 definida como estatica para todo el programa.
	cout << "Parametro: " << param << "\n";
	cout << "Funcion: " << 1 << "\n";
	return 1;
}

class ClaseA
{
	//Clase A. Para la función 2.
public:
	static int funcion2(int param);
};

int ClaseA::funcion2(int param)
{
	//Funcion 2 definida como estatica de la Clase A.
	cout << "Parametro: " << param << "\n";
	cout << "Funcion: " << 2 << "\n";
	return 2;
}

class ClaseB
{
	//clase B, para la función 3
public:
	static void setCallBackClaseB(int (ClaseB::*&callbackFunClasB)(int));
private:
	int funcion3(int param);
};

int ClaseB::funcion3(int param)
{
	//Funcion 3 definida como privada de la Clase B
	cout << "Parametro: " << param << "\n";
	cout << "Funcion: " << 3 << "\n";
	return 3;
}

void ClaseB::setCallBackClaseB(int (ClaseB::*&callbackFunClasB)(int))
{
	callbackFunClasB = &ClaseB::funcion3;
}

typedef int(*CallBack)(int);
typedef int(ClaseB::*CallBackB)(int);









//PROYECTO2. PCB


//Definición de identificadores, asociados a los diferentes estados de los procesos, posibles casos, y a la cantidad máxima de los mismos.
#define MAX 10 //La cantidad maxima de procesos
#define ESTADO_RUN 1 
#define READY 2 
#define DONE 3
#define SUCCESSFUL 0 //Resultado exitoso 

#define UNAVAILABLE 1 //Posicion no disponible para agregar al proceso
#define OVERFLOW 2 //La cantidad de procesos agregados ha sido alcanzada
#define OUT_OF_RANGE 3 //El indice para agregar ha sido sobrepasado

#define PROCESS_IS_NULL 1 //No hay proceso en esa posicion
#define PROCESS_IS_DONE 2 //El proceso ha sido terminado y desea ejecutarse
#define PROCESS_NOT_FOUND 3 //El proceso no ha sido encontrado

class PCB
{
private:
	int id; //Identificador de proceso
public:
	int status, *funcion; //status: Estado del proceso; *funcion: Puntero a la funcion que debe ejecutar
	ClaseB *obj;//Objeto a utilizar en caso de que la funcion no sea estatica

	PCB(int id, int status, int *callback)
	{
		this->id = id;
		this->status = status;
		this->funcion = callback;
		this->obj = NULL;
	}

	PCB(int id, int status, int *callback, ClaseB *obj)
	{
		this->id = id;
		this->status = status;
		this->funcion = callback;
		this->obj = obj;
	}

	~PCB()
	{
		this->id = this->status = 0;
		this->funcion = NULL;
		if (this->obj != NULL)
		{ //TODO: Agregar el destructor de obj, si es necesario
			this->obj = NULL;
		}
	}

	int getId()
	{
		return this->id;
	}
};

//Kernel que lleva la tabla de procesos
class Kernel
{
private:
	//Contador de identificadores
	int id_ContProcesos;

	//Valida si un proceso nuevo puede ser agregado en la posicion
	int NuevoProceso(int IDProceso)
	{
		if (IDProceso >= MAX || IDProceso < 0)
			return OUT_OF_RANGE;
		if (this->pcb[IDProceso] != NULL)
		{
			if (this->pcb[IDProceso]->status != DONE)
				return UNAVAILABLE;
			else
				EliminarID(IDProceso);
		}
		if (ContProcesos >= MAX)
			return OVERFLOW;
		return SUCCESSFUL;
	}

	//Corre un proceso al recibir el PCB
	static void runProceso(PCB *pcb)
	{
		int result;
		int *funcion = pcb->funcion;
		pcb->status = ESTADO_RUN;
		if (pcb->obj != NULL)
		{
			CallBackB *cb = (CallBackB*)(funcion);
			result = (pcb->obj->**cb)(1);
			int REGeax = 0, REGebx = 0, REGecx = 0, REGedx = 0;//Registros de propósito general
			int REGesi = 0, REGedi = 0; //Registros índices o punteros
			int REGesp = 0, REGebp = 0; //Registros para la pila
			int REGecs = 0, REGeds = 0, REGees = 0, REGess = 0; //Registros de segmentos de datos
			_asm {
				mov REGeax, eax;
				mov REGebx, ebx;
				mov REGecx, ecx;
				mov REGedx, edx;//Registros de propósito general

				mov REGesi, esi;
				mov REGedi, edi; //Registros punteros o índices

				mov REGebp, ebp;
				mov REGesp, esp; //Registros de pila
			}

			cout << "EAX " << REGeax << "\n";
			cout << "EBX " << REGebx << "\n";
			cout << "ECX " << REGecx << "\n";
			cout << "EDX " << REGedx << "\n\n";
			cout << "ESI " << REGesi << "\n";
			cout << "EDI " << REGedi << "\n\n";
			cout << "EBP " << REGebp << "\n";
			cout << "ESP " << REGesp << "\n\n";
		}
		else
		{
			CallBack cb = (CallBack)*(&funcion);
			result = cb(0);int REGeax, REGebx, REGecx, REGedx;//Registros de propósito general
			
			int REGesi, REGedi; //Registros índices o punteros
			int REGesp, REGebp; //Registros para la pila
			int REGecs, REGeds, REGees, REGess; //Registros de segmentos de datos
			_asm {
				mov REGeax, eax;
				mov REGebx, ebx;
				mov REGecx, ecx;
				mov REGedx, edx;//Registros de propósito general

				mov REGesi, esi;
				mov REGedi, edi; //Registros punteros o índices

				mov REGebp, ebp;
				mov REGesp, esp; //Registros de pila
			}

			cout << "EAX " << REGeax << "\n";
			cout << "EBX " << REGebx << "\n";
			cout << "ECX " << REGecx << "\n";
			cout << "EDX " << REGedx << "\n\n";
			cout << "ESI " << REGesi << "\n";
			cout << "EDI " << REGedi << "\n\n";
			cout << "EBP " << REGebp << "\n";
			cout << "ESP " << REGesp << "\n\n";
		}
		pcb->status = DONE;


		cout << "Id " << pcb->getId() << " del Proceso Terminado\nFuncion ejecutada y finalizada: " << result << "\n\n";
	}

	//Valida si un proceso puede ser ejecutado
	static int ValidarProceso(PCB *current)
	{
		if (current == NULL)
			return PROCESS_IS_NULL;
		if (current->status == DONE)
			return PROCESS_IS_DONE;
		return SUCCESSFUL;
	}

	//Retorna el primer indice disponible para almacenar un nuevo proceso en PCB
	int IDProcesoDisponible()
	{
		int i = 0;
		while (i < MAX)
		{
			if (this->pcb[i] == NULL)
				return i;
			else if (this->pcb[i]->status == DONE)
			{
				EliminarID(i);
				return i;
			}
			i++;
		}
		return -1;
	}


	
public:
	//Tabla de Control de Procesos
	PCB *pcb[MAX];
	int ContProcesos;

	Kernel()
	{
		this->ContProcesos = this->id_ContProcesos = 0;
		for (int i = 0; i < MAX; i++)
			this->pcb[i] = NULL;
	}

	~Kernel()
	{
		for (int i = 0; i < MAX; i++)
			if (pcb[i] != NULL)
			{
				EliminarID(i);
				pcb[i] = NULL;
			}
		this->ContProcesos = 0;
	}

	//Agrega un proceso a la Tabla de Control de Procesos en la ultima posicion disponible
	int AgregarProceso(int *callback)
	{
		int result = NuevoProceso(ContProcesos);
		if (result != SUCCESSFUL)
			return result;
		PCB *pcb = new PCB(id_ContProcesos++, READY, callback);
		int IDProceso = IDProcesoDisponible();
		this->pcb[IDProceso] = pcb;
		ContProcesos++;
		return SUCCESSFUL;
	}

	
	//Agrega un proceso a la Tabla de Control de Procesos en la ultima posicion disponible
	int AgregarProceso(int *callback, ClaseB *obj)
	{
		int result = NuevoProceso(ContProcesos);
		if (result != SUCCESSFUL)
			return result;
		PCB *pcb = new PCB(id_ContProcesos++, READY, callback, obj);
		int IDProceso = IDProcesoDisponible();
		this->pcb[IDProceso] = pcb;
		ContProcesos++;
		return SUCCESSFUL;
	}

	
	//Ejecuta el proceso, según su ID
	int RunProceso(int IDProceso)
	{
		PCB *current = this->pcb[IDProceso];
		int result = ValidarProceso(current);
		if (result != SUCCESSFUL)
			return result;
		runProceso(current);
		


		return SUCCESSFUL;
	}

	
	//Ejecuta todos los procesos y los cierra en la Tabla de Control de Procesos
	int RunAll()
	{
		for (int i = 0; i < MAX; i++)
		{
			RunProceso(i);
			EliminarID(i);
		}
		return SUCCESSFUL;
	}

	//Elimina un proceso en el indice indicado
	int EliminarID(int IDproceso)
	{
		if (IDproceso >= MAX || IDproceso < 0)
			return OUT_OF_RANGE;
		if (this->pcb[IDproceso] == NULL)
			return PROCESS_IS_NULL;
		ContProcesos--;
		this->pcb[IDproceso]->~PCB();
		this->pcb[IDproceso] = NULL;
		return SUCCESSFUL;
	}

	



};

int main()
{
	Kernel *kernel = new Kernel();
	kernel->AgregarProceso((int*)&funcion1);
	kernel->AgregarProceso((int*)&ClaseA::funcion2);
	CallBackB cb;
	ClaseB::setCallBackClaseB(cb);
	ClaseB *obj = new ClaseB();
	kernel->AgregarProceso((int*)&cb, obj);

	kernel->RunAll();
	int contador = 100;
	
	while (contador>0)
	{
		contador++;
		system("pause>nul");
		kernel->~Kernel();
		
	}
	
	return 0;
}