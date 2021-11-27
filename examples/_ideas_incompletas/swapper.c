/*Tal cual tu lo dices, el spinlock usa 100% de la máquina, incluso con la
instrucción pause. Incluso yendo un poco mas lejos, lo que el monitor del
sistema muestra como "idle" es la ejecución de una tarea que siempre está en la
cola de procesos, llamada la tarea "swapper" o "idle process" (de pid 0).
La función de esta tarea durante el arranque del sistema es inicializar el
kernel y crear el proceso de pid 1 (init). Luego de esto, se coloca siempre en
las colas de procesos listos para ejecutar, cosa de que tome el control en
cuanto la máquina se quede sin tareas que ejecutar.

La gracia de este proceso swapper es que ejecuta una función llamada cpu_idle(),
la cual es básicamente la ejecución de la instrucción de máquina "hlt"
http://en.wikipedia.org/wiki/HLT. Esta instrucción coloca la CPU en un modo de
bajo consumo para esperar a la siguiente interrupción de hardware que llegue.
Además, como bien lo dices, hlt es una función que corre en ring 0, es decir,
con permisos elevados. */
