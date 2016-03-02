// Programa1.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "timer.h"
#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <thread>
#include <cstdlib>

using namespace std;

// ******************** PROYECTO 3 - Grupo 2 ********************

//Total de procesos en la table
#define PROC_LIMIT 10

//Tipo de proceso
#define PROC_KERNEL 1
#define PROC_USUARIO 2

//Estado del proceso
#define NUEVO 1
#define PREPARADO 2
#define EN_EJECUCION 3
#define EN_ESPERA 4
#define TERMINADO 5

//Errores
#define LIMITE_ALCANZADO 1

static bool conmutando = false;

/*static void asignarThread(void* funcAddress) {
	typedef void func(void);
	func* f = (func*)funcAddress;
	thread first(f);
}*/

// ********** PCB **********
class PCB {
private:
	int id;
	int tipoProceso;
	//int16_t AX, BX, CX, DX;
	//int16_t SP, BP, DS, CS, IP;

public:
	int estado;
	void* funcAddress;

	PCB(void* fAddress, int nuevoID, int nuevoTipoProceso, int nuevoEstado) {
		funcAddress = fAddress;
		id = nuevoID;
		tipoProceso = nuevoTipoProceso;
		estado = nuevoEstado;
	}

	void ejecutarFuncion() {
		typedef void func(PCB*);
		func* f = (func*)funcAddress;
		f(this);
	}

	int getID() {
		return id;
	}
};

// ********** LISTA_PCB **********
struct NODO_PCB {
	PCB* data;
	NODO_PCB* next;
};

class LISTA_PCB {
private:
	NODO_PCB* head = NULL;
	NODO_PCB* tail = NULL;
	int limite = 0;
	int totalNodos = 0;
public:
	LISTA_PCB(int lim) {
		limite = lim;
	}

	int agregarNodo(PCB* nuevoPCB) {
		NODO_PCB* nodo = new NODO_PCB();
		nodo->data = nuevoPCB;
		if (totalNodos < limite) {
			if (head == NULL && tail == NULL) { //Lista vacía
				head = nodo;
				tail = nodo;
			}
			else { //Lista tiene algo
				tail->next = nodo;
				tail = nodo;
			}
			totalNodos++;
			return 0;
		}
		else return LIMITE_ALCANZADO;
	}

	NODO_PCB* quitarHead() {
		if (head == NULL) return NULL;
		else {
			NODO_PCB* nodoQuitado = head;
			if (head == tail) { //Un elemento
				head = NULL;
				tail = NULL;
			}
			else head = head->next;
			totalNodos--;
			return nodoQuitado;
		}
	}

	NODO_PCB* buscarNodoConID(int id) {
		if (head != NULL) {
			NODO_PCB* temp = head;
			while (temp != NULL) {
				if (temp->data->getID() == id)
					return temp;
				else
					temp = temp->next;
			}
			return NULL;
		}
		else return NULL;
	}

	NODO_PCB* quitarNodoConID(int id) {
		if (head != NULL) {
			NODO_PCB* temp = head;
			NODO_PCB* tempPrev = NULL;
			while (temp != NULL) {
				if (temp->data->getID() == id) {
					if (head == temp) { //Elemento encontrado en la primera posición
						totalNodos--;
						return quitarHead();
					}
					else { //Encontrado en medio o en el final
						if (temp == tail) //Quitando la cola
							tempPrev->next = NULL;
						else
							tempPrev->next = temp->next;
					}
					totalNodos--;
					return temp;
				}
				else {
					tempPrev = temp;
					temp = temp->next;
				}
			}
			return NULL;
		}
		else return NULL;
	}
};

// ********** KERNEL **********
class KERNEL {
private:
	int id_correlativo = 0;
public:
	LISTA_PCB* tablaPCB = new LISTA_PCB(PROC_LIMIT);
	LISTA_PCB* nuevos = new LISTA_PCB(PROC_LIMIT);
	LISTA_PCB* preparados = new LISTA_PCB(PROC_LIMIT);
	LISTA_PCB* esperando = new LISTA_PCB(PROC_LIMIT);
	LISTA_PCB* terminados = new LISTA_PCB(PROC_LIMIT);
	PCB* ejecucion = NULL;


	int getNextId() {
		id_correlativo++;
		return id_correlativo;
	}

	void crearNuevoPCB(void* funcAddress, int tipoProceso) {
		PCB* nuevoPCB = new PCB(funcAddress, getNextId(), tipoProceso, NUEVO);
		if (tablaPCB->agregarNodo(nuevoPCB) != LIMITE_ALCANZADO)
			nuevos->agregarNodo(nuevoPCB);
	}

	void moverNuevoAPreparado() {
		//Se está pasando el primero en llegar, se podría cambiar por otro criterio de elección
		PCB* pcbQuitado = nuevos->quitarHead()->data;
		preparados->agregarNodo(pcbQuitado);
	}

	void moverEjecucionAEspera() {
		//Se está pasando el primero en llegar, se podría cambiar por otro criterio de elección
		PCB* pcbQuitado = ejecucion;
		ejecucion = NULL;
		esperando->agregarNodo(pcbQuitado);
	}

	void moverEjecucionATerminado() {
		//Se está pasando el primero en llegar, se podría cambiar por otro criterio de elección
		PCB* pcbQuitado = ejecucion;
		ejecucion = NULL;
		terminados->agregarNodo(pcbQuitado);
	}

	void moverEsperaAPreparado() {
		//Se está pasando el primero en llegar, se podría cambiar por otro criterio de elección
		PCB* pcbQuitado = esperando->quitarHead()->data;
		preparados->agregarNodo(pcbQuitado);
	}

	void moverPreparadoAEjecucion() {
		//Se está pasando el primero en llegar, se podría cambiar por otro criterio de elección
		PCB* pcbQuitado = preparados->quitarHead()->data;
		ejecucion = pcbQuitado;
	}

	void ejecutar() {
		ejecucion->ejecutarFuncion();
	}

	void conmutar() {
		NODO_PCB* nuevoNuevoNodo = nuevos->quitarHead();
		
		if (nuevoNuevoNodo != NULL) {
			PCB* nuevoNuevo = nuevoNuevoNodo->data;
			nuevoNuevo->estado = PREPARADO;
			preparados->agregarNodo(nuevoNuevo);
		}

		NODO_PCB* nuevoEjecucionNodo = preparados->quitarHead();
		if (nuevoEjecucionNodo != NULL) { //Sí hay PCB para ejecutar
			PCB* nuevoEjecucion = nuevoEjecucionNodo ->data;
			nuevoEjecucion->estado = EN_EJECUCION;
			if (ejecucion != NULL) {
				ejecucion->estado = PREPARADO;
				preparados->agregarNodo(ejecucion);
			}
			ejecucion = nuevoEjecucion;
		}
	}
};

#pragma region Funciones estáticas
static void funcion0(PCB* PCBEncargado)
{
	while(PCBEncargado->estado == EN_EJECUCION)
		printf("\n\t 0-Kernel");
}

static void funcion1(PCB* PCBEncargado)
{
	while(PCBEncargado->estado == EN_EJECUCION)
		printf("\n\t 1-Func1");
}

static void funcion2(PCB* PCBEncargado)
{
	while(PCBEncargado->estado == EN_EJECUCION)
		printf("\n\t 2-Func2");
}
#pragma endregion

static KERNEL* kernel = new KERNEL();

static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0)
	{
		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
		{

			kernel->conmutar();
			kernel->ejecutar();
		}
	}
	//return CallNextHookEx(hHook, nCode, wParam, lParam);
	return 1;
}

int main()
{
	kernel->crearNuevoPCB((void*)funcion0, PROC_KERNEL);
	kernel->crearNuevoPCB((void*)funcion1, PROC_USUARIO);
	kernel->crearNuevoPCB((void*)funcion2, PROC_USUARIO);

	CTimer timer;
	timer.Set(2000, 2000, []()
	{
		kernel->conmutar();
		kernel->ejecutar();
	});

	kernel->conmutar();
	kernel->ejecutar();

	
	int c = 0;
	while (1)
	{
		c = 0;

		switch ((c = _getch())) {
		case 'f':
			exit(1);
			break;
		}
	}

	return 0;
}


