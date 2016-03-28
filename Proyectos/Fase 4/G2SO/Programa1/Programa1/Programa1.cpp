// Programa1.cpp: define el punto de entrada de la aplicación de consola.
//
#pragma warning(disable:4996)
#include "stdafx.h"
#include "timer.h"
#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <thread>
#include <cstdlib>
#include <sstream>
#include <vector>

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
static int posicionIngresada = 1;

static int currentQuantum = 1;
static int defaultQuantum = 1;

COORD cWhere;
DWORD dwCharsWritten;
HANDLE output;

static void cleanPosition()
{
	wchar_t wtext[1];
	wtext[0] = ' ';
	LPWSTR ptr = wtext;
	WriteConsoleOutputCharacter(output, ptr, 1, cWhere, &dwCharsWritten);
}

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
	bool debeMoverseAEspera = false;
	bool debeMoverseAPreparado = false;
	bool eliminar = false;
	int posicion;
	int quantum;
	char caracter;
	void* funcAddress;

	PCB(void* fAddress, int nuevoID, int nuevoTipoProceso, int nuevoEstado, int nQuantum, char nCaracter, int nPosicion) {
		funcAddress = fAddress;
		id = nuevoID;
		tipoProceso = nuevoTipoProceso;
		estado = nuevoEstado;
		quantum = nQuantum;
		caracter = nCaracter;
		posicion = nPosicion;
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

	NODO_PCB* buscarNodoConChar(char caracter) {
		if (head != NULL) {
			NODO_PCB* temp = head;
			while (temp != NULL) {
				if (temp->data->caracter == caracter)
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
						{
							tempPrev->next = NULL;
							tail = tempPrev;
						}
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

	vector<int> idsParaEspera()
	{
		vector<int> ids;
		if (head != NULL) {
			NODO_PCB* temp = head;
			while (temp != NULL) {
				if (temp->data->debeMoverseAEspera)
					ids.push_back(temp->data->getID());
				temp = temp->next;
			}
		}
		return ids;
	}

	vector<int> idsParaPreparados()
	{
		vector<int> ids;
		if (head != NULL) {
			NODO_PCB* temp = head;
			while (temp != NULL) {
				if (temp->data->debeMoverseAPreparado)
					ids.push_back(temp->data->getID());
				temp = temp->next;
			}
		}
		return ids;
	}

	vector<int> idsParaEliminar()
	{
		vector<int> ids;
		if (head != NULL) {
			NODO_PCB* temp = head;
			while (temp != NULL) {
				if (temp->data->eliminar)
					ids.push_back(temp->data->getID());
				temp = temp->next;
			}
		}
		return ids;
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

	void crearNuevoPCB(void* funcAddress, int tipoProceso, char caracter, int quantum) {
		PCB* nuevoPCB = new PCB(funcAddress, getNextId(), tipoProceso, NUEVO, quantum, caracter, posicionIngresada);
		posicionIngresada++;
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

	void moverPCBAEspera(char caracter) {
		NODO_PCB * pcb = tablaPCB->buscarNodoConChar(caracter);
		if (pcb != NULL) {
			pcb->data->debeMoverseAEspera = true;
		}
	}

	void moverPCBDeEsperaAPreparado(char caracter) {
		NODO_PCB * pcb = esperando->buscarNodoConChar(caracter);
		if (pcb != NULL) {
			pcb->data->debeMoverseAPreparado = true;
		}
	}

	void eliminarPCB(char caracter) {
		NODO_PCB * pcb = tablaPCB->buscarNodoConChar(caracter);
		if (pcb != NULL) {
			pcb->data->eliminar = true;
		}
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
		cleanPosition();
		if (ejecucion != NULL)
		{
			int nuevaPosicion = ejecucion->posicion;
			cWhere.X = nuevaPosicion - 1;
			cWhere.Y = 0;
			output = GetStdHandle(STD_OUTPUT_HANDLE);
			ejecucion->ejecutarFuncion();
		}
		cleanPosition();
	}

	void eliminarProcesos() {
		vector<int> idsParaEliminar = tablaPCB->idsParaEliminar();
		for (int i = 0; i < idsParaEliminar.size(); i++)
		{
			PCB * pcb = tablaPCB->buscarNodoConID(idsParaEliminar[i])->data;
			switch (pcb->estado) {
				case PREPARADO:
					preparados->quitarNodoConID(pcb->getID());
					break;
				case EN_ESPERA:
					esperando->quitarNodoConID(pcb->getID());
					break;
				case EN_EJECUCION:
					ejecucion = NULL;
					break;
				case NUEVO:
					nuevos->quitarNodoConID(pcb->getID());
					break;
			}
			pcb->estado = TERMINADO;
			pcb->eliminar = false;
			terminados->agregarNodo(pcb);
		}
	}

	void cambiarQuantum(char caracter, int nuevoQuantum) {
		NODO_PCB * nodo = tablaPCB->buscarNodoConChar(caracter);
		if (nodo != NULL)
		{
			PCB * pcb = nodo->data;
			pcb->quantum = nuevoQuantum;
		}
	}

	void conmutar() {
		//Terminar los procesos terminados
		eliminarProcesos();

		//Pasar de nuevos a preparados
		NODO_PCB* nuevoNuevoNodo = nuevos->quitarHead();
		while (nuevoNuevoNodo != NULL) {
			PCB* nuevoNuevo = nuevoNuevoNodo->data;
			nuevoNuevo->estado = PREPARADO;
			preparados->agregarNodo(nuevoNuevo);
			nuevoNuevoNodo = nuevos->quitarHead();
		}

		//Sacar de los preparados a espera
		vector<int> paraEspera = preparados->idsParaEspera();
		for (int i = 0; i < paraEspera.size(); i++)
		{
			NODO_PCB * quitado = preparados->quitarNodoConID(paraEspera[i]);
			if (quitado != NULL)
			{
				PCB * pcbQuitado = quitado->data;
				pcbQuitado->debeMoverseAEspera = false;
				pcbQuitado->estado = EN_ESPERA;
				esperando->agregarNodo(pcbQuitado);
			}
		}

		//Sacar de espera a preparados
		vector<int> paraPreparados = esperando->idsParaPreparados();
		for (int i = 0; i < paraPreparados.size(); i++)
		{
			NODO_PCB * quitado = esperando->quitarNodoConID(paraPreparados[i]);
			if (quitado != NULL)
			{
				PCB * pcbQuitado = quitado->data;
				pcbQuitado->debeMoverseAPreparado = false;
				pcbQuitado->estado = PREPARADO;
				preparados->agregarNodo(pcbQuitado);
			}
		}
		
		//Pasar ejecución a preparados o espera
		if (ejecucion != NULL) {
			if (!ejecucion->debeMoverseAEspera)
			{
				ejecucion->estado = PREPARADO;
				preparados->agregarNodo(ejecucion);
			}
			else
			{
				ejecucion->estado = EN_ESPERA;
				ejecucion->debeMoverseAEspera = false;
				esperando->agregarNodo(ejecucion);
			}
			ejecucion = NULL;
		}

		//De preparados a ejecución
		NODO_PCB* nuevoEjecucionNodo = preparados->quitarHead();
		if (nuevoEjecucionNodo != NULL) { //Sí hay PCB para ejecutar
			PCB* nuevoEjecucion = nuevoEjecucionNodo->data;
			nuevoEjecucion->estado = EN_EJECUCION;
			ejecucion = nuevoEjecucion;
		}
	}
};

static void printChar(PCB* PCBEncargado)
{
	while (PCBEncargado->estado == EN_EJECUCION)
	{
		wchar_t wtext[1];
		wtext[0] = PCBEncargado->caracter;
		LPWSTR ptr = wtext;
		WriteConsoleOutputCharacter(output, ptr, 1, cWhere, &dwCharsWritten);
	}
}

static KERNEL* kernel = new KERNEL();

int main()
{
	/*kernel->crearNuevoPCB((void*)printChar, PROC_KERNEL, 'a', defaultQuantum);
	kernel->crearNuevoPCB((void*)printChar, PROC_USUARIO, 'b', defaultQuantum);
	kernel->crearNuevoPCB((void*)printChar, PROC_USUARIO, 'c', defaultQuantum);*/

	CTimer timer;
	timer.Set(currentQuantum, currentQuantum, []()
	{
		kernel->conmutar();
		if (kernel->ejecucion != NULL)
			currentQuantum = kernel->ejecucion->quantum;
		kernel->ejecutar();
	});

	/*kernel->conmutar();
	kernel->ejecutar();*/

	COORD p = { 0, 5 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);

	while (1)
	{
		string str;
		getline(cin, str);
		string arr[3];
		int i = 0;
		stringstream ssin(str);
		while (ssin.good() && i < 3)
		{
			ssin >> arr[i];
			i++;
		}
		if (arr[0] == "add")
		{
			char nuevaLetra = arr[1].at(0);
			if (kernel->tablaPCB->buscarNodoConChar(nuevaLetra) == NULL)
				kernel->crearNuevoPCB((void*)printChar, PROC_USUARIO, nuevaLetra, defaultQuantum);
		}
		else if (arr[0] == "pause")
		{
			char letraPausa = arr[1].at(0);
			kernel->moverPCBAEspera(letraPausa);
		}
		else if (arr[0] == "unpause")
		{
			char letraPausa = arr[1].at(0);
			kernel->moverPCBDeEsperaAPreparado(letraPausa);
		}
		else if (arr[0] == "remove")
		{
			char letraRemove = arr[1].at(0);
			kernel->eliminarPCB(letraRemove);
		}
		else if (arr[0] == "quantum")
		{
			char letra = arr[1].at(0);
			int nuevoQuantum = stoi(arr[2]);
			kernel->cambiarQuantum(letra, nuevoQuantum);
		}
	}

	return 0;
}
/*#pragma region Funciones estáticas
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
#pragma endregion*/

