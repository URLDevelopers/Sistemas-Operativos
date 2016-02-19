// PROYECTO2.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include<time.h>
using namespace std;
#define TAMANIO 10//TAMANIO DE LA TABLA
#define TOP 1000
#pragma region FASE1
static int function(int param) {
	cout << "Parametro: " << param << " de la  Funcion" << endl;
	return 1;
}
#pragma region CLASES
class AClass
{
public:

	typedef int(AClass::*Callback)(int);
	static int function(int param) {
		cout << "Parametro: " << param << " Funcion: 2" << endl;
		return 2;
	}
};

class  BClass : public AClass
{
public:

	typedef int(BClass::*Callback)(int);
	typedef int(BClass::*var)(int);
	void direc(var &v)
	{
		v = &BClass::function;
	}

private:
	int function(int param) {
		cout << "Parametro: " << param << " Funcion: 3" << endl;
		return 3;
	}
	
};
#pragma endregion
typedef int(*MyCallBack)(int);
//typedef int(BClass::*Callback)(int);
typedef int(AClass::*Callback)(int);
#pragma endregion

class PCB {
	//int id;
	//string state;
	//int memory;
	//(int*)adress;//adress to general see
	////
	//int *referenceToHeap;//direccion heap
	//int *referenteToStack;//direccion del stack
	////
	//int programcounter;
	int count;
public:
	MyCallBack subcallback;
	int id;
	string state;
	int memory;
	int *adressToProcess;//adress to general see
	int* directions[TAMANIO];				 //
	int *referenceToHeap;//direccion heap
	int *referenteToStack;//direccion del stack
	int typeasignament;
					  //
	int programcounter;
	PCB() {
		count = NULL;
		state = "NUEVO";
		memory = 0;
		adressToProcess = NULL;
		//*referenceToHeap = NULL;
		//*referenteToStack = NULL;
		programcounter = 0;
		typeasignament = 0;
	}
	void call(int i, int v) {
		MyCallBack m1 = NULL, m2 = NULL;
		m1 = (MyCallBack)directions[i];
		m1(v);
	}
	void ingproceso(int pid, string estado)
	{
		this->id = pid;
		this->state = estado;
		//*memory = memoria;
		//*adressToProcess = *dir;
		//programcounter = pc;
	}
	
	~PCB() {
		state = "";
		memory = 0;
		*adressToProcess = NULL;
		*referenceToHeap = NULL;
		*referenteToStack = NULL;
		programcounter = NULL;
		typeasignament = NULL;
	}
	int getCount() {
		if (count >= TAMANIO)
		{
			count = NULL;
			return NULL;
		}
		else
			return count++;
	}
};
class kernel {
	PCB *vpcb[TAMANIO];  // [10];
	
	int pcbactual;
private:
	bool ejecutar(PCB *it) {
		srand(time(NULL));
		int t = rand() % TOP;
		if (it->typeasignament && ExisteElPCB(it))//0 heap, 1 stack
		{	
			int i = it->getCount();
		    *it->directions[i] = *(int*)&function;//(int*)&funtion;
			it->subcallback(t);
		}
		else if (!it->typeasignament && ExisteElPCB(it)) {
			int ik = it->getCount();
			*it->directions[ik] = *(int*)function;//(int*)&funtion;
			it->subcallback(t);
		}
		return 0;
	}
public:
	kernel() {
		*vpcb = new PCB[10];
		pcbactual = NULL;
	}
	/*void agregarproceso(int pid, string estado, int memoria, int *dir, int pc)
	{
		if (pcbactual < 10)
		{
			*vpcb[pcbactual] = new PCB();
			vpcb[pcbactual].ingproceso(pid, estado, memoria, dir, pc);
			pcbactual++;
		}
		else
		{
			liberar();
		}
	}*/
	bool agregarProceso(int micaseofmemory,int pid, string state) {
		if (pcbactual < TAMANIO)
		{
			vpcb[pcbactual] = new PCB();
			//++pcbactual;
			if (micaseofmemory == NULL)
			{//se envia la direccion del heap
				//pcb[pcbactual]->ingproceso(++pcbactual, state);
				vpcb[pcbactual]->subcallback= &function;
			}
			else if (micaseofmemory == 1)
			{
				vpcb[pcbactual]->subcallback = &AClass::function;
			}
			else if (micaseofmemory == 2)
			{
				vpcb[pcbactual]->subcallback = &AClass::function;
			}
			else// si no la del stack
				vpcb[pcbactual]->ingproceso(++pcbactual, state);
			return 1;
		}	
		liberar();
		return 0;
	}
	void liberar()
	{	//liberar memoria
		--pcbactual;
		vpcb[pcbactual]->~PCB();
		delete(vpcb[pcbactual]);
	}
	bool ProcesoEspecifico(int i) {//i es el indice del proceso
		if (!this->ExisteElPCB(this->vpcb[i]))
		{
			return -1;
		}
		ejecutar(this->vpcb[i]);
		return 0;
	}

	bool ExisteElPCB(PCB *i) {
		return i == NULL;
	}
	~kernel() {
		delete(this->vpcb);
	}
};

int main()
{
	//toma de valores
	kernel  *k = new kernel();
	
	for (size_t i = 0; i < TAMANIO; i++)
	{
		k->agregarProceso(1,i,"NUEVO");
		k->ProcesoEspecifico(0);
	}
	//k->ProcesoEspecifico(0);
	k->~kernel();
	delete(k);
	system("PAUSE...");
	return 0;
}