// Programa1.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

//Define size
//
#define v_size 10 //Tamaño del vector

//Define Process Control States
#define s_running 0 //En ejecucion
#define s_suspended 1 //Suspendido
#define s_blocked 2 //Bloqueado
#define s_ready 3 //Listo para la ejecucion
#define s_ready_and_suspend  4 //Listo y suspendido
#define s_blocked_and_suspend 5 //Bloqueado y suspendido
#define s_waiting 6 //En espera
#define s_done 7 //Terminado

//Define CPU states
#define available 8 //Espacio dispobible
#define not_available 9 //Ya no hay espacio
#define out_of_range 10 //fuera del limite del espacio
#define s_delete 11 //Terminado

string ProcessName[12] = { "Corriendo","Suspendido","Bloqueado", "Listo","Listo y Suspendido","Bloqueado y Suspendido", "En Espera", "Terminado",
"Disponible","No Disponible", "Fuera de Limite", "Eliminado"
};


//------------------------Funciones-------------------------
class claseA
{
public:
	static int function(int param)
	{
		printf("Funcion 2: estatica en clase A\n");
		printf(" - Se mando el valor: %d\n", param);
		return param;
	}
};

class claseB
{

public:
	static void calling_function(int(*&mem)(int))
	{
		mem = &function;
	}

private:
	static int function(int param)
	{
		printf("Funcion 3: privada en clase B\n");
		printf(" - Se mando el valor: %d\n", param);
		return param;
	}
};

static int function(int param)
{
	printf("Funcion 1: estatica de todo el programa\n");
	printf(" - Se mando el valor: %d\n", param);
	return param;
}

//----------------------------------------------------------


//------------------------Clase-PCB-------------------------
class PCB {
private:
	int ID;
	int state;


public:
	int ProcessState; //Describe en que proceso se encuentra el PCB	
	int* puntero;	// Almacena el valor de la direccion del callback a realizar.
					// Tiene el tipo de estado actualmente en el CPU.
	PCB* siguiente; // Apuntador asia siguiente PCB
	int16_t A_X, B_X, C_X, D_X;
	int16_t S_P, B_P, D_S, C_S;

#pragma region Funciones Get y Set

	void setState(int state) {
		this->state = state;
	}

	void setProcess(int pross) {
		this->ProcessState = pross;
	}

	//Función que retorna el ID
	int returnID()
	{
		return ID;
	}

	int returnState() {
		return state; //devuelve estado en el CPU
	}

	int returnProcessState() {
		return ProcessState; //Devuelve estado del proceso.
	}

	PCB* getNext() {
		return siguiente;
	}

#pragma endregion

#pragma region Constructor y Destructor
	//Constructor para funciones 1 y 2
	PCB(int newId, int newstate, int* pointer)
	{
		ID = newId;
		state = newstate;
		puntero = pointer;
		int16_t ax2, bx2, cx2, dx2;
		uint16_t sp2, ds2, cs2, bp2;
		__asm
		{
			mov ax2, ax
			mov bx2, bx
				mov cx2, cx
				mov dx2, dx
				mov ax, sp
				mov sp2, ax
				mov ax, ds
				mov ds2, ax
				mov ax, cs
				mov cs2, ax
				mov ax, bp
				mov bp2, ax
		}

		A_X = ax2; B_X = bx2; C_X = cx2; D_X = dx2;
		S_P = sp2; D_S = ds2; C_S = cs2; B_P = bp2;
	}

	//"Desctructor"
	~PCB()
	{
		ID = 0;
		state = available;
		puntero = NULL;
	}
#pragma endregion
};
//----------------------------------------------------------

//-----------------------Lista circular--------------------
class lista {
private:
	PCB* actual;

public:
	lista() {
		actual = NULL;
	}

	void insertar(PCB* nodo) {
		if (actual == NULL)
			actual = nodo;
		else nodo->siguiente = actual->siguiente;

		actual->siguiente = nodo;
	}

	void eliminar(int contPCB, int ID) {
		PCB* Aux = actual, *Anterior = Aux; int iterador = 0;
		bool salir = false;
		while (iterador < contPCB && !salir)
		{
			Anterior = Aux;
			Aux = Aux->siguiente;
			if (Aux->returnID() == ID)
				salir = true;
			iterador++;
		}

		if (salir) //Encontró el PCB
		{
			if (Aux == Aux->siguiente) {


				actual->ProcessState = s_delete;
				cout << "El Estado del PCB es: " + ProcessName[actual->returnProcessState()] << endl;
				cout << "Apache una tecla para terminar proceso" << endl;
				getchar();
				actual = NULL;
			}
			else
			{
				actual->ProcessState = s_delete;
				cout << "El Estado del PCB es: " + ProcessName[actual->returnProcessState()] << endl;
				cout << "Apache una tecla para continuar con el otro proceso proceso" << endl;
				getchar();
				Anterior->siguiente = Aux->siguiente;
				actual = Anterior;

			}

		}
		else
			printf("El PCB %d no ha sido encontrado.", ID);
	}

	void eliminar_todos() {
		actual = NULL;
	}

	PCB* tomaPCB()
	{
		return actual;
	}
};

//----------------------------------------------------------

//-----------------------Clase-Kernel-----------------------
class kernel {
private:
	int PCB_ID;

#pragma region Métodos privados

	//Establece los estados segun su ejecucion.
	void setProcessStates(PCB *actPCB, int state, int delay) {
		actPCB->setProcess(state);
		cout << "Su estado actual es: " + ProcessName[actPCB->returnProcessState()] << endl;
		Sleep(delay);
		//https://ccodigo.wordpress.com/tag/time/
	}

	//Ejecuta la ejecucion individual del PCB
	void runFunction(PCB *actPCB)
	{
		//Inicia Espera para ejecutar
		setProcessStates(actPCB, s_waiting, 3000);

		//Inicia proceso de ejecucion
		setProcessStates(actPCB, s_running, 2000);
		int *puntero = actPCB->puntero;
		int(*callback) (int);
		printf("El PCB ejecutado fue el numero %d\n", actPCB->returnID());
		callback = (int(*)(int))*(&puntero);
		callback(1); //Ejecuta función		

					 //Establece el final de la ejecucion
		setProcessStates(actPCB, s_done, 2000);

		//Borrarlo después de correrlo
		deletePCB(actPCB->returnID()); //Borra PCB
									   //-----------------------------
		printf("\n");
	}

#pragma endregion

public:
	int PCB_count;
	lista *PCB_list;
#pragma region Constructor y Destructores

	//Constructor del kernel

	kernel()
	{
		PCB_count = 0;
		PCB_list = new lista();
		PCB_ID = 1;
	}

	//"Destructor del kernel"
	~kernel()
	{
		delete_ALL_PCB(); //Borra todos los PCB
		PCB_count = 0;
	}

#pragma endregion

#pragma region Métodos para agregar PCB

	/*
	Método que agrega un PCB a lista circular.
	*/
	void addPCB(int *callback)
	{
		if (PCB_count < v_size)
		{

			PCB_list->insertar(new PCB(PCB_ID, available, callback)); //Agrega PCB a lista

																	  //Permite decir que se ingreso y su estado actual en el CPU
																	  //cout<<"El estado en el CPU actual es: "  +ProcessName[PCB_list->tomaPCB()->returnState()]<<endl;


			PCB_count++;
			PCB_ID++;
		}
		else
			printf("Error. No se permiten mas procesos");
	}
#pragma endregion

#pragma region Métodos para quitar PCB

	void deletePCB(int ID)
	{
		bool founded = false;
		int cont = 0;
		PCB *actPCB = NULL;
		while (!founded && cont < PCB_count) //Busca el PCB. Al encontrarlo se sale del ciclo
		{
			actPCB = PCB_list->tomaPCB();
			if (actPCB->returnID() == ID) //Si es igual al que se está buscando...
				founded = true; else
				cont++;
		}
		if (founded)
			PCB_list->eliminar(PCB_count, ID); else
			printf("El PCB %d no ha sido encontrado\n", ID);
	}

	/*
	Método que recorre lista de PCB y los
	elimina todos.
	*/
	void delete_ALL_PCB()
	{
		PCB_list->eliminar_todos();
	}

#pragma endregion

#pragma region Métodos para correr PCB

	/*
	Método que busca un PCB por ID. Si lo encuentra
	lo ejecuta. Si no,
	*/
	void runPCB(int ID)
	{
		bool founded = false;
		int cont = 0;
		PCB *actPCB = NULL;
		while (!founded && cont < PCB_count) //Busca el PCB. Al encontrarlo se sale del ciclo
		{
			actPCB = PCB_list->tomaPCB();
			if (actPCB->returnID() == ID) //Si es igual al que se está buscando...
				founded = true; else
				cont++;
		}
		if (founded) //Si encuentra el PCB lo ejecuta
			runFunction(actPCB); //Corre PCB
		else
			printf("El PCB %d no ha sido encontrado\n", ID);
	}

	/*
	Método que corre todos los PCB
	*/
	void runAllPCB()
	{
		PCB *actPCB;
		for (int i = 0; i < PCB_count; i++)
		{
			actPCB = PCB_list->tomaPCB();
			runFunction(actPCB);
		}
	}

#pragma endregion
};
//----------------------------------------------------------

int main()
{
#pragma region Proyecto 2
	int(*privado)(int);
	claseB::calling_function(privado);
	kernel *newKernel = new kernel();

	newKernel->addPCB((int*)&function);
	newKernel->addPCB((int*)&claseA::function);
	newKernel->addPCB((int*)privado);
	newKernel->runAllPCB();
	//newKernel->~kernel();
#pragma endregion

#pragma region Proyecto 1
	/*int *hola;
	int(*PrimerCallback) (int);
	PCB *elpcb = new PCB(10, PrimerCallback);
	int(*SegundoCallback) (int);
	int(claseB::*TercerCallback) (int);

	PrimerCallback = &function;
	PrimerCallback(10);

	SegundoCallback = &claseA::function;
	SegundoCallback(20);

	claseB::calling_function(TercerCallback);
	claseB *objeto = new claseB();
	(objeto->*TercerCallback)(30);

	initializateArray(vector);

	setPosition(&function,vector);
	setPosition(&claseA::function,vector);

	recorreVector(vector);
	//setPosition(&function);
	//PrimerCallback = (int(*)(int))vector[0];
	//PrimerCallback(11);
	*/
#pragma endregion

	return 0;
}


