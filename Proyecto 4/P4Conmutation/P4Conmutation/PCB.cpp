#include "stdafx.h"
#include "PCB.h"


PCB::PCB(int id, int*inst, int mod, short Reg[13], char c, unsigned long q)
{
	this->status = NEW;
	this->next = NULL;
	this->id = id;
	this->instruction = inst;
	this->mod = mod;
	this->regAX = Reg[0];
	this->regBX = Reg[1];
	this->regCX = Reg[2];
	this->regDX = Reg[3];
	this->regSI = Reg[4];
	this->regDI = Reg[5];
	this->regSP = Reg[6];
	this->regBP = Reg[7];
	this->regCS = Reg[8];
	this->regDS = Reg[9];
	this->regSS = Reg[10];
	this->regES = Reg[11];
	this->regIP = Reg[12];
	this->c = c;
	this->quantum = q;
}


PCB::~PCB()
{

}
