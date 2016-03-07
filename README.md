# Sistemas-Operativos
Repositorio creado para los proyectos de la clase Sistemas Operativos. Primer ciclo 2016. Universidad Rafael Landivar, Guatemala.

GRUPO I

1	David Meneses Villagrán	1115212

2	Daniel Mejía Alvarado	1358213

3	Mario Villanueva Martínez	1265513

4	Diego Alvarez Mendoza	1166513

5	Pablo Damián Mejía	1148012

6	Alejandro Herrera Hernández	1219813

La última versión contiene Threads, manejados con la Api de Win32. Esta es la forma en que se simula el tiempo asignado a cada proceso (función).
El proceso de Kernel se ejecuta en todo momento y es ahí donde se decide el momento en que cada proceso debe ejecutarse según el quantum asignado -revisar el macro QUANTUM en Kernel.h para conocer su valor-.
La función de Kernel es estática, por ende debe enviarse el kernel como parametro para el trabajo dentro de la función.

Cambios en la Versión 1.1 (18/02/2016):

	- La clase Kernel y PCB se encuentran definidas dentro del mismo archivo de encabezado (header file): Kernel.h.

	- El manejo ya no es mediante callbacks, sino mediante threads con timer.

		*El timer es la simulacion de una interrupcion mediante un hilo que se llama luego de un tiempo especificado (el quantum)
		
	- Se ha eliminado el soporte a las funciones no estáticas (que requieren la inicialización de un objeto para su ejecución). En cambio, es recomendable crear una función estática que reciba al objeto como parametro.

		* Es necesario revisar la documentación de WinApi.h y el manejo de hilos (threads) para comprender este concepto.

	- Los registros son guardados (por medio de simulación) por cada función
		
		* Los únicos registros utilizados son los de propósito general, esto se debe al bloqueo por parte del sistema operativo en posiciones de memoria y al manejo de hilos por parte de este
		-->Investigar<--