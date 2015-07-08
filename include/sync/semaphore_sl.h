#ifndef __SEMAPHORE_SL_H__
#define __SEMAPHORE_SL_H__

#include <stdlib.h>
#include "datatypes/structures/list.h"
#include "arch/spinlock.h"

#ifndef semaphore
#define semaphore semaphore_sl
#define semaphore_make semaphore_sl_make
#define semaphore_wait semaphore_sl_wait
#define semaphore_signal semaphore_sl_signal
#define semaphore_destroy semaphore_sl_destroy
#endif

/**
 * struct semaphore_sl - representación de semáforo manejado con spinlocks
 * @tickets: cantidad de tickets disponibles en el semáforo
 * @queue: cola fifo para quienes esperan por el semáforo
 * @sl: spinlock para controlar el acceso al semáforo
 */
struct semaphore_sl {
	int tickets;
	struct list *queue;
	struct spinlock sl;
};

struct semaphore_sl *semaphore_sl_make (int tickets);
void semaphore_sl_wait (struct semaphore_sl *s);
void semaphore_sl_signal (struct semaphore_sl *s);
short int semaphore_sl_destroy (struct semaphore_sl *s);

#endif
