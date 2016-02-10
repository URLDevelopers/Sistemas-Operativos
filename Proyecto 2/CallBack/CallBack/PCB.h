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

public:

	//Metodos 
	int GetId();

	int* GetInstruccion();

	int GetEstado();



};

