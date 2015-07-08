/**
 * @file productor_consumidor_sin_datarace_semaforo.c
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-20
 *
 * Compilar con:
 *  $ make APP=productor_consumidor_sin_datarace_semaforo
 *
 * Ejecutar con:
 *  $ ./productor_consumidor_sin_datarace_semaforo
 */

#include <stdio.h>
#include <string.h>
#include "ToyOS.h"

#define N 3
#define TEXT "Este es el texto que los consumidores deben imprimir!\n"

int i = 0;
char buffer[N];
int f=0, e=0;
struct semaphore *empty, *full;

char produce ()
{
	char *s = TEXT;
	if (i < strlen(s))
		return s[i++];
	return '\0';
}

void consume (char l)
{
	printf("%c", l);
}

void put (char l)
{
	semaphore_wait (empty);
	buffer[f] = l;
	f = (f+1)%N;
	semaphore_signal (full);
}

char get ()
{
	char l;
	semaphore_wait (full);
	l = buffer[e];
	e = (e+1)%N;
	semaphore_signal (empty);
	return l;
}

int productor ()
{
	for (;;) {
		char c = produce ();
		put (c);
	}
	return 0;
}

int consumidor ()
{
	for (;;) {
		char c = get ();
		consume (c);
	}
	return 0;
}

int main ()
{
	struct cores *cores = cores_make (2);
	empty = semaphore_make (N);
	full = semaphore_make (0);
	core_run (cores, 0, productor, NULL);
	core_run (cores, 1, consumidor, NULL);
	cores_wait (cores);
	return 0;
}
