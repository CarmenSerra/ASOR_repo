//Ejercicio 9. Añadir la lógica necesaria en el servidor para que no quede ningún proceso en estado zombie. Para ello, se deberá capturar la señal SIGCHLD y obtener la información de estado de los procesos hijos finalizados.


#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


void controlador(int senial){
  pid_t pid;

  pid = wait(NULL);

   printf("Ha salido el pid.\n");//, pid);
}



int main(int argc, int**argv){

struct addrinfo filtro;
struct addrinfo *resultado;

memset(&filtro,0,sizeof(struct addrinfo));

filtro.ai_socktype = SOCK_STREAM;
filtro.ai_family = AF_UNSPEC;
filtro.ai_flags =  AI_PASSIVE;

int rc =  getaddrinfo(argv[1], argv[2],&filtro, &resultado);


	if(rc != 0){
	printf("Error en getaddrinfo : %d\n", gai_strerror(rc));
	return -1;
	}

//Socket 
int sd_tcp = socket(resultado->ai_family, resultado->ai_socktype, 0);


//Conexion
int bd = bind(sd_tcp,resultado->ai_addr,resultado->ai_addrlen);

	if(bd!= 0){
	printf("Error en bind \n");
	return -1;
	}
//Listen

int lis = listen(sd_tcp,5);
	
	if(lis!= 0){
	printf("Error en listen \n");
	return -1;
	}
freeaddrinfo(resultado);
//Cliente
struct sockaddr_storage cliente_addr;
socklen_t cliente_addrlen = sizeof(struct sockaddr_storage);

char buffer[257];
char host[NI_MAXHOST];
char serv[NI_MAXSERV];


signal(SIGCHLD,controlador);
int ac;
int status;

	while(1){
	ac = accept(sd_tcp,(struct sockaddr*)&cliente_addr,&cliente_addrlen);
	pid_t pid = fork();
		if( pid == 0){
			while(1){
			getnameinfo((struct sockaddr *)&cliente_addr, cliente_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST);
        printf("pid: %i Conexion con  %s:%s\n", getpid(), host, serv);
			ssize_t bytes;
					
			bytes = recv(ac, buffer, 256*sizeof(char), 0);
				do{

					if(bytes == -1){
						printf("Error al recibir los datos\n");
						close(sd_tcp);
						return -1;

					}else if(bytes ==0){
						printf("El cliente ha cerrado la conexion\n");	
						exit(0);
					}
					else{
					buffer[bytes]='\0';
					ssize_t esc = send(ac, buffer, bytes+1, 0);
						if(esc == -1){
							printf("Error al escribir los datos\n");
							return -1;
						}

					}
				bytes = recv(ac, buffer, 256*sizeof(char), 0);
				}while((buffer[0] != 'q') && (bytes!= 2));	
			}
		}else{
			pid = wait(&status);
			close(ac);
			exit(0);
		}
	
	}



close(sd_tcp);
return 0;
}