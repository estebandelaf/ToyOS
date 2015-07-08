#ifndef __SPINLOCK_H__
#define __SPINLOCK_H__

#define SPINLOCK_OPEN 0
#define SPINLOCK_CLOSED 1

/**
 * struct spinlock - estructura para utilizar spinlocks
 * @lock: candado para el spinlock
 */
struct spinlock {
	long lock;
};

extern void _spin_lock_init (struct spinlock *sl, int status);
#define spin_lock_init _spin_lock_init
extern void _spin_lock (struct spinlock *sl);
#define spin_lock _spin_lock
extern void _spin_unlock (struct spinlock *sl);
#define spin_unlock _spin_unlock

#endif
