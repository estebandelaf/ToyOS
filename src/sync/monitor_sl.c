#include "sync/monitor_sl.h"

/**
 * monitor_sl_make - crear un monitor
 * @return Monitor
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
struct monitor_sl *monitor_sl_make ()
{
	struct monitor_sl *m = malloc(sizeof(struct monitor_sl));
	m->list = list_make ();
	spin_lock_init (&m->sl, SPINLOCK_OPEN);
	return m;
}

/**
 * monitor_sl_enter - solicitar la propiedad sobre el monitor
 * @param m monitor
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void monitor_sl_enter (struct monitor_sl *m)
{
	spin_lock (&m->sl);
}

/**
 * monitor_sl_exit - liberar la propiedad del monitor
 * @param m monitor
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void monitor_sl_exit (struct monitor_sl *m)
{
	spin_unlock (&m->sl);
}

/**
 * monitor_sl_wait - liberar monitor y esperar
 * @param m monitor
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void monitor_sl_wait (struct monitor_sl *m)
{
	struct spinlock wait_lock;
	spin_lock_init (&wait_lock, SPINLOCK_CLOSED);
	list_put (m->list, &wait_lock);
	spin_unlock (&m->sl);
	spin_lock (&wait_lock);
	spin_lock (&m->sl);
}

/**
 * monitor_sl_notify_all - desbloquear a todos los que esperan por el monitor
 * @param m monitor
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
void monitor_sl_notify_all (struct monitor_sl *m)
{
	while (!list_empty(m->list))
		spin_unlock (list_get(m->list));
}

/**
 * monitor_sl_destroy - destruir monitor
 * @param m monitor
 * @return 0 en caso de éxito, 1 en caso de error
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2013-05-24
 */
short int monitor_sl_destroy (struct monitor_sl *m)
{
	if (!list_empty(m->list))
		return 1;
	free(m);
	return 0;
}
