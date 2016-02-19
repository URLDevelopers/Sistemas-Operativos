#pragma once
class ClassB
{
public:
	ClassB();
	~ClassB();

	static void SetCallback3(int(*&funcion)(int));

	//Funcion no.3 privada
private: 
	static int Funcion3(int par);
};
