/**
 * @file filosofos_con_datarace.c
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-20
 *
 * Compilar con:
 *  $ make APP=filosofos_con_datarace
 *
 * Ejecutar con:
 *  $ ./filosofos_con_datarace
 */

#include <stdio.h>
#include "ToyOS.h"

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
		comer (f,  f, (f+1)%5);
		pensar (f);
	}
	return 0;
}

int main ()
{
	struct cores *cores = cores_make (5);
	int i;
	int *f = NULL;
	for (i=0; i < cores->cores; ++i) {
		f = malloc(sizeof(int));
		*f = i;
		core_run (cores, i, filosofo, (void *)f);
	}
	cores_wait (cores);
	return 0;
}
