//Escribir un programa que consulte y muestre en pantalla el estado del cerrojo sobre un fichero usando lockf(3). El programa mostrará el estado del cerrojo (bloqueado o desbloqueado). Además:

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

       int lockf(int fd, int cmd, off_t len);

int main(int argc, char **argv) {



	if (argc < 2){
	printf("Error: No se ha especificado la ruta del archivo. Introducir de nuevo");
	return -1;
	}

	int fd = open(argv[1], O_CREAT | O_RDWR);

	int cmd = F_TLOCK;
	off_t len;
	int cerr = lockf(fd, cmd, len);

	if(cerr == -1){
	printf("La región está bloqueada");	
	}


	return 0;
}