//Escribir un programa que muestre la política de planificación (como cadena) y la prioridad del proceso actual, además de mostrar los valores máximo y mínimo de la prioridad para la política de planificación. 

//Carmen Serrano Avilés

#include <sched.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>



int main(int argc, char **argv) {

int plani_i;
pid_t pid = getpid(); //Obtengo el pid del proceso para obtener la planificacion
printf("Proceso %d\n", pid);

plani_i = sched_getscheduler(pid);
char plani[10];

sprintf(plani,"%d",plani_i);

printf("Politica planificacion: %c\n", plani);

int prio_proc = getpriority(PRIO_PROCESS, pid);

printf("Prioridad del proceso: %d\n", prio_proc);

int max = sched_get_priority_max(plani_i);
int min = sched_get_priority_min(plani_i);


printf("Max prio politica: %d\n", max);
printf("Min prio politica: %d\n", min);

return 0;
}