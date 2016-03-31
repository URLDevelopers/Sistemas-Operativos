#include "stdafx.h"
#include "Kernel.h"
#include <iostream>
#include <algorithm>
#include <conio.h>
#include <Windows.h>

Kernel::Kernel()
{
	this->Head == NULL;
	this->Tail == NULL;
	this->idcounter = 0;
	this->poscommandy = 5;
	this->poscommandx = 0;
	this->command = "";
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
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, 0 });
			cout << " ";
			break;
		}

	}
}

void Kernel::KeywordChange()
{
	Timer *temp = new Timer();
	temp->Start();
	if (_kbhit() != 0)
	{
		int c = _getch();
		if (c == 43) //+
		{
			exit(0);
		}
		else if (c == 13) //enter
		{
			AnaliceCommand();
			for (int i = 0; i < this->command.length(); i++)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)i, this->poscommandy });
				cout << " ";
			}
			this->command = "";
			this->poscommandx = 0;
		}
		else if ((c > 96 && c < 122) || (c > 47 && c < 58) || c == ' ')
		{
			char x = (char)c;
			this->command += x;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { this->poscommandx, this->poscommandy });
			cout << x;
			poscommandx++;
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
		if (iterator->c == c)
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
		if (iterator->c == c)
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
		this->Head = this->Head->next;
		iterator = NULL;
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
			iterator = iterator->next;
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
	while (true)
	{
		PCB*iterator = this->Head;
		short x = 0;
		KeywordChange();
		while (iterator != NULL)
		{
			if (iterator->status != PAUSE)
			{
				ExectutePCB(iterator, x);
			}
			KeywordChange();
			x++;
			iterator = iterator->next;
		}
		//KeywordChange();
	}
}

void Kernel::AnaliceCommand()
{
	int x = this->command.find(' ');
	transform(this->command.begin(), this->command.end(), this->command.begin(), ::tolower);
	try
	{
		string delimiter = " ";
		string token = command.substr(0, command.find(delimiter));
		//add, pause, remove, quantum
		if (token == "add")
		{
			string resto = command.substr(command.find_first_of(delimiter) + 1, command.length() - 1);
			char c = resto[0];
			InsertPCB(c);
		}
		else if (token == "pause")
		{
			string resto = command.substr(command.find_first_of(delimiter) + 1, command.length() - 1);
			char c = resto[0];
			PausePCB(c);
		}
		else if (token == "remove")
		{
			string resto = command.substr(command.find_first_of(delimiter) + 1, command.length() - 1);
			char c = resto[0];
			DeletePCB(c);
		}
		else if (token == "quantum")
		{
			string resto = command.substr(command.find_first_of(delimiter) + 1, command.length() - 1);
			char c = resto[0];
			resto = resto.substr(resto.find_first_of(delimiter) + 1, resto.length() - 1);
			long quantum = stoi(resto);
			ChangeQuantum(c, quantum);
		}
	}
	catch (exception e)
	{
		this->command == "";
	}
}