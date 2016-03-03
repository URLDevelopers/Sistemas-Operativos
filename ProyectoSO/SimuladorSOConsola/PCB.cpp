#include "stdafx.h"
#include "PCB.h"


PCB::PCB(int id, void *process, int estado)
{
	this->Id = id;
	this->proceso = process;
	this->status = estado;
	this->Siguiente = NULL;
	this->Anterior = NULL;
}

PCB::~PCB()
{
	this->status = 0;
	this->Id = 0;
	this->proceso = NULL;
	this->Siguiente = NULL;
	this->Anterior = NULL;
}

int PCB::GetId()
{
	return this->Id;
}

void PCB::SetEstado(int estado)
{
	this->status = estado;
}

void *PCB::GetProceso()
{
	return this->proceso;
}

int PCB::GetEstado()
{
	return this->status;
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