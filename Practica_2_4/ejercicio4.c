//Escribir un programa que abra la tubería con el nombre anterior en modo sólo escritura, y escriba en ella el primer argumento del programa. En otro terminal, leer de la tubería usando un comando adecuado.


//Carmen Serrano Aviles

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>



int main(int argc, char **argv) {


		if (argc < 2) {
		    printf("Error, introduce escritura.\n");
		    return -1;
		  }

		int fd;
	
		//Para las tuberías sin nombre se abren con el open y los descriptores
		fd = open("tub", O_WRONLY);
		if (fd == -1) {
		   perror("Error abriendo la tuberia\n");
		   close(fd);
		    return -1;
		  }
	
		size_t tam_entrada = strlen(argv[1]);
		ssize_t escritura = write(fd, argv[1], tam_entrada);
		
		if (escritura == -1) {
		perror("Error escribiendo en la tubería");
		close(fd);
		return -1;
	}

		close(fd);



return 0;
}
