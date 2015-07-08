#include "datatypes/structures/list.h"

/**
 * list_node_make - crea un nodo de la lista
 * @param object objeto que se colocará en el nodo de la lista
 * @return Nodo creado
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
struct list_node *list_node_make (void *object)
{
	struct list_node *node = malloc(sizeof(struct list_node));
	if (!node)
		return NULL;
	node->object = object;
	node->next = NULL;
	return node;
}

/**
 * list_make - crear una lista vacía
 * @return Lista creada vacía
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
struct list *list_make ()
{
	struct list *list = malloc(sizeof(struct list));
	list->first_node = NULL;
	list->size = 0;
	return list;
}

/**
 * list_destroy - destruye la lista y todos sus nodos
 * @param list lista que quiere ser destruída
 * @warning no se está haciendo free de los objetos, ¡revisar con gdb!
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void list_destroy (struct list *list)
{
	struct list *tmp = malloc(sizeof(struct list));
	while (list->first_node != NULL) {
		tmp->first_node = list->first_node;
		list->first_node = list->first_node->next;
/*		if (tmp->first_node->object != NULL)
			free(tmp->first_node->object);*/
		free(tmp->first_node);
	}
	free(tmp);
	free(list);
}

/**
 * list_empty - determinar si una lista está o no vacía
 * @param list lista que se desea saber si es o no vacía
 * @return 1 si la lista está vacía, 0 en caso que tenga al menos un nodo
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
short int list_empty (struct list *list)
{
	return list->first_node == NULL ? 1 : 0;
}

/**
 * list_size - entrega el tamaño de la lista (cantidad de objetos)
 * @param list lista a la que se desea saber su tamaño
 * @return tamaño de la lista (cantidad de nodos)
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
int list_size (struct list *list) {
	return list->size;
}

/**
 * list_push - coloca un objeto al inicio de la lista
 * @param list lista donde colocar el objeto
 * @param object objeto que se colocará al inicio de la lista
 * @return 0 en caso de éxito, 1 en caso de error
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
short int list_push (struct list *list, void *object)
{
	struct list_node *node = list_node_make (object);
	if (node == NULL)
		return 1;
	node->next = list->first_node;
	list->first_node = node;
	list->size++;
	return 0;
}

/**
 * list_put - coloca un objeto al final de lista
 * @param list lista donde colocar el objeto
 * @param object objeto que se colocará al final de la lista
 * @return 0 en caso de éxito, 1 en caso de error
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
short int list_put (struct list *list, void *object)
{
	struct list_node *tmp;
	struct list_node *node = list_node_make (object);
	if (node == NULL)
		return 1;
	if (list->first_node == NULL) {
		list->first_node = node;
	} else {
		tmp = list->first_node;
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = node;
	}
	list->size++;
	return 0;
}

/**
 * list_insert - insertar un objeto en cierta posición de la lista
 * @param list lista donde se desea insertar un objeto
 * @param object objeto que se desea insertar en la lista
 * @param index posición en donde se desea insertar (desde 0 y -1 para final)
 * @return 0 en caso de éxito, 1 en caso de error
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
short int list_insert (struct list *list, void *object, int index)
{
	int i;
	struct list_node *tmp;
	struct list_node *node;
	if (index == 0)
		return list_push (list, object);
	else if (index < 0 || index >= list->size)
		return list_put (list, object);
	node = list_node_make (object);
	if (node == NULL)
		return 1;
	tmp = list->first_node;
	for (i=0; i < index-1; ++i)
		tmp = tmp->next;
	node->next = tmp->next;
	tmp->next = node;
	list->size++;
	return 0;
}

/**
 * list_extract - extraer un objeto de la lista
 * @param list lista desde donde sacar el objeto
 * @param index posición para extraer (desde 0 y -1 para el final)
 * @return Objeto que se extrae del nodo solicitado
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void *list_extract (struct list *list, int index)
{
	int i;
	void *object;
	struct list_node *node = NULL;
	struct list_node *delete = NULL;
	if (index < 0)
		index = list->size-1;
	if (index >= list->size)
		return NULL;
	if (index == 0) {
		node = list->first_node;
		list->first_node = list->first_node->next;
		object = node->object;
		free (node);
		list->size--;
		return object;
	}
	node = list->first_node;
	for (i=0; i < index-1; ++i)
		node = node->next;
	delete = node->next;
	node->next = node->next->next;
	object = delete->object;
	free (delete);
	list->size--;
	return object;
}

/**
 * list_pop - extraer un elemento del inicio/tope de la lista
 * @param list lista desde donde sacar el objeto del inicio/tope
 * @return Objeto que se extrae desde el inicio/tope de la lista
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void *list_pop (struct list *list)
{
	return list_extract (list, 0);
}

/**
 * list_popend - extrar un elemento del final de la lista
 * @param list lista desde donde sacar el elemento del final
 * @return Objeto que se extrae desde el final de la lista
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void *list_popend (struct list *list)
{
	return list_extract (list, -1);
}

/**
 * list_remove - borra un objeto de la lista
 * @param list lista donde se quiere borrar un objeto
 * @param index posición del objeto que se desea borrar
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void list_remove (struct list *list, int index)
{
	void *object = list_extract (list, index);
	free (object);
}

/**
 * list_swap - coloca en el índice indica el objeto, retornando el antiguo
 * @param list lista donde se desea hacer el intercambio
 * @param index posición donde se desea hacer el intercambio
 * @param object objeto que se intercambiará en la posición indicada
 * @return Objeto que se encontraba en el índice indicado de la lista
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void *list_swap (struct list *list, int index, void *object)
{
	int i;
	void *tmp;
	struct list_node *node = NULL;
	if (index < 0 || index >= list->size)
		return NULL;
	node = list->first_node;
	for (i=0; i < index; ++i)
		node = node->next;
	tmp = node->object;
	node->object = object;
	return tmp;
}

/**
 * list_index - entrega el índice donde se encuentra el objeto en la lista
 * @param list lista en la que se desea buscar el índice del objeto
 * @param object_compare función para realiar la comparación entre objetos
 * @param object objeto al que se está buscando el índice en la lista
 * @return Índice del objeto en la lista
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
int list_index (struct list *list, int(*object_compare)(void*,void*),
				void *object)
{
	int i = 0;
	struct list_node *tmp = list->first_node;
	while(tmp != NULL && tmp->object != NULL) {
		if (object_compare(tmp->object, object)==0)
			return i;
		tmp = tmp->next;
		++i;
	}
	return -1;
}

/**
 * list_exists - determina si el objeto está o no en la lista
 * @param list lista en la que se desea buscar el objeto
 * @param object_compare función para realizar la comparación entre objetos
 * @param object objeto que se está buscando en la lista
 * @return 1 si el objeto existe en la lista, 0 si no existe
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
short int list_exists (struct list *list, int(*object_compare)(void*,void*),
				void *object)
{
	return list_index (list, object_compare, object) == -1 ? 0 : 1;
}

/**
 * list_foreach - aplicar una determinada acción a cada objeto de la lista
 * @param list lista a la que se desea aplicar determinada acción
 * @param object_action función que se aplicará a cada objeto de la lista
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void list_foreach (struct list *list, void(*object_action)(void*))
{
	struct list_node *tmp = list->first_node;
	while(tmp != NULL && tmp->object != NULL) {
		object_action(tmp->object);
		tmp = tmp->next;
	}
}

/**
 * list_print - imprimir todos los objetos de la lista
 * @param list lista que se desea imprimir
 * @param object_print función que realizará la impresión de cada objeto
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void list_print (struct list *list, void(*object_print)(void*))
{
	struct list_node *tmp = list->first_node;
	printf("[");
	while(tmp != NULL && tmp->object != NULL) {
		object_print(tmp->object);
		if(tmp->next != NULL)
			printf(", ");
		tmp = tmp->next;
	}
	printf("]\n");
}
