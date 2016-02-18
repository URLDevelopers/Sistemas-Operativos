#pragma once
class PCB
{
public:
	PCB(int id, int *instr, int estado, short paramReg[12]);
	~PCB();

	//Variables
private:
	int id;
	int *Instruccion;
	int Estado;
	PCB *next;
	PCB *prev;
#pragma region Registros
	short regax;
	short regbx;
	short regcx;
	short regdx;
	short regsi;
	short regdi;
	short regsp;
	short regbp;
	short regcs;
	short regds;
	short regss;
	short reges;
#pragma endregion
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

