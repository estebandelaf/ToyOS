#include <stdio.h>
#include "ToyOS.h"

int main (void)
{
	struct spinlock sl;
	spin_lock_init (&sl, SPINLOCK_OPEN);
	printf ("sl.lock = %ld\n", sl.lock);
	spin_lock (&sl);
	printf ("sl.lock = %ld\n", sl.lock);
	spin_unlock (&sl);
	printf ("sl.lock = %ld\n", sl.lock);
	spin_lock (&sl);
	printf ("sl.lock = %ld\n", sl.lock);
	spin_lock (&sl);
	/* nunca llega acá */
	return 0;
}
