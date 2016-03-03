#pragma once
class ClassA
{	//Funcion no. 2 estatica
public:
	static int Funcion2(int par);
};

class ClassB
{
public:
	static void SetCallback3(int(*&funcion)(int));

	//Funcion no.3 privada
private:
	static int Funcion3(int par);
};
