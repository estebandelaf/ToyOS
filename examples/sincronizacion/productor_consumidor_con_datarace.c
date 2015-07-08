/**
 * @file productor_consumidor_con_datarace.c
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-20
 *
 * Compilar con:
 *  $ make APP=productor_consumidor_con_datarace
 *
 * Ejecutar con:
 *  $ ./productor_consumidor_con_datarace
 */

#include <stdio.h>
#include <string.h>
#include "ToyOS.h"

#define N 3
#define TEXT "Este es el texto que los consumidores deben imprimir!\n"

int i = 0;
char buffer[N];
int c=0, f=0, e=0;

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
	while (c==N);
	buffer[f] = l;
	f = (f+1)%N;
	c++;
}

char get ()
{
	char l;
	while (c==0);
	l = buffer[e];
	e = (e+1)%N;
	c--;
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
	core_run (cores, 0, productor, NULL);
	core_run (cores, 1, consumidor, NULL);
	cores_wait (cores);
	return 0;
}
