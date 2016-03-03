#include "Thread.h"
#include "stdafx.h"


Thread::Thread()
{

}

Thread::~Thread()
{

}

void Thread::CreateThread(int ThreadId, void *process)
{

}

void Thread::ClearScreen(void)
{
	DWORD    dummy;
	COORD    Home = { 0, 0 };
	FillConsoleOutputCharacter(HandleConsoleOut, ' ',
		ConsoleBufferInfo.dwSize.X * ConsoleBufferInfo.dwSize.Y,
		Home, &dummy);
}

void Thread::WriteTitle(int ThreadNum)
{
	enum {
		sizeOfNThreadMsg = 80
	};
	char    NThreadMsg[sizeOfNThreadMsg];

	//sprintf_s(NThreadMsg, sizeOfNThreadMsg,
	//	"Threads running: %02d.  Press 'A' "
		//"to start a thread,'Q' to quit.", ThreadNum);
}
