###### Sistemas-Operativos
__ Repositorio creado para los proyectos de la clase Sistemas Operativos. Primer ciclo 2016. Universidad Rafael Landivar, Guatemala.__

## GRUPO I

	1. 	David Meneses Villagrán	1115212

	2. 	Daniel Mejía Alvarado	1358213

	3. 	Mario Villanueva Martínez	1265513

	4. 	Diego Alvarez Mendoza	1166513

	5. 	Pablo Damián Mejía	1148012

	6. 	Alejandro Herrera Hernández	1219813

### Submodelos:

	- __ Callbacks: __ contiene la versión inicial del proyecto. No existe la simulación de multiprogramación.
	- __ Threads: __ primera implementación de multiprogramación por medio del manejo de hilos con WINAPI. A partir de esta versión todas las funciones deben ser estáticas.
		* Versión descontinuada
	- __ Kernel: __ _ (versión actual) _ Se continúa con la simulación mediante hilos pero con la simulación de una interrupción de timer.	
	
### Descripción:

Este proyecto simula la multiprogramación de los procesos manejada por un sistema operativos. El fin de este proyecto es solamente para fines educativos * (por el momento) * y solamente es posible apreciar su funcionamiento, pero no manipular su manejo mas que por código. 
El planificador actual no es un objeto, solamente es un algoritmo dentro del kernel.

### Ejemplos de código:

El siguiente ejemplo muestra como agregar una función, la cual toma como parametro un número entero, al kernel y luego ejecuta todos los procesos

```
DWORD WINAPI func(LPVOID param)
{
	int x = (int)param;
	cout << "Hi! The param sent is: " << x << endl;
	return 0;
}

int main()
{
	Kernel *kernel = new Kernel();
	
	int x = 3;
	
	PCB pcb(func, 3);
	
	kernel->registerObserver(pcb);
	
	kernel->runAllProcesses();
	
	return 0;
}
```

La salida del programa será * debe presionar la tecla F para salir *:

```
Hi! The param sent is: 3;
0 - Kernel
0 - Kernel
0 - Kernel
...
```

### Por hacer:

	- [ ] Implementar el planificador como objeto y comportamiento
	- [ ] Asegurarse que solo exista un kernel _ (Singleton Pattern) _
	- [ ] Hacer una interfaz de usuario
	- [ ] Seguir las directivas para el siguiente proyecto