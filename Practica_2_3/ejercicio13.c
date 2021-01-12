// Escribir un programa que realice el borrado programado del propio ejecutable. El programa tendrá como argumento el número de segundos que esperará antes de borrar el fichero. El borrado del fichero se podrá detener si se recibe la señal SIGUSR1.


//Carmen Serrano Aviles
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int parar = 0;

void manejador( int s){
	if ( s == SIGUSR1) parar =1;
}


int main(int argc, char **argv) {


if (argc < 2) {
    printf("Introduce los segundos:\n");
    return -1;
  }

sigset_t sa;
sigemptyset(&sa);
sigaddset(&sa, SIGUSR1);
sigprocmask(SIG_UNBLOCK, &sa, NULL);


//Manejador
struct sigaction s;
sigaction(SIGUSR1, NULL, &s);
s.sa_handler = manejador;
sigaction(SIGUSR1, &s, NULL);


int segs = atoi(argv[1]);
sleep (segs);

//borrado del programado del propio ejecutable,

if (parar == 0){
printf("Borrando \n");
unlink(argv[0]);
}else printf("Se ha detenido el borrado");


return 0;
}