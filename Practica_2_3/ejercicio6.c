//Escribir una plantilla de demonio (creación del nuevo proceso y de la sesión) en el que únicamente se muestren los atributos del proceso (como en el ejercicio anterior). Además, fijar el directorio de trabajo del demonio a /tmp.

//Carmen Serrano Avilés
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <sys/time.h>


int main(int argc, char **argv) {
//crear nuevo proceso
pid_t pid;
pid = fork();
pid_t sesion;

switch (pid) {
    case 0:
      //crear nueva sesión 
	sesion = setsid();
      //Fijar directorio de trabajo al proceso creado, al demonio a /tmp
	 chdir("/tmp");

	//mostrar solo los atributos del proceso HIJO
	printf("Id del proceso: %i\n", pid);
	pid_t pid_padre  = getppid();
	printf("Id del proceso padre: %i\n", pid_padre);
	pid_t  pid_grupo  = getpgid(pid);
	printf("Id grupo proceso: %i\n", pid_grupo);
     break;

     default:
	
	//mostrar solo los atributos del proceso PADRE
	printf("Id del proceso: %i\n", getpid());
	//pid_t pid_padre_2  = getppid();
	printf("Id del proceso padre: %i\n", getppid());
	//pid_t  pid_grupo_2  = getpgid(getpid());
	printf("Id grupo proceso: %i\n", getpgid(getpid())); 
     break;

}

return 0;
}