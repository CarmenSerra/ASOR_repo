//Usando la versión con execvp(3) del ejercicio 7 y la plantilla de demonio del ejercicio 6, escribir un programa que ejecute cualquier programa como si fuera un demonio. Además, redirigir los flujos estándar asociados al terminal usando dup2(2):
//La salida estándar al fichero /tmp/daemon.out.
//La salida de error estándar al fichero /tmp/daemon.err.
//La entrada estándar a /dev/null.
//Comprobar que el proceso sigue en ejecución tras cerrar la shell.

//Carmen Serrano Aviles

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 

int main(int argc, char **argv) {


 if (argc < 2) {
    printf("Introduce el comando.\n");
    return -1;
  }

pid_t pid = fork();
pid_t sesion;
int status;

switch (pid) {
    case 0:
 	//HIJO
	sesion = setsid(); //creando sesion 
	int dir_n = chdir("/tmp");
	
	//La entrada estándar a /dev/null.
	int demonio_entrada = open("/dev/null", O_RDONLY);
	int demonio_salida = open("/tmp/daemon.out", O_WRONLY | O_CREAT);
	int demonio_error = open("/tmp/daemon.err", O_WRONLY | O_CREAT);
	if(demonio_entrada == -1 || demonio_salida == -1 || demonio_error == -1){
		close(demonio_entrada);
		close(demonio_salida);
		close(demonio_error);
	}
	//Creando las copias de los descriptores de fichero 
	int dup_entrada = dup2(demonio_entrada, 0 );
	int dup_salida = dup2(demonio_salida,1); 
	int dup_error = dup2(demonio_error,2);

	if (execvp(argv[1],argv +1) == -1){
		printf("No se ha podido ejecutar correctamente.\n");
	}
     break;

     default:	
	//PADRE
	wait(&status); 
	if(status == -1){
		printf("Ha fallado el comando");
	}
	
	printf("Ya ha terminado de ejecutarse\n");

     break;

}


return 0;
}