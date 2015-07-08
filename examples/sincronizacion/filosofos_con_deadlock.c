/**
 * @file filosofos_con_deadlock.c
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-21
 *
 * Compilar con:
 *  $ make APP=filosofos_con_deadlock
 *
 * Ejecutar con:
 *  $ ./filosofos_con_deadlock
 */

#include <stdio.h>
#include "ToyOS.h"

struct semaphore *palitos[5];

void pedir (int palito1, int palito2)
{
	semaphore_wait (palitos[palito1]);
	semaphore_wait (palitos[palito2]);
}

void devolver (int palito1, int palito2)
{
	semaphore_signal (palitos[palito1]);
	semaphore_signal (palitos[palito2]);
}

void pensar (int filosofo)
{
	printf("filósofo %d pensando...\n", filosofo);
	sleep (3);
}

void comer (int filosofo, int palito1, int palito2)
{
	printf("filósofo %d comiendo con palitos(%d,%d)...\n",
						filosofo, palito1, palito2);
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
	for (i=0; i < cores->cores; ++i)
		palitos[i] = semaphore_make (1);
	for (i=0; i < cores->cores; ++i) {
		f = malloc(sizeof(int));
		*f = i;
		core_run (cores, i, filosofo, (void *)f);
	}
	cores_wait (cores);
	return 0;
}
