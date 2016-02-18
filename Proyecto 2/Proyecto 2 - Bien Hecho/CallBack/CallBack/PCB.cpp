#include "stdafx.h"
#include "PCB.h"

//Constructor de la clase
PCB::PCB(int id, int*instr, int estado, short paramReg[12])
{
	this->id = id;
	this->Instruccion = instr;
	this->Estado = estado;
	this->next = NULL;
	this->prev = NULL;
	this->regax = paramReg[0];
	this->regbx = paramReg[1];
	this->regcx = paramReg[2];
	this->regdx = paramReg[3];
	this->regsi = paramReg[4];
	this->regdi = paramReg[5];
	this->regsp = paramReg[6];
	this->regbp = paramReg[7];
	this->regcs = paramReg[8];
	this->regds = paramReg[9];
	this->regss = paramReg[10];
	this->reges = paramReg[11];
}

//Destructor de la clase
PCB::~PCB()
{
	this->Estado = 0;
	this->id = 0;
	this->Instruccion = NULL;
	this->prev = NULL;
	this->next = NULL;
}

//Metodos

//Retorna el id del PCB actual
int PCB::GetId()
{
	return this->id;
}

//Establece el estado del PCB
void PCB::SetEstado(int estado)
{
	this->Estado = estado;
}
//Retorna el puntero de la instruccion del PCB actual
int* PCB::GetInstruccion()
{
	return this->Instruccion;
}

//Retorna el estado del PCB actual
int PCB::GetEstado()
{
	return this->Estado;
}

//Obtiene el nodo siguiente
PCB *PCB::GetNext()
{
	return this->next;
}

//Establece el puntero para el siguiente PCB
void PCB::SetNext(PCB* next)
{
	this->next = next;
}

//Obtiene el nodo anterior
PCB *PCB::GetPrev()
{
	return this->prev;
}

//Establece el puntero del nodo anterior
void PCB::SetPrev(PCB *prev)
{
	this->prev = prev;
}


