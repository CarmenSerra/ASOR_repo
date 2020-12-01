#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main (){


long args_max;
long fich_max;
long proc_max;

//longitud maxima de argumentos : _SC_ARG_MAX
args_max = sysconf(_SC_ARG_MAX);

// num max de ficheros abiertos por proceso _SC_OPEN_MAX
fich_max = sysconf(_SC_OPEN_MAX);

//num max d procesos simultaneos por user : _SC_CHILD_MAX
proc_max = sysconf(_SC_CHILD_MAX);

printf("Longitud maxima de argumentos: %li\n", args_max);
printf("Num máximo de ficheros abiertos por proceso: %li\n", fich_max);
printf("Num maximo de procesos simultaneos: %li\n", proc_max);

return 1;
}
	