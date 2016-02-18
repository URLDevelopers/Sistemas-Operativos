#include "stdafx.h"
#include "Register.h"
//Constructor de la clase
Registers::Registers(short ax, short bx, short cx, short dx, short si, short di, short sp, short bp, short cs, short ds, short ss, short es)
{
	this->regax = ax;
	this->regbx = bx;
	this->regcx = cx;
	this->regdx = dx;
	this->regsi = si;
	this->regdi = di;
	this->regsp = sp;
	this->regbp = bp;
	this->regcs = cs;
	this->regds = ds;
	this->regss = ss;
	this->reges = es;

}

//Destructor de la clase
Registers::~Registers()
{
	this->regax = NULL;
	this->regbx = NULL;
	this->regcx = NULL;
	this->regdx = NULL;
	this->regsi = NULL;
	this->regdi = NULL;
	this->regsp = NULL;
	this->regbp = NULL;
	this->regcs = NULL;
	this->regds = NULL;
	this->regss = NULL;
	this->reges = NULL;

}
