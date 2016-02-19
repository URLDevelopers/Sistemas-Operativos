#pragma once
class PCB
{
public:
	PCB(int id, int *proceso, int estado);
	~PCB();

private:
	int id;
	int Estado;
	int* proceso;
	PCB *Siguiente;
	PCB *Anterior;

public:
	int GetId();

	int* GetProceso();

	int GetEstado();

	void SetEstado(int estado);

	void SetSiguiente(PCB *next);

	void SetAnterior(PCB *siguiente);

	PCB *GetSiguiente();

	PCB *GetAnterior();
};

