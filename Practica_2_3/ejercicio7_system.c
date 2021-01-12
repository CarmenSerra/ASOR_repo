#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {


  if (argc < 2) {
    printf("ERROR: Introduce el comando.\n");
    return -1;
  }

  //Reservamos espacio en memoria mediante malloc en funcion de lo que nos pasen en pantalla
   int long_cmd =1;
   int i;

   for( i =1; i< argc; i++){
	long_cmd += strlen(argv [i] +1);
     }
   char *cmd = malloc(sizeof(char)*long_cmd);
   strcpy(cmd,""); // Inicializo


  //Concatenamos con strcat

   for (i=1; i< argc; i++){
	strcat(cmd,argv[i]);
	strcat(cmd," ");
    }
  
  //Ejecutamos con system 

    if(system(cmd) == -1){
	printf("No se ha podido ejecutar el comando .\n");
}

	printf("Se ha ejecutado el comando y ya ha terminado.\n");
return 0;
}