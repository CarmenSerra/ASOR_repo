//Escribir dos versiones, una con system(3) y otra con execvp(3), de un programa que ejecute otro programa que se pasará como argumento por línea de comandos. En cada caso, se debe imprimir la cadena “El comando terminó de ejecutarse” después de la ejecución. ¿En qué casos se imprime la cadena? ¿Por qué? 
//Carmen Serrano aviles


#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>



int main(int argc, char **argv) {

//int execvp(const char *file, char *const argv[]);


if (argc < 2) {
    printf("ERROR: Introduce el comando.\n");
    return -1;
  }


if (execvp(argv[1],argv +1) == -1){
	printf("No se ha podido ejecutar correctamente.\n");

}

printf("Ya ha terminado.\n");

return 0;
}