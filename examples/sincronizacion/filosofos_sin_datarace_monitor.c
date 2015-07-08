/**
 * @file filosofos_sin_datarace_monitor.c
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-20
 *
 * Compilar con:
 *  $ make APP=filosofos_sin_datarace_monitor
 *
 * Ejecutar con:
 *  $ ./filosofos_sin_datarace_monitor
 */

#include <stdio.h>
#include "ToyOS.h"

struct monitor *m;
int ocupados[] = {0, 0, 0, 0, 0};

void pedir (int palito1, int palito2)
{
	monitor_enter (m);
	while (ocupados[palito1] || ocupados[palito2])
		monitor_wait (m);
	ocupados[palito1] = ocupados[palito2] = 1;
	monitor_exit (m);
}

void devolver (int palito1, int palito2)
{
	monitor_enter (m);
	ocupados[palito1] = ocupados[palito2] = 0;
	monitor_notify_all (m);
	monitor_exit (m);
}

void pensar (int filosofo)
{
	printf("filósofo %d pensando...\n", filosofo);
	sleep (3);
}

void comer (int filosofo, int palito1, int palito2)
{
	printf("filósofo %d comiendo con palitos(%d,%d)...\n", filosofo,
							palito1, palito2);
	sleep (1);
}

int filosofo (void *filosofo)
{
	int f = *(int *)filosofo;
	for (;;) {
		pedir (f, (f+1)%5);
		comer (f,  f, (f+1)%5);
		devolver (f, (f+1)%5);
		pensar (f);
	}
	return 0;
}

int main ()
{
	struct cores *cores = cores_make (5);
	int i;
	int *f = NULL;
	m = monitor_make ();
	for (i=0; i < cores->cores; ++i) {
		f = malloc(sizeof(int));
		*f = i;
		core_run (cores, i, filosofo, (void *)f);
	}
	cores_wait (cores);
	return 0;
}
