 //Crear otra tubería con nombre. Escribir un programa que espere hasta que haya datos listos para leer en alguna de ellas. El programa debe mostrar la tubería desde la que leyó y los datos leídos.
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

	if( mkfifo("tuberia1", 0644) == -1){
		perror("Error creando las tuberías\n");
		return -1;
	}
	if(mkfifo("tuberia2", 0644) ==-1){
		perror("Error creando las tuberías\n");
		return -1;
	}

	int desc_dispo = 0;
	char buffer[257];
	
	  int pipe1 = open("tuberia1", O_RDONLY | O_NONBLOCK);
  	  int pipe2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
          int num_pipe;

	while(desc_dispo !=-1){
		fd_set conjunto_desc;

		FD_ZERO(&conjunto_desc);
		FD_SET(pipe1, &conjunto_desc);
		FD_SET(pipe2, &conjunto_desc);

		int actual;
		int pipe_elegida;
		
		//Debo averiguar cual de las dos tuberias es mayor 
		if (pipe1 >pipe2) pipe_elegida = pipe1+1;
		else pipe_elegida = pipe2+1;
		
		//El select me devuelve los descriptores accesibles
		desc_dispo = select(pipe_elegida, &conjunto_desc,0,0,0);

		//Mientras que haya alguno
		if (desc_dispo > 0){
			//Compruebo si  es la pipe 1 la que está lista
			if(FD_ISSET(pipe1,&conjunto_desc)){
			num_pipe = 1;
			actual = pipe1;
			}
			//Compruebo si es la pipe 1 la que está lista
			if(FD_ISSET(pipe2,&conjunto_desc)){
			num_pipe = 2;
			actual = pipe2;
			}

			ssize_t lectura = 256;
			//Creo el buffer para su posterior lectura y muestro en que tuberia estoy escribiendo
			while( lectura == 256){
			lectura = read(actual,buffer,256);
			buffer[lectura] ='\0';
			printf("Escribo en tuberia %i: %s", num_pipe, buffer);
			}
			//Compruebo en que pipe tengo que escribir para abrir con el open
			if( lectura != 256 && num_pipe ==1){
			close(pipe1);
       			 pipe1 = open("tuberia1", O_RDONLY | O_NONBLOCK);
				if (pipe1 == -1) {
					perror("No se puede abrir la primera tub");
					close(pipe1);
					close(pipe2);
					return -1;
				}
			}
			if( lectura != 256 && num_pipe ==2){
			close(pipe2);
       			 pipe2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
				if (pipe1 == -1) {
					perror("No se puede abrir la segunda tub");
					close(pipe1);
					close(pipe2);
					return -1;
				}
			}

		}

		
	}
close(pipe1);
close(pipe2);
return 0;
}
