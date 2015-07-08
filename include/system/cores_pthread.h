#ifndef __CORES_PTHREAD_H__
#define __CORES_PTHREAD_H__

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#ifndef cores
#define cores cores_pthread
#define cores_destroy cores_pthread_destroy
#define cores_make cores_pthread_make
#define cores_wait cores_pthread_wait
#define core_run core_pthread_run
#define core_wait core_pthread_wait
#endif

/**
 * struct cores_pthread - representación de los núcleos mediante threads
 * @cores: cantidad de core disponibles
 * @running: cuantos cores están ejecutando código (una función)
 * @threads: código en ejecución en cada core
 * @mutex: mutex para controlar el acceso a la estructura
 */
struct cores_pthread {
	int cores;
	int running;
	pthread_t *threads;
	pthread_mutex_t mutex;
};

/**
 * struct core_pthread_main_args - argumentos para la funciónde pthread_create
 * @func: función que se ejecutará dentro del core
 * @args: argumentos que se pasarán a ña función que se cargará en el core
 * @cores: puntero a la estructura cores_pthread
 */
struct core_pthread_main_args {
	int (*func)(void *);
	void *args;
	struct cores_pthread *cores;
};

struct cores_pthread *cores_pthread_make (int availables);
short int cores_pthread_destroy (struct cores_pthread *cores);
int core_pthread_wait (struct cores_pthread *cores, int core);
void cores_pthread_wait (struct cores_pthread *cores);
void *core_pthread_main (void *args);
short int core_pthread_run (struct cores_pthread *cores, int core,
					int(core_main)(void *), void *args);
int cores_pthread_first_free (struct cores_pthread *cores);

#endif
