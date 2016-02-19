#include "stdafx.h"
#include "PCB.h"


PCB::PCB(int id, int*proceso, int estado)
{
	this->id = id;
	this->proceso = proceso;
	this->Estado = estado;
	this->Siguiente = NULL;
	this->Anterior = NULL;
}

PCB::~PCB()
{
	this->Estado = 0;
	this->id = 0;
	this->proceso = NULL;
	this->Siguiente = NULL;
	this->Anterior = NULL;
}

int PCB::GetId()
{
	return this->id;
}

void PCB::SetEstado(int estado)
{
	this->Estado = estado;
}

int* PCB::GetProceso()
{
	return this->proceso;
}

int PCB::GetEstado()
{
	return this->Estado;
}

PCB *PCB::GetSiguiente()
{
	return this->Siguiente;
}

void PCB::SetSiguiente(PCB* siguiente)
{
	this->Siguiente = siguiente;
}

PCB *PCB::GetAnterior()
{
	return this->Anterior;
}

void PCB::SetAnterior(PCB *anterior)
{
	this->Anterior = anterior;
}