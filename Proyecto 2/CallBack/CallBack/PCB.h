#pragma once
class PCB
{
public:
	PCB(int id, int *instr, int estado);
	~PCB();

	//Variables
private:
	int id;
	int *Instruccion;
	int Estado;
	PCB *next;
	PCB *prev;

public:

	//Metodos 
	int GetId();

	int* GetInstruccion();

	int GetEstado();

	void SetEstado(int estado);

	void SetNext(PCB *next);

	PCB *GetNext();

	PCB *GetPrev();

	void SetPrev(PCB * prev);
};

