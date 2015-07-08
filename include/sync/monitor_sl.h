#ifndef __MONITOR_SL_H__
#define __MONITOR_SL_H__

#include <stdlib.h>
#include "datatypes/structures/list.h"
#include "arch/spinlock.h"

#ifndef monitor
#define monitor monitor_sl
#define monitor_make monitor_sl_make
#define monitor_enter monitor_sl_enter
#define monitor_exit monitor_sl_exit
#define monitor_wait monitor_sl_wait
#define monitor_notify_all monitor_sl_notify_all
#define monitor_destroy monitor_sl_destroy
#endif

/**
 * struct monitor_sl - representación de monitor manejado con spinlocks
 * @list: lista de quienes esperan por el monitor
 * @sl: spinlock para controlar el acceso al monitor
 */
struct monitor_sl {
	struct list *list;
	struct spinlock sl;
};

struct monitor_sl *monitor_sl_make ();
void monitor_sl_enter (struct monitor_sl *m);
void monitor_sl_exit (struct monitor_sl *m);
void monitor_sl_wait (struct monitor_sl *m);
void monitor_sl_notify_all (struct monitor_sl *m);
short int monitor_sl_destroy (struct monitor_sl *m);

#endif
