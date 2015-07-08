#include "ToyOS.h"

int main (void)
{
	struct list *l = list_make ();
	list_put (l, "Esteban");
	list_put (l, "David");
	list_put (l, "Miguel");
	list_print (l, string_print);
	list_push (l, "Gustavo");
	list_print (l, string_print);
	list_pop (l);
	list_popend (l);
	list_print (l, string_print);
	return 0;
}
