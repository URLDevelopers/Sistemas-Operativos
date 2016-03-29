#pragma once
class PCB
{
	//Status
#define NEW 1
#define PAUSE 2
#define EXECUTE 3
#define DELETE 4

	//Mods
#define KERNEL 0
#define USER 1


public:
	PCB(int id, int*inst, int mod, short reg[13], char c, unsigned long q);
	~PCB();

	///Variables
	int *instruction;
	int id, status, mod;
	unsigned long quantum;
	char c;

	PCB *next;

	short regAX, regBX, regCX, regDX, regSI, regDI, regSP, regBP, regCS, regDS,regSS, regES, regIP;

	//Methods

};

