#include "stdafx.h"
#include <iostream>
using namespace std;

//Función estática de todo el programa
static void functionF(int param) {
	cout << "Funcion estatica de todo el programa" << endl;
	cout << "Parametro: " << param << endl;
	cout << "Funcion: 1"<< endl;
}

//Clase A
class ClaseA {
	public: static void functionA(int param) {
		cout << "Funcion estatica de la Clase A" << endl;
		cout << "Parametro: " << param << endl;
		cout << "Funcion: 2" << endl;
	}
};

//Clase B
class ClaseB {
	public: static void getfunctionB(int param) {
		functionB(param);
	}

	private: static void functionB(int param) {
		cout << "Funcion privada de la Clase B" << endl;
		cout << "Parametro: " << param << endl;
		cout << "Funcion: 3" << endl;
	}
};


void main() {
	cout << "Grupo 5" << endl;

	void(*callback1)(int) = &functionF;
	callback1(1);

	void(*callback2)(int) = &ClaseA::functionA;
	callback2(2);

	ClaseB* objB = new ClaseB();
	void(*callback3)(int) = &objB->getfunctionB;
	callback3(3);

	cin.get();
}

