// Escribir un programa que muestre los identificadores del proceso: identificador de proceso, de proceso padre, de grupo de procesos y de sesión. Mostrar además el número máximo de ficheros que puede abrir el proceso y el directorio de trabajo actual.
//Carmen Serrano Avilés
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <sys/resource.h>



int main(int argc, char **argv) {


//-id proceso
pid_t pid = getpid();
printf("Id del proceso: %i\n", pid);

//-id proceso padre
pid_t pid_padre  = getppid();
printf("Id del proceso padre: %i\n", pid_padre);


//- id grupo de procesos
pid_t  pid_grupo  = getpgid(pid);
printf("Id grupo proceso: %i\n", pid_grupo);


//_id sesión.
pid_t sesion =  getsid(pid);
printf("Id sesion proceso: %i\n", sesion);

//Num max ficheros que puede abrir el proceso
struct rlimit limite_fich;
getrlimit(RLIMIT_NOFILE, &limite_fich);

printf("Num max de ficheros: %li\n", limite_fich.rlim_max);




return 0;
}