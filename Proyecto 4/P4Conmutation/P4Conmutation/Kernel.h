#pragma once
#include "PCB.h"
#include "Timer.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>

using namespace std;


class Kernel
{
	
public:
	//Variables
	PCB *Tail, *Head;
	const unsigned long quantum = 1;
	short poscommandx, poscommandy;
	int idcounter;
	string command;
	
	//Methods
	Kernel();
	~Kernel();

	//Static function
	static void StaticFunction(char c, unsigned long q, short x);

	//Set id for PCB
	int NewID();

	void InsertPCB(char c);

	bool DeletePCB(char c);

	void ExectutePCB(PCB * nodo, int x);

	void ChangeQuantum(char c, unsigned long newquantum);

	void ExecuteSO();

	bool CharExists(char c);

	PCB *CreatePCB(char c);

	void PausePCB(char c);

	void KeywordChange();

	void AnaliceCommand();

};

