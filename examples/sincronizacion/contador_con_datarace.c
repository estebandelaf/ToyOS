/**
 * @file contador_con_datarace.c
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-20
 *
 * Compilar con:
 *  $ make APP=contador_con_datarace
 *
 * Ejecutar con:
 *  $ for i in `seq 0 100`; do ./contador_con_datarace; done
 */

#include <stdio.h>
#include "ToyOS.h"

int c = 0;	

int contador ()
{
	int aux, wait = 100;
	aux = c;
	while (wait--);
	c = aux + 1;
	return 0;
}

int main ()
{
	struct cores *cores = cores_make (1000);
	int i;
	for (i=0; i < cores->cores; ++i)
		core_run (cores, i, contador, NULL);
	cores_wait (cores);
	printf("contador = %d\n", c);
	return 0;
}
