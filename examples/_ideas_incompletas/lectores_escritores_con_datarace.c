/**
 * @file lectores_escritores_con_datarace.c
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-22
 *
 * Compilar con:
 *  $ make APP=lectores_escritores_con_datarace
 *
 * Ejecutar con:
 *  $ ./lectores_escritores_con_datarace
 */

#include <stdio.h>
#include <string.h>
#include "dSystem.h"

#define MAX 100

char *keys[MAX], *defs[MAX];

int getSlot()
{
	int i;
	for (i=0; i < MAX; i++)
		if (keys[i]==NULL)
			return i;
	return -1;
}

int getIdX (char *k)
{
	int i;
	for (i=0; i < MAX; i++)
		if(keys[i] != NULL && !strcmp (k, keys[i]))
			return i;
	return -1;
}

void newDef (char *k, char *d)
{
	int i = getSlot();
	if (i != -1) {
		keys[i] = k;
		defs[i] = d;
	}
}

char *query (char *k) {
	int i = getIdX (k);
	return i==-1 ? NULL : defs[i];
}

void delDef (char *k) {
	int i = getIdX(k);
	if(i != -1) {
		keys[i] = NULL;
		defs[i] = NULL;
	}
}

int escritor ()
{
	int i;
	char *k, *d;
	for (i=33; i < 127; ++i) {
		k = malloc (sizeof(char)*2);
		d = malloc (sizeof(char)*4);
		sprintf (k, "%c", (char)i);
		sprintf (d, "%d", i);
		newDef (k, d);
	}
	for (i=33; i < 127; i+=7) {
		k = malloc (sizeof(char)*2);
		sprintf (k, "%c", (char)i);
		delDef(k);
	}
	return 0;
}

int lector ()
{
	int i;
	char k[2];
	for (i=33; i < 127; ++i) {
		sprintf (k, "%c", (char)i);
		printf ("%s = %s\n", k, query(k));
	}
	return 0;
}

int main ()
{
	struct cores *cores = cores_make (6);
	core_run (cores, 0, escritor, NULL);
	core_run (cores, 1, lector, NULL);
	cores_wait (cores);
	return 0;
}
