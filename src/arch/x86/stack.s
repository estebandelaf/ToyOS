# Declarar rutinas como globales (para ser vistas desde C)
.globl _stack_swap

# Rutina que intercambia las pilas de dos procesos
# TODO: implementar (verificar parámetros)
# void _stack_swap (struct stack *sp1, struct stack *sp2);
# rdi = sp1
# rsi = sp2
_stack_swap:
	ret
