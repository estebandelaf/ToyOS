/**
 * @file productor_consumidor_con_deadlock.c
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-20
 *
 * Compilar con:
 *  $ make APP=productor_consumidor_con_deadlock
 *
 * Ejecutar con:
 *  $ ./productor_consumidor_con_deadlock
 */

#include <stdio.h>
#include <string.h>
#include "ToyOS.h"

#define N 3
#define TEXT "Este es el texto que los consumidores deben imprimir!\n"

int i = 0;
char buffer[N];
int c=0, f=0, e=0;
struct semaphore *s;

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
	semaphore_wait (s);
	while (c==N);
	buffer[f] = l;
	f = (f+1)%N;
	c++;
	semaphore_signal (s);
}

char get ()
{
	char l;
	semaphore_wait (s);
	while (c==0);
	l = buffer[e];
	e = (e+1)%N;
	c--;
	semaphore_signal (s);
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
	s = semaphore_make (1);
	core_run (cores, 0, productor, NULL);
	core_run (cores, 1, consumidor, NULL);
	cores_wait (cores);
	return 0;
}
