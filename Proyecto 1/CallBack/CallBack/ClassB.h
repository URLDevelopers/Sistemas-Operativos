#pragma once
class ClassB
{
public:
	ClassB();
	~ClassB();
	
	static void SetCB3(int (ClassB::*&fun)(int));

	//Funcion no.3 privada en Clase B
private: int Funcion3(int par);


		 

};

