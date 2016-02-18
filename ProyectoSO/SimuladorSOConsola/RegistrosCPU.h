#pragma once
class RegistrosCPU
{
public:
	RegistrosCPU()
	{

	}
	~RegistrosCPU()
	{

	}

	//Registros de segmento
	int* CS, DS, SS, ES;

	//IP
	int* SP, BP;

	//Registro de propósitos generales
	int* AX, BX, CX, DX;

	//Registros de indices
	int* DL, SL;

	//Banderas
	bool* OF, DF, IF, TF, SF, ZF, AF, PF, CF;

};

