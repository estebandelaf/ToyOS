# Autor original: Diego Rivera Villagra (drivera[at]dcc.uchile.cl)

# Declarar rutinas como globales (para ser vistas desde C)
.globl _spin_lock_init
.globl _spin_lock
.globl _spin_unlock

# Rutina que inicializa el spinlock
# void _spin_lock_init (struct spinlock *sl, int status);
# rdi = sl
# rsi = status
_spin_lock_init:
	movq %rsi, (%rdi)
	ret

# Rutina que solicita el spinlock (realiza busy-waiting)
# void _spin_lock (struct spinlock *sl);
# rdi = sl
_spin_lock:
	pause
	movq $1, %rax
	lock xchgq (%rdi), %rax # exchange/swap %rdi with %rax (¡atómico!)
	test %rax, %rax # test %rax, %rax will set ZF if rax = 0
	jnz _spin_lock # jump when ZF is equal to 0 (ZF is not set)
	ret

# Rutina que libera el spinlock
# void _spin_unlock (struct spinlock *sl);
# rdi = sl
_spin_unlock:
	movq $0, %rax
	lock xchgq (%rdi), %rax
	ret
