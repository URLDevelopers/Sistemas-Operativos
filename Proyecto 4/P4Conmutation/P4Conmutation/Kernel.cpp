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

void Kernel::StaticFunction(char c, unsigned long q, short x)
{
	Timer *temp = new Timer();
	temp->Start();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, 0 });
	cout << c;
	while (true)
	{
		if (!temp->isTimeout(q))
		{
			//LamarMetodo()
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, 0 });
			cout << " ";
			break;
		}
		if (GetAsyncKeyState(VK_ADD) & 0x8000) //VK_ADD ascii of '+'
		{
			//string++;
			//if(enter)
			//{ AgregarProcesoNuevo() }

			exit(0);
		}
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
	if (!this->CharExists(c))
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
			this->Tail = this->Tail->next;
		}
	}
}

bool Kernel::CharExists(char c)
{
	PCB *iterator = this->Head;
	while (iterator != NULL)
	{
		if (iterator->c == c)
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

void Kernel::ExectutePCB(PCB *nodo, int x)
{
	typedef void(*Function)(char, unsigned long, int);
	Function DoFunction = (Function)*(&nodo->instruction);
	DoFunction(nodo->c, nodo->quantum, x);
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

void Kernel::ExecuteSO()
{
	InsertPCB('a');
	InsertPCB('b');
	InsertPCB('c');
	InsertPCB('d');
	InsertPCB('e');
	InsertPCB('f');
	PCB*iterator = this->Head;
	short x = 0;
	while (iterator != NULL)
	{
		if (iterator->status != PAUSE)
		{
			ExectutePCB(iterator, x);
		}
		x++;
		iterator = iterator->next;
	}
	this->ExecuteSO();
}