#pragma once
#include "PCB.h"
#include "Timer.h"
#include <iostream>
using namespace std;


class Kernel
{
	
public:
	//Variables
	PCB *Tail, *Head;

	const unsigned long quantum = 5;
	int idcounter;

	//Methods
	Kernel();
	~Kernel();


	//Static function
	static void StaticFunction(char c, unsigned long q);

	//Set id for PCB
	int NewID();

	void InsertPCB(char c);

	bool DeletePCB(char c);

	void ExectutePCB(PCB * nodo);

	void ChangeQuantum(char c, unsigned long newquantum);

	void ExecuteSO();

	bool CharExists(char c);

	PCB *CreatePCB(char c);

	void PausePCB(char c);

};

