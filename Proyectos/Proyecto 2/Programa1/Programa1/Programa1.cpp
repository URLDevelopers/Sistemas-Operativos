// Programa1.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
using namespace std;


#define v_size 10 //Tamaño del vector

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
	static void claseB::calling_function(int(*&mem)(int))
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

	public:
		int* puntero;

	//Función que retorna el ID
	int returnID()
	{
		return ID;
	}

	#pragma region Constructor y Destructor
	//Constructor para funciones 1 y 2
	PCB(int newId, int* pointer)
	{
		ID = newId;
		puntero = pointer;
	}

	//"Desctructor"
	~PCB()
	{
		ID = 0;
		puntero = NULL;
	}
	#pragma endregion
};
//----------------------------------------------------------


//-----------------------Clase-Kernel-----------------------
class kernel {
	private:

		#pragma region Métodos privados
		void initializateArray()
		{
			for (int i = 0; i < v_size; i++)
				if (pcbList[i] != NULL)
					pcbList[i] = NULL;
		}

		//Función que retorna primera celda disponible
		int firstAvailable()
		{
			int cont = 0;
			while (cont < v_size)
			{
				if (pcbList[cont] == NULL)
					return cont; else
					cont++;
			}
		}

		//Método que ejecuta PCB específico
		void runFunction(PCB *actPCB)
		{

			int *puntero = actPCB->puntero;
			int(*callback) (int);
			printf("El PCB ejecutado fue el numero %d\n", actPCB->returnID());
			callback = (int(*)(int))*(&puntero);
			callback(1); //Ejecuta función
			printf("\n");
		}
		#pragma endregion

	public:
		PCB *pcbList[v_size]; //Vector de 10 posiciones
		int PCB_count;

		#pragma region Constructor y Destructores

			//Constructor del kernel
			kernel()
			{
				PCB_count = 0;
				initializateArray(); //Vuelve todo NULL
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
			Método que agrega un puntero y lo convierte
			en PCB. Luego, este lo ingresa en la lista en
			la primera posición disponible.
			*/
			void addToAvailable(int *callback)
			{
				if (PCB_count <= 10)
				{
					int first = firstAvailable() + 1; //Toma 1er espacio NULL disponible
					PCB *newPCB = new PCB(first, callback); //Crea PCB
					pcbList[first - 1] = newPCB; //Lo agrega a lista
					PCB_count++;
				}
				else
					printf("Error. No se permiten mas procesos");
			}

			/*
			Método que agrega un puntero y lo convierte
			en PCB. Luego, este lo ingresa en la lista en
			la posición index.
			*/
			void addToIndex(int *callback, int index)
			{
				if (index >= 0 && index < v_size)
				{
					if (pcbList[index] == NULL)
					{
						PCB *newPCB = new PCB(index + 1, callback); //Crea PCB
						pcbList[index] = newPCB; //Lo agrega a lista
						PCB_count++;
					}
					else
						printf("Error. La posicion %d ya esta ocupada", index);
				}
				else
					printf("Error. Indice no esta dentro del rango [0..%d]\n", v_size);
			}
		#pragma endregion

		#pragma region Métodos para quitar PCB

			/*
			Método que borra un PCB en una posición
			específica.
			*/
			void deletePCB(int index)
			{
				if (index >= 0 && index < v_size)
				{
					if (pcbList[index] != NULL) //Si es != null, borra PCB
					{
						PCB_count--;
						pcbList[index]->~PCB(); //Utiliza destructor
						pcbList[index] = NULL; //Es necesario?
					}
				}
				else
					printf("Error. Índice no está dentro del rango [0..%d]\n", v_size);;
			}

			/*
			Método que recorre lista de PCB y los
			elimina todos.
			*/
			void delete_ALL_PCB()
			{
				for (int i = 0; i < v_size; i++)
					deletePCB(i);
			}

		#pragma endregion

		#pragma region Métodos para correr PCB
			
			/*
				Método que corre un PCB en una posición index.
			*/
			void runFunction_Index(int index)
			{
				if (index >= 0 && index < v_size)
				{
					PCB *act = pcbList[index];
					if (act != NULL)
						runFunction(act); //Corre PCB
				}
				else
					printf("Error. indice no esta dentro del rango [0..%d]\n", v_size);
			}

			/*
				Método que corre todos los PCB en lista
			*/
			void runAllFunctions()
			{
				for (int i = 0; i < v_size; i++)
				{
					runFunction_Index(i);
					deletePCB(i); //Borra PCB
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

	newKernel->addToAvailable((int*)&function);
	newKernel->addToAvailable((int*)&claseA::function);
	newKernel->addToAvailable((int*)privado);
	newKernel->runAllFunctions();
	newKernel->~kernel();
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


