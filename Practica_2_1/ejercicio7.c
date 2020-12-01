#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main (){

//pathconf



//num maximo de enlaces _PC_LINK_MAX
// tam maximo de una ruta  _PC_PATH_MAX
// tam max el nombre de un fichero _PC_NAME_MAX


char *ruta = "/home/cursoredes/Documents/Pr2_1";

long max_enlaces;
long tam_max_ruta;
long nom_fichero; 

max_enlaces = pathconf(ruta,_PC_LINK_MAX);
tam_max_ruta=   pathconf(ruta,_PC_PATH_MAX);
nom_fichero=   pathconf(ruta,_PC_NAME_MAX);

printf("Num max de enlaces %li\n", max_enlaces);
printf("Tam max de una ruta %li\n", tam_max_ruta);
printf("Tam max de una ruta %li\n", nom_fichero);

return 1;
}