#include "sync/semaphore_sl.h"

/**
 * semaphore_sl_make - crear un semáforo
 * @param tickets cantidad de tickets iniciales del semáforo
 * @return Semáforo
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
struct semaphore_sl *semaphore_sl_make (int tickets)
{
	struct semaphore_sl *s = malloc(sizeof(struct semaphore_sl));
	s->tickets = tickets;
	s->queue = list_make ();
	spin_lock_init (&s->sl, SPINLOCK_OPEN);
	return s;
}

/**
 * semaphore_sl_wait - solicitar un ticket del semáforo
 * @param s semáforo
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void semaphore_sl_wait (struct semaphore_sl *s)
{
	struct spinlock wait_lock;
	spin_lock(&s->sl);
	while (s->tickets <= 0) {
		spin_lock_init (&wait_lock, SPINLOCK_CLOSED);
		list_put (s->queue, &wait_lock);
		spin_unlock(&s->sl);
		spin_lock(&wait_lock);
		spin_lock(&s->sl);
	}
	s->tickets--;
	spin_unlock(&s->sl);
}

/**
 * semaphore_sl_signal - entregar un ticket al semáforo
 * @param s semáforo
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void semaphore_sl_signal (struct semaphore_sl *s)
{
	spin_lock(&s->sl);
	s->tickets++;
	if (!list_empty(s->queue)) {
		spin_unlock(list_get (s->queue));
	}
	spin_unlock(&s->sl);
}

/**
 * semaphore_sl_destroy - destruye el semáforo
 * @param s semáforo
 * @return 0 en caso de éxito, 1 en caso de error
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
short int semaphore_sl_destroy (struct semaphore_sl *s)
{
	if (!list_empty(s->queue))
		return 1;
	free(s);
	return 0;
}
