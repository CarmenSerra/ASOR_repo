//Escribir un programa que emule el comportamiento de la shell en la ejecución de una sentencia en la forma: comando1 argumento1 | comando2 argumento2. El programa creará una tubería sin nombre y creará un hijo:
//El proceso padre redireccionará la salida estándar al extremo de escritura de la tubería y ejecutará comando1 argumento1.
//El proceso hijo redireccionará la entrada estándar al extremo de lectura de la tubería y ejecutará comando2 argumento2.


//Carmen Serrano Aviles

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv) {

 if (argc < 4) {
    printf("Introduce el comando.\n");
    return -1;
  }

	int fd[2];
//Creo primero la tubería porque si no debajo del fork no compartirían los descriptores y tendrían tuberías diferentes, y queremos que compartan la misma

	if( pipe(fd) ==-1){
		perror("Error en pipe()\n");
	}

	pid_t pid = fork();



	switch (pid) {
	    case -1:
		perror("error en el fork()\n");
		return -1;
	    case 0:
	 	//HIJO
		dup2(fd[1],1); //descriptor de fichero de entrada y entrada estandar
		close(fd[1]);
		close(fd[0]);
		//Ejecutamos mediante lista porque sabemos que siempre van a entrar esos X argumentos
		execlp(argv[1], argv[1], argv[2], NULL);
	
	     break;

	     default:	
		//PADRE
		//No necesitamos el wait porque ya se hace la sincronización mediante la escritura y lectura

		dup2(fd[0],0);
		

		close(fd[0]);
		close(fd[1]);

		execlp(argv[3], argv[3], argv[4], NULL);
	
	     break;

	}


return 0;
}
