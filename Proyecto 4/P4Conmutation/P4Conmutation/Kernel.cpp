#include "stdafx.h"
#include "Kernel.h"
#include <iostream>

Kernel::Kernel()
{
	this->Head == NULL;
	this->Tail == NULL;
	this->idcounter = 0;
}


Kernel::~Kernel()
{
	this->Head = NULL;
	this->Tail = NULL;
	this->idcounter = 0;
}

int Kernel::NewID()
{
	return idcounter++;
}

void Kernel::StaticFunction(char c, unsigned long q)
{
	Timer *temp = new Timer();
	temp->Start();
	cout << c << endl;
	while (!temp->isTimeout(q))
	{
		break;
	}
}

PCB * Kernel::CreatePCB(char c)
{
	short reg[13];
	__asm {
		mov reg[0], ax
			mov reg[1], bx
			mov reg[2], cx
			mov reg[3], dx
			mov reg[4], si
			mov reg[5], di
			mov reg[6], sp
			mov reg[7], bp
			mov reg[8], ds
			mov reg[9], cs
			mov reg[10], ss
			mov reg[11], es
			mov ax, [esp]
			mov reg[12], ax
	}
	return new PCB(this->NewID(), (int*)&StaticFunction, USER, reg, c, quantum);

}

void Kernel::InsertPCB(char c)
{
	if (!CharExists(c))
	{
		PCB *nuevo = CreatePCB(c);
		if (this->Head == NULL)
		{
			this->Head = nuevo;
			this->Tail = nuevo;
		}
		else
		{
			this->Tail->next = nuevo;
			this->Tail = nuevo;
		}
	}
}

bool Kernel::CharExists(char c)
{
	PCB *iterator = this->Head;
	while (iterator != NULL)
	{
		if (iterator->c = c)
		{
			return true;
		}
		iterator = iterator->next;
	}
	return false;
}

void Kernel::PausePCB(char c)
{
	PCB *iterator = this->Head;
	while (iterator != NULL)
	{
		if (iterator->c = c)
		{
			iterator->status = PAUSE;
			break;
		}
		iterator = iterator->next;
	}
}

void Kernel::ExectutePCB(PCB *nodo)
{
	typedef int(*Function)(char, unsigned long);
	Function DoFunction = (Function)*(&nodo->instruction);
	DoFunction(nodo->c, nodo->quantum);
}

void Kernel::ChangeQuantum(char c, unsigned long newquantum)
{
	PCB *iterator = this->Head;
	while (iterator != NULL)
	{
		if (iterator->c = c)
		{
			iterator->quantum = newquantum;
			break;
		}
		iterator = iterator->next;
	}
}

bool Kernel::DeletePCB(char c)
{
	PCB *iterator = this->Head;
	if (this->Head->c == c)
	{
		this->Head == this->Head->next;
		iterator == NULL;
		return true;
	}
	else
	{
		PCB *prev = iterator;
		while (iterator->next != NULL)
		{
			if (iterator->next->c == c)
			{
				iterator->next = iterator->next->next;
				return true;
			}
			prev = iterator;
			iterator == iterator->next;
		}
		if (iterator == this->Tail)
		{
			if (iterator->c == c)
			{
				this->Tail = prev;
				return true;
			}
		}
		return false;
	}
}