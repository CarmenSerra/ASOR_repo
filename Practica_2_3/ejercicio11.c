// Escribir un programa que bloquee las señales SIGINT y SIGTSTP. Después de bloquearlas el programa debe suspender su ejecución con sleep(3) un número de segundos que se obtendrán de la variable de entorno SLEEP_SECS. 

//Después de despertar de sleep(3), el proceso debe informar de si recibió la señal SIGINT y/o SIGTSTP. En este último caso, debe desbloquearla con lo que el proceso se detendrá y podrá ser reanudado en la shell (imprimir una cadena antes de finalizar el programa para comprobar este comportamiento) 

//Carmen Serrano Aviles

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

//SIGINT = Interrucpcion
//SIGTSTP= Parar el proceso

int main(int argc, char **argv) {



if (argc < 2) {
    printf("Introduce los segundos:\n");
    return -1;
  }

sigset_t s;

//Creamos un conjunto de señales y añadimos las que marca el ejercicio
sigemptyset(&s);
sigaddset(&s, SIGINT);
sigaddset(&s, SIGTSTP);

//Evitamos la recepción de las señales
  sigprocmask(SIG_BLOCK, &s, NULL);

//entorno
char *segs = getenv("SLEEP_SECS");
int se = atoi(segs);


printf("El procesose va a dormir %d segundos\n", se);
sleep(se);


//Checkeamos las pendientes mediante otro conjunto de señales 
  sigset_t pending;
  sigpending(&pending);


if(sigismember(&pending,SIGINT) ==1){
	printf("Se ha recibido una SIGINT\n");
	sigdelset(&s, SIGINT); //La eliminamos del primer conjunto
}else printf("No se ha recibido una SIGINT\n");

if(sigismember(&pending,SIGTSTP) ==1){
	printf("Se ha recibido una SIGTSTP\n");
	sigdelset(&s, SIGTSTP); //La eliminamos del primer conjunto
}else printf("No se ha recibido una SIGTSTP\n");

//Desbloqueamos la mascara
sigprocmask(SIG_UNBLOCK, &s, NULL);
}