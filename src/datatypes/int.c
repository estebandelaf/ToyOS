#include "datatypes/int.h"

/**
 * int_compare - compara dos enteros
 * @param n1 primer entero
 * @param n2 segundo entero
 * @return <, =, > que cero si n1 <, =, > que n2
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-19
 */
int int_compare (void *n1, void *n2)
{
	if (*(int *)n1 == *(int *)n2)
		return 0;
	else if (*(int *)n1 < *(int *)n2)
		return -1;
	else
		return 1;
}

/**
 * int_print - imprime un entero
 * @param n entero que se desea imprimir
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-19
 */
void int_print (void *n)
{
	printf("%d", *(int*)n);
}
