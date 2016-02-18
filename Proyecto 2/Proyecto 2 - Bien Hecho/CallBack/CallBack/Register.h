#pragma once
class Registers
{
public:
	Registers(short ax, short bx, short cx, short dx, short si, short di, short sp, short bp, short cs, short ds, short ss, short es);
	~Registers();

	//Variables
private:
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
#pragma region Temporales
	short tempregax;
	short tempregbx;
	short tempregcx;
	short tempregdx;
	short tempregsi;
	short tempregdi;
	short tempregsp;
	short tempregbp;
	short tempregcs;
	short tempregds;
	short tempregss;
	short tempreges;
#pragma endregion


public:

	//Metodos 
	


};
