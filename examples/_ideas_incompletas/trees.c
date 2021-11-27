#include <stdio.h>
#include <stdlib.h>
#include "dSystem.h"

#define TREE_TRAVERSAL_DEPTH_FIRST_PRE_ORDER 0
#define TREE_TRAVERSAL_DEPTH_FIRST_IN_ORDER 1
#define TREE_TRAVERSAL_DEPTH_FIRST_POST_ORDER 2

struct tree {
	void *object;
	struct tree *parent;
	struct tree *left;
	struct tree *right;
};

/**
 *
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
struct tree *tree_make ()
{
	struct tree *tree = malloc (sizeof(struct tree));
	if (!tree)
		return NULL;
	tree->object = NULL;
	tree->parent = NULL;
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}

/**
 *
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
short int tree_insert (struct tree *tree, int(*object_compare)(void*,void*),
				void *object)
{
	if (tree == NULL)
		return 1;
	if (tree->object == NULL) {
		tree->object = object;
		return 0;
	}
	if (object_compare (object, tree->object) <= 0) {
		if (tree->left == NULL) {
			tree->left = tree_make ();
			if (tree->left == NULL)
				return 1;
			tree->left->parent = tree;
		}
		return tree_insert (tree->left, object_compare, object);
	} else {
		if (tree->right == NULL) {
			tree->right = tree_make ();
			if (tree->right == NULL)
				return 1;
			tree->right->parent = tree;
		}
		return tree_insert (tree->right, object_compare, object);
	}
	return 1;
}

/**
 *
 * @todo implementar
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void *tree_extract (struct tree *tree, ...)
{
	void *object = NULL;
	return object;
}

/**
 *
 * @todo implementar
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void tree_remove (struct tree *tree, ...)
{
	void *object = tree_extract (tree);
	free (object);
}

/**
 *
 * @todo implementar
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
short int tree_exists (struct tree *tree, int(*object_compare)(void*,void*),
				void *object)
{
	return -1;
}

/**
 *
 * @todo implementar
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
int tree_height (struct tree *tree)
{
	return 0;
}

/**
 *
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void tree_print (struct tree *tree, void(object_print)(void*), short int type)
{
	if (tree == NULL || tree->object == NULL)
		return;
	if (type == TREE_TRAVERSAL_DEPTH_FIRST_PRE_ORDER) {
		object_print (tree->object);
		printf("\n");
		tree_print (tree->left, object_print, type);
		tree_print (tree->right, object_print, type);
	} else if (type == TREE_TRAVERSAL_DEPTH_FIRST_IN_ORDER) {
		tree_print (tree->left, object_print, type);
		object_print (tree->object);
		printf("\n");
		tree_print (tree->right, object_print, type);
	} else if (type == TREE_TRAVERSAL_DEPTH_FIRST_POST_ORDER) {
		tree_print (tree->left, object_print, type);
		tree_print (tree->right, object_print, type);
		object_print (tree->object);
		printf("\n");
	}
}

/**
 *
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void tree_foreach (struct tree *tree, void(object_action)(void*),
							short int type)
{
	if (tree == NULL || tree->object == NULL)
		return;
	if (type == TREE_TRAVERSAL_DEPTH_FIRST_PRE_ORDER) {
		object_action (tree->object);
		tree_foreach (tree->left, object_action, type);
		tree_foreach (tree->right, object_action, type);
	} else if (type == TREE_TRAVERSAL_DEPTH_FIRST_IN_ORDER) {
		tree_foreach (tree->left, object_action, type);
		object_action (tree->object);
		tree_foreach (tree->right, object_action, type);
	} else if (type == TREE_TRAVERSAL_DEPTH_FIRST_POST_ORDER) {
		tree_foreach (tree->left, object_action, type);
		tree_foreach (tree->right, object_action, type);
		object_action (tree->object);
	}
}

int main (void)
{
	struct tree *tree = tree_make ();
	tree_insert (tree, string_compare, "Esteban");
	tree_insert (tree, string_compare, "David");
	tree_insert (tree, string_compare, "Miguel");
	tree_insert (tree, string_compare, "Carolina");
	tree_insert (tree, string_compare, "Gustavo");
	tree_insert (tree, string_compare, "Eduardo");
	tree_insert (tree, string_compare, "Guillermo");
	tree_insert (tree, string_compare, "Cristian");
	tree_insert (tree, string_compare, "Carlos");
	tree_insert (tree, string_compare, "Giovanni");
	printf ("PRE-ORDER:\n");
	tree_print (tree, string_print, TREE_TRAVERSAL_DEPTH_FIRST_PRE_ORDER);
	printf ("\nIN-ORDER:\n");
	tree_print (tree, string_print, TREE_TRAVERSAL_DEPTH_FIRST_IN_ORDER);
	printf ("\nPOST-ORDER:\n");
	tree_print (tree, string_print, TREE_TRAVERSAL_DEPTH_FIRST_POST_ORDER);
	return 0;
}
