#include "system/cores_pthread.h"

/**
 * cores_pthread_make - crear un conjunto de cores
 * @param availables cores disponibles
 * @return Estructura que representa los cores disponibles
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
struct cores_pthread *cores_pthread_make (int availables)
{
	int i;
	struct cores_pthread *cores = malloc(sizeof(struct cores_pthread));
	cores->cores = availables;
	cores->running = 0;
	cores->threads = malloc(sizeof(pthread_t)*cores->cores);
	for (i=0; i < cores->cores; ++i)
		cores->threads[i] = 0;
	pthread_mutex_init (&cores->mutex, NULL);
	return cores;
}

/**
 * cores_pthread_destroy - destruye los cores
 * @param cores estructura de cores
 * @return 0 en caso de éxito, 1 en caso de error
 * @warning no se está liberando la memoria
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
short int cores_pthread_destroy (struct cores_pthread *cores)
{
	pthread_mutex_lock (&cores->mutex);
	if (cores->running) {
		pthread_mutex_unlock (&cores->mutex);
		return 1;
	}
	/*free (cores->threads);*/
	pthread_mutex_unlock (&cores->mutex);
	/*free (cores);*/
	return 0;
}

/**
 * core_pthread_wait - esperar hasta que termine la ejecución del core
 * @param cores estructura de cores
 * @param core core por el que se está esperando
 * @return Entrega el retorno del core o bien -1 en caso que no haya retorno
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
int core_pthread_wait (struct cores_pthread *cores, int core)
{
	int *rc = NULL;
	pthread_join (cores->threads[core], (void **)&rc);
	cores->threads[core] = 0;
	return rc != NULL ? *rc : -1;
}

/**
 * cores_pthread_wait - esperar por que terminen todos los cores
 * @param cores estructura de cores
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void cores_pthread_wait (struct cores_pthread *cores)
{
	int i;
	for (i=0; i < cores->cores; ++i)
		core_pthread_wait (cores, i);
}

/**
 * core_pthread_main - wrapper para el código que se cargará en el core
 * @param args argumentos para la función en el core (core_pthread_main_args)
 * @return Puntero a cualquier cosa que sea entregada por la función del thread
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void *core_pthread_main (void *args)
{
	int *rc = malloc(sizeof(int));
	struct core_pthread_main_args *core_main_args = args;
	struct cores_pthread *cores = core_main_args->cores;
	*rc = (core_main_args->func)(core_main_args->args);
	free(core_main_args);
	pthread_mutex_lock (&cores->mutex);
	cores->running--;
	pthread_mutex_unlock(&cores->mutex);
	pthread_exit(rc);
	return NULL;
}

/**
 * core_pthread_run - ejecutar código en el primer core disponible
 * @param cores estructura de cores
 * @param core_main función con el código que se ejecutará en el core
 * @param args argumentos que se pasarán a la función que se cargará en el core
 * @return 0 en caso de éxito, 1 en caso de error
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
short int core_pthread_run (struct cores_pthread *cores, int core,
					int(core_main)(void *), void *args)
{
	pthread_t thread;
	struct core_pthread_main_args *core_main_args =
				malloc(sizeof(struct core_pthread_main_args));
	int rc;
	pthread_mutex_lock (&cores->mutex);
	if (cores->threads[core]!=0) {
		pthread_mutex_unlock(&cores->mutex);
		return 1;
	}
	core_main_args->func = core_main;
	core_main_args->args = args;
	core_main_args->cores = cores;
	pthread_mutex_unlock(&cores->mutex);
	rc = pthread_create(&thread, NULL, core_pthread_main, core_main_args);
	if (!rc) {
		pthread_mutex_lock (&cores->mutex);
		cores->threads[core] = thread;
		cores->running++;
		pthread_mutex_unlock(&cores->mutex);
		return 0;
	}
	return 1;
}

/**
 * cores_pthread_first_free - buscar primer core libre (se debe sincronizar)
 * @param cores estructura de cores
 * @return Índice del primer core disponible (si proceso en ejecución)
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
int cores_pthread_first_free (struct cores_pthread *cores)
{
	int i = 0;
	for (i=0; i < cores->cores; ++i)
		if (!cores->threads[i])
			return i;
	return -1;
}
