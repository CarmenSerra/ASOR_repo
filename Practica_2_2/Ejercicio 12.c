// Escribir un programa que redirija la salida estándar a un fichero cuya ruta se pasa como primer argumento. Probar haciendo que el programa escriba varias cadenas en la salida estándar.

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


       int dup(int oldfd);
       int dup2(int oldfd, int newfd);

int main(int argc, char **argv) {

	if (argc < 2){
	printf("Error: No se ha especificado la ruta del archivo. Introducir de nuevo");
	return -1;
	}

	int destino = open(argv[1], O_CREAT | O_RDWR);
	
	//La salida estándar = 1;
	if( destino == -1){
	printf("No se ha podido abrir o crear el archivo");	
	}	

	int fd2 = dup2(destino, 1);

	printf("Voy a escribir en el fichero especificado");
	
	dup2(fd2,destino);


return 0;
}