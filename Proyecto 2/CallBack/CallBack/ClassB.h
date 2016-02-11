#pragma once
class ClassB
{
public:
	ClassB();
	~ClassB();
	
	static void SetCB3(int(*&funcion)(int));

	//Funcion no.3 privada en Clase B
private: static int Funcion3(int par);


		 

};

