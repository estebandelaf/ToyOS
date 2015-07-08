#include "datatypes/string.h"

/**
 * string_compare - compara dos strings
 * @param s1 primer string
 * @param s2 segundo string
 * @return <, =, > que cero si s1 <, =, > que s2
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-20
 */
int string_compare (void *s1, void *s2)
{
	return strcmp((const char *)s1, (const char *)s2);
}

/**
 * string_print - imprime un string
 * @param s string que se desea imprimir
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-20
 */
void string_print (void *s)
{
	printf("%s", (const char *)s);
} 
