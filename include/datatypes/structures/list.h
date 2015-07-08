#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>

/**
 * struct node - estructura para representar un nodo de la lista
 * @object: objeto que se guardará, puede ser de cualquier tipo
 * @next: puntero al siguiente elemento en la lista
 * @previous: puntero al anterior elemento en la lista
 */
struct list_node {
	void *object;
	struct list_node *next;
};

/**
 * struct list - estructura para representar la lista (su inicio)
 * @first_node: puntero al primer nodo de la lista
 * @size: cantidad de objetos en la lista
 */
struct list {
	struct list_node *first_node;
	int size;
};

struct list_node *list_node_make (void *object);
struct list *list_make ();
void list_destroy (struct list *list);
short int list_empty (struct list *list);
int list_size (struct list *list);
short int list_push (struct list *list, void *object);
short int list_put (struct list *list, void *object);
#define list_append list_put
short int list_insert (struct list *list, void *object, int index);
void *list_extract (struct list *list, int index);
void *list_pop (struct list *list);
#define list_get list_pop
void *list_popend (struct list *list);
void list_remove (struct list *list, int index);
void *list_swap (struct list *list, int index, void *object);
int list_index (struct list *list, int(*object_compare)(void*,void*),
				void *object);
short int list_exists (struct list *list, int(*object_compare)(void*,void*),
				void *object);
void list_foreach (struct list *list, void(*object_action)(void*));
void list_print (struct list *list, void(*object_print)(void*));

#endif
