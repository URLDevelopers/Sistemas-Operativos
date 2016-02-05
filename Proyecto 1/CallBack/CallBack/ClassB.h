#pragma once
class ClassB
{
public:
	ClassB();
	~ClassB();
	
	
	//Funcion no.3 privada en Clase B
private: static int Funcion3(int par);
public: static int AccesoFuncion3(int par);
		 

};

