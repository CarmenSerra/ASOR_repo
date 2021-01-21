// Modificar el servidor para que, además de poder recibir comandos por red, los pueda recibir directamente por el terminal, leyendo dos caracteres (el comando y ‘\n’) de la entrada estándar. Multiplexar el uso de ambos canales usando select(2)

//Carmen Serrano Avilés

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <sys/select.h>

int main(int argc, char **argv){

struct addrinfo filtro;
struct addrinfo *resultado;

//Inicializo a 0 la estructura de filtro 
memset(&filtro, 0, sizeof(struct addrinfo));

//Inicializo los flags que me interesan a los valores correspondientes
filtro.ai_family = AF_UNSPEC; 
filtro.ai_socktype = SOCK_DGRAM;
filtro.ai_flags = AI_PASSIVE;


//Obtengo el resultado
int rc = getaddrinfo(argv[1],argv[2],&filtro,&resultado);

	if( rc != 0){
	printf("Error en getaddrinfo : %s\n", gai_strerror(rc));
	}
//Creo el socket a aprtir de la informacion de resultado, 
int sd_udp = socket(resultado->ai_family,resultado->ai_socktype,0);

//Establezco la conexión con el bind, IMP el cast a sockaddr.
int bd = bind(sd_udp, (struct sockaddr *)resultado->ai_addr, resultado->ai_addrlen);

	if( bd !=0){
	printf("Error en bind\n");
	}

freeaddrinfo(resultado);

//Creo al cliente
struct sockaddr_storage cliente_addr;
socklen_t cliente_addrlen = sizeof(struct sockaddr_storage);
char buffer[2] ="";
char host[NI_MAXHOST];
char serv[NI_MAXSERV];

//COnjunto controlador de la entrada
fd_set conjunto;

time_t tiempo =time(NULL);
struct tm *tm = localtime(&tiempo);
size_t m;
char buf[50];

	while(buffer[0] != 'q'){
	
		FD_ZERO(&conjunto); 
		FD_SET(0,&conjunto); // Entrada estandar
		FD_SET(sd_udp, &conjunto);//Entrada por socket
		int fd = select(sd_udp +1, &conjunto, NULL,NULL,NULL);
	

		//Compruebo cual es el que he leído 
		if (FD_ISSET(sd_udp,&conjunto)){
		printf("hola");
			ssize_t bytes = recvfrom(sd_udp, buffer,1, 0,(struct sockaddr *) &cliente_addr, &cliente_addrlen);
	
			 getnameinfo((struct sockaddr *)&cliente_addr, cliente_addrlen,host,NI_MAXHOST,serv,NI_MAXSERV,NI_NUMERICHOST|NI_NUMERICSERV);
	
			printf("%i bytes de %s,:%s\n", bytes,host,serv);

			buffer[bytes] = '\0';

			if(buffer[0] == 't'){
			int b = strftime(buf,m,"%I:%M:%S %p ",tm);
			int escritura = sendto(sd_udp, buf,b, 0,(struct sockaddr *)&cliente_addr,  cliente_addrlen);
				if( escritura != 0){
				printf("Error escribiendo en cliente\n");	
				return -1;
				}

			}
			else if (buffer[0] == 'd'){
			int b = strftime(buf,m,"%F",tm);
			int escritura = sendto(sd_udp, buf,b, 0,(struct sockaddr *)&cliente_addr,  cliente_addrlen);
				if( escritura != 0){
				printf("Error escribiendo en cliente\n");	
				return -1;
				}
			}
			else if (buffer[0] == 'q'){
				printf("Termina el proceso servidor\n");
				exit(0);
				
			}
		 	else{
       			printf("Comando no soportado: %d...\n", buf[0]);
     			}			
	
		}else{
		read(0,buffer,2);
		printf("Por consola: %i bytes\n", 2);
		buffer[1] = '\0';	
			if(buffer[0] == 't'){
			int b = strftime(buf,m,"%I:%M:%S %p ",tm);
			printf("Hora: %s\n", buf);
			}
			else if (buffer[0] == 'd'){
			int b = strftime(buf,m,"%F",tm);
			printf("Fecha: %s\n", buf);
			
			}
			else if (buffer[0] == 'q'){
				printf("Termina el proceso servidor\n");
				exit(0);
			}
			else{
       			printf("Comando no soportado: %d...\n", buf[0]);
     			}			
	

		
		}
	

	
	
	
	}

close(sd_udp);
return 0;
}

