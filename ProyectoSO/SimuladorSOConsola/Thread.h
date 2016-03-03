#include <Windows.h>


class Thread {
private:
	#define MAX_THREADS  32
	HANDLE  HandleConsoleOut;                 // Handle to the console 
	int     ThreadID;                    // Number of threads started 
	CONSOLE_SCREEN_BUFFER_INFO ConsoleBufferInfo; // Console information 

public:

	Thread();
	~Thread();


	void CreateThread(int ThreadId, void *process);      // Threads 2 to n: display 
	void ClearScreen(void);            // Screen clear 
	void WriteTitle(int ThreadNum);    // Display title bar information 

};