#include <stdio.h>
#include "ToyOS.h"

int core1 ()
{
	printf ("Soy el core 1\n");
	return 0;
}

int core2 ()
{
	printf ("Soy el core 2\n");
	return 0;
}

int main (void)
{
	struct cores *cores = cores_make (2);
	core_run (cores, 0, core1, NULL);
	core_run (cores, 1, core2, NULL);
	cores_wait (cores);
	return 0;
}
