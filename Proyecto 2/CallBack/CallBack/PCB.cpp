#include "stdafx.h"
#include "PCB.h"


PCB::PCB(int id, int*instr, int estado)
{
	this->id = id;
	this->Instruccion = instr;
	this->Estado = estado;
}

PCB::~PCB()
{
	this->Estado = 0;
	this->id = 0;
	this->Instruccion = NULL;
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

