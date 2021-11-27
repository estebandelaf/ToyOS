# Autor original: Diego Rivera Villagra (drivera[at]dcc.uchile.cl)
# TODO: probar en máquina de 32 bits

# Declarar rutinas como globales (para ser vistas desde C)
.globl _spin_lock_init
.globl _spin_lock
.globl _spin_unlock

# Rutina que inicializa el spinlock
# void _spin_lock_init (struct spinlock *sl, int status);
# ebx = sl
# ecx = status
# TODO: cambiar para asignar directametne, sin usar lock xchgl (agregar algo
# como push %ecx y luego pasar lo de ese registro al ebx, CONFIRMAR ESTO)
_spin_lock_init:
	pushl %ebx
	movl $0, %eax
	movl 8(%ebp), %ebx
	lock xchgl (%ebx), %eax
	popl %ebx
	ret

# Rutina que solicita el spinlock (realiza busy-waiting)
# void _spin_lock (struct spinlock *sl);
# ebx = sl
_spin_lock:
	pushl %ebx
	__spin_lock:
		pause
		movl $1, %eax
		movl 8(%ebp), %ebx
		lock xchgl (%ebx), %eax
		test %eax, %eax
		jnz __spin_lock
	popl %ebx
	ret

# Rutina que libera el spinlock
# void _spin_unlock (struct spinlock *sl);
# ebx = sl
_spin_unlock:
	pushl %ebx
	movl $0, %eax
	movl 8(%ebp), %ebx
	lock xchgl (%ebx), %eax
	popl %ebx
	ret
