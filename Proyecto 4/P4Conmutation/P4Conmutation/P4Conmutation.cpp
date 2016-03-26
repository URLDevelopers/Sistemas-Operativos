// P4Conmutation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Timer.h"
#include "Kernel.h"
#include <conio.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	/*short poscommandx = 0;
	string command = "";
	while (true)
	{
		if (GetAsyncKeyState(VK_ADD) & 0x8000) //VK_ADD ascii of '+'
		{
			exit(0);
		}
		if (GetKeyState(VK_RETURN) & 0x8000) //Virtual key for enter
		{
			command = "";
			break;
		}
		else
		{
			char x = (char)_getch();
			command += x;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { poscommandx, 2 });
			cout << x;
			poscommandx++;
		}
	}*/


	
	Kernel *SO = new Kernel();
	SO->ExecuteSO();
	return 0;
}

