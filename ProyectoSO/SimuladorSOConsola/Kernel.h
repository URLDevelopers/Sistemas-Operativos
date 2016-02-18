#include "PCB.h"
#include "stdafx.h"

#pragma once
class Kernel
{

public:
	
	
	Kernel(int LONG)
	{
		longitudTabla = LONG;
		for (int i = 0; i < longitudTabla; i++)
		{
			TablaProcesos[i] = nullptr;
		}
	}

	~Kernel()
	{
	}

	PCB* TablaProcesos [10];
	
	void CargarProceso(int* procesoUsuario)
	{

	}


private:
	
	int longitudTabla;
	void PrepararProceso()
	{

	}

	void SuspenderProceso()
	{

	}

	void AtenderProceso()
	{

	}

	void EjecutarProceso()
	{

	}

	PCB* _buscarPCBDisponible()
	{
		for (int i = 0; i < longitudTabla; i++)
		{

		}
	}

};

