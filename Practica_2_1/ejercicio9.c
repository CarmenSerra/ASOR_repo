#include<unistd.h>
#include<sys/types.h>
#include <string.h>
#include <stdio.h>

int main (){

//uid real del user 
//uid efectivo  del user
  printf("Real: %d\n", getuid());
  printf("Efectivo: %d\n", geteuid());

return 1;
}


//Para saber  con certeza que el fichero del programa tiene activado el bit "setuid" hay que comprobar si el uid es distinto el real del efectivo.