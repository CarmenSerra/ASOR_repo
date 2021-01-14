//El padre leerá de la entrada estándar (terminal) y enviará el mensaje al proceso hijo, escribiéndolo en la tubería p_h. Entonces permanecerá bloqueado esperando la confirmación por parte del hijo en la otra tubería, h_p.
//El hijo leerá de la tubería p_h, escribirá el mensaje por la salida estándar y esperará 1 segundo. Entonces, enviará el carácter ‘l’ al proceso padre, escribiéndolo en la tubería h_p, para indicar que está listo. Después de 10 mensajes enviará el carácter ‘q’ para indicar al padre que finalice.

//Carmen Serrano Aviles

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv) {


	int padre_hijo[2];
	int hijo_padre[2];
//Creo primero la tubería porque si no debajo del fork no compartirían los descriptores y tendrían tuberías diferentes, y queremos que compartan la misma

	if (pipe(padre_hijo) == -1 || pipe(hijo_padre) == -1){

		perror("Error al crear las tuberías\n");
	}
	
	pid_t pid = fork();



	switch (pid) {
	    case -1:
		perror("error en el fork()\n");
		return -1;
	    case 0:
	 	//HIJO
		close(hijo_padre[0]); //cierro extremo lectura del h_p
		close(padre_hijo[1]);//cierro extremo escritura del p_h
		
		char recibido_usr_mensaje[257];
		char padre_mensaje[1] = {'l'};

		int i;
		for ( i = 0; i< 10; i++){
			ssize_t c_size = read(padre_hijo[0], recibido_usr_mensaje,256);
			if (c_size == -1) {
				perror("Error en hijo al leer de tuberia");
				exit(-1);
				}
			recibido_usr_mensaje[c_size] = '\0';
			
			printf("En hijo, msje de padre: %s", recibido_usr_mensaje);
			sleep(1);

			if ( i == 9 ) padre_mensaje[0] = 'q';
			c_size = write(hijo_padre[1], padre_mensaje, 1);
				if (c_size == -1) {
					perror("Errr en hijo escribiendo en tuberia");
					exit(-1);
				}
			}

			close(padre_hijo[0]);
			close(hijo_padre[1]);
			exit(0);
		

	
	     break;

	     default:	
		//PADRE
		close(hijo_padre[1]); //cierro extremo escritura del h_p
		close(padre_hijo[0]); //cierro extremo lectura del p_h
		
		char usuario_mensaje[257];
		char hijo_mensaje[1] = {'l'};

		while(hijo_mensaje[0] != 'q'){

			//Leo entrada estandar y guardo en usuario_mensaje
			ssize_t p_size = read(0,usuario_mensaje,256); 
			if (p_size == -1) {
				perror("Error en padre leyendo entrada user\n");
				exit(-1);
			}

			usuario_mensaje[p_size] = '\0';
			//Escribo en el [1] del pipe, que es escritura el mensaje
			p_size = write(padre_hijo[1],usuario_mensaje, p_size+1);
			if (p_size == -1) {
				perror("Error en padre escribiendo en pipe p_h");
				exit(-1);
			}

			while(hijo_mensaje[0] != 'l' && hijo_mensaje[0] != 'q'){
				//Leo desde el punto de lectrura del pipe h_p
				p_size = read(hijo_padre[0],hijo_mensaje,1);
				if (p_size == -1) {
					perror("Error en padre leyendo de pipe");
					exit(-1);
				}

			}

		}	

		//cierro los otros extremos
		close(hijo_padre[0]); 
		close(padre_hijo[1]); 
		exit(0);
		

	}


return 0;
}
