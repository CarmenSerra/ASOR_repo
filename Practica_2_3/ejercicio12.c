// Escribir un programa que instale un manejador sencillo para las señales SIGINT y SIGTSTP. El manejador debe contar las veces que ha recibido cada señal. El programa principal permanecerá en un bucle que se detendrá cuando se hayan recibido 10 señales. El número de señales de cada tipo se mostrará al finalizar el programa.

//Carmen Serrano Aviles
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static volatile int contador_int =0; //Global para que sea compartida
static volatile int contador_stp =0; //Global para que sea compartida

void contar(int s){
 	if( s == SIGINT)  contador_int++;
 	if( s == SIGTSTP)  contador_stp++;
}


int main(int argc, char **argv) {
int max = 10;
//Instalar manejador
struct sigaction s;

s.sa_handler = contar; // manejador
s. sa_flags = SA_RESTART; //que se reinicie la anterior llamada si entra la señal justo

sigaction(SIGINT,&s, 0);
sigaction(SIGTSTP,&s, 0);


while( contador_int + contador_stp < max){

}

printf("El numero de veces que se ha recibido SIGINT: %i\n", contador_int);
printf("El numero de veces que se ha recibido SIGTSTP: %i\n", contador_stp);



return 0;
}