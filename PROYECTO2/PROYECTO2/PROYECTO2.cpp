#include "stdafx.h"
#include <iostream>

using namespace std;
#define tamanio 10
#pragma region Proyecto1
static int Funcion1(int param)
{
	cout << "Parametro: " << param << " Funcion: 1" << endl;
	return 1;
}

class ClassA
{
public:
	static int Funcion2(int param);
};

int ClassA::Funcion2(int param)
{
	cout << "Parametro: " << param << " Funcion: 2" << endl;
	return 2;
}

class ClassB
{
public:
	static void setCallBack(int (ClassB::*&cb)(int));
private:
	int Funcion3(int param);
};

int ClassB::Funcion3(int param)
{
	cout << "Parametro: " << param << " Funcion: 3" << endl;
	return 3;
}

void ClassB::setCallBack(int (ClassB::*&cb)(int))
{
	cb = &ClassB::Funcion3;
}

typedef int(*CallBack)(int);
typedef int(ClassB::*CallBackB)(int);
#pragma endregion
#pragma region proyecto2
class PCB
{
private:
	int id;
public:
	int Estado, *Funcion;

	ClassB *objeto;

	PCB(int id, int EstadoParam, int *callback)
	{
		this->id = id;
		this->Estado = EstadoParam;
		this->Funcion = callback;
		this->objeto = NULL;
	}

	PCB(int id, int status, int *callback, ClassB *obj)
	{
		this->id = id;
		this->Estado = status;
		this->Funcion = callback;
		this->objeto = obj;
	}

	~PCB()
	{
		this->id = this->Estado = 0;
		this->Funcion = NULL;
		if (this->objeto != NULL)
		{
			this->objeto = NULL;
		}
	}
	int getId()
	{
		return this->id;
	}
};

class Kernel
{
private:
	int id_count;
	bool Valirdar(int i)
	{
		if (i >= tamanio || i < 0)
			return 3;
		if (this->pcb[i] != NULL)
		{
			if (this->pcb[i]->Estado != 6)
				return 1;
			else
				FinalizarProcesos(i);
		}
		if (count >= tamanio) {
			return 2;
		}
		else {
			return 0;
		}
	}

	static void Procesos(PCB *pcb, int val)
	{
		int result;
		int *function = pcb->Funcion;
		pcb->Estado = 1;
		if (pcb->objeto != NULL)
		{
			CallBackB *cb = (CallBackB*)(function);
			result = (pcb->objeto->**cb)(val);
		}
		else
		{
			CallBack cb = (CallBack)*(&function);
			result = cb(val);
		}
		pcb->Estado = 6;
		cout << "Proceso terminado\nNumero de Proceso: " << pcb->getId() << "\nResultado: " << result << endl << endl;
	}

	static bool validarElProceso(PCB *current)
	{
		if (current == NULL)
			return 1;
		if (current->Estado == 6)
			return 2;
		return 0;
	}

	int firstAvailableIndex()
	{
		int i = 0;
		while (i < tamanio)
		{
			if (this->pcb[i] == NULL)
				return i;
			else if (this->pcb[i]->Estado == 6)
			{
				FinalizarProcesos(i);
				return i;
			}
			i++;
		}
		return -1;
	}
	PCB *getProcesorId(int id)
	{
		for (int i = 0; i < tamanio; i++)
			if (pcb[i] != NULL && pcb[i]->getId() == id) {
				return pcb[i];
			}
		return NULL;
	}

	int getProceso(int id)
	{
		for (int i = 0; i < tamanio; i++)
			if (pcb[i] != NULL && pcb[i]->getId() == id) {
				return i;
			}
			else {
				return -1;
			}
	}
public:
	PCB *pcb[tamanio];
	int count;

	Kernel()
	{
		this->count = this->id_count = 0;
		for (int i = 0; i < tamanio; i++)
			this->pcb[i] = NULL;
	}

	~Kernel()
	{
		for (int i = 0; i < tamanio; i++)
			if (pcb[i] != NULL)
			{
				FinalizarProcesos(i);
				pcb[i] = NULL;
			}
		this->count = 0;
	}

	int CrearProceso(int *callback)
	{
		int result = Valirdar(count);
		if (result != 0)
			return result;
		PCB *pcb = new PCB(id_count++, 3, callback);
		int index = firstAvailableIndex();
		this->pcb[index] = pcb;
		count++;
		return 0;
	}

	int CrearProceso(int *callback, int i)
	{
		int result = Valirdar(i);
		if (result != 0) {
			return result;
		}
		PCB *pcb = new PCB(id_count++, 3, callback);
		this->pcb[i] = pcb;
		count++;
		return 0;
	}

	int CrearProceso(int *callback, ClassB *obj)
	{
		int result = Valirdar(count);
		if (result != 0) {
			return result;
		}
		PCB *pcb = new PCB(id_count++, 3, callback, obj);
		int index = firstAvailableIndex();
		this->pcb[index] = pcb;
		count++;
		return 0;
	}

	int CrearProceso(int *callback, ClassB *obj, int i)
	{
		int result = Valirdar(i);
		if (result != 0)
			return result;
		PCB *pcb = new PCB(id_count++, 3, callback, obj);
		this->pcb[i] = pcb;
		i++;
		return 0;
	}

	int runProcessAt(int i, int val)
	{
		PCB *current = this->pcb[i];
		int result = validarElProceso(current);
		if (result != 0) {
			return result;
		}
		Procesos(current, val);
		return 0;
	}

	int runProcessById(int id, int val)
	{
		PCB *current = getProcesorId(id);
		int result = validarElProceso(current);
		if (result != 0) {
			return result;
		}
		Procesos(current, val);
		return 0;
	}
	int ProbarProcesos(int val)
	{
		for (int i = 0; i < tamanio; i++)
		{
			runProcessAt(i, val);
			FinalizarProcesos(i);
		}
		return 0;
	}

	int FinalizarProcesos(int i)
	{
		if (i >= tamanio || i < 0) {
			return 3;
		}
		if (this->pcb[i] == NULL) {
			return 1;
		}
		count--;
		this->pcb[i]->~PCB();
		this->pcb[i] = NULL;
		return 0;
	}

	int FinalizarProyectoID(int id)
	{
		int index = getProceso(id);
		if (index < 0) {
			return 3;
		}
		FinalizarProcesos(index);
		return 0;
	}
};
#pragma endregion
int main()
{
	int valor1;
	cout << "Ingrese valor" << endl;
	cin >> valor1;
	Kernel *kernel = new Kernel();
	kernel->CrearProceso((int*)&Funcion1);
	kernel->CrearProceso((int*)&ClassA::Funcion2);
	CallBackB cb;
	ClassB::setCallBack(cb);
	ClassB *obj = new ClassB();
	kernel->CrearProceso((int*)&cb, obj);

	kernel->ProbarProcesos(valor1);

	system("PAUSE...");
	kernel->~Kernel();
	return 0;
}