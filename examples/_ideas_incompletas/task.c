#include <stdio.h>
#include <strings.h>
/*#include <linux/sched.h>
#include <linux/unistd.h>*/

#define TASK_RUNNING 0
#define TASK_INTERRUPTIBLE 1
#define TASK_UNINTERRUPTIBLE 2
#define TASK_STOPED 3
#define TASK_ZOMBIE 4
#define TASK_SWAPING 5

struct list *init_task;

#define TASK_MAX_PROCESS 65536

/*
 * struct task - estructura para representar un proceso
 * @state: estado actual del proceso (macros TASK_*)
 * @counter: tiempo que le queda al proceso en ejecución
 * @priority: prioridad estática del proceso
 * @errno: variable para indicar el tipo de error que ha ocurrido
 * @pid: identificador del proceso
 */
struct task {
	short int state;
	long counter;
	short int priority;
	int errno;
	unsigned short int pid;
};

int task_main (void *args) {
	return 0;
}

int main ()
{	
/*	int task_pid = -1;
	void *task_stack = NULL;
	int task_flags = CLONE_VM | CLONE_SIGHAND | CLONE_NEWPID;
	void *task_args = NULL;
	task_pid = clone(task_main, task_stack, task_flags, task_args);
	if (task_pid<0) {
		perror("[error]: ");
		return EXIT_FAILURE;
	} else {
		printf("Tarea creada con PID %d\n", task_pid);
	}*/
	return 0;
}
