//Crear un servidor TCP de eco que escuche por conexiones entrantes en una dirección (IPv4 o IPv6) y puerto dados. Cuando reciba una conexión entrante, debe mostrar la dirección y número de puerto del cliente. A partir de ese momento, enviará al cliente todo lo que reciba desde el mismo (eco). Comprobar su funcionamiento empleando la herramienta Netcat como cliente. Comprobar qué sucede si varios clientes intentan conectar al mismo tiempo.

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
#include <unistd.h>



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


	while(1){
//Accept
	int ac =  accept(sd_tcp, (struct sockaddr*)&cliente_addr, &cliente_addrlen);
		if ( ac == -1){
			printf("Error en el accept\n");
			return -1;
		}


	 getnameinfo((struct sockaddr*)&cliente_addr, cliente_addrlen,host,NI_MAXHOST,serv,NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

	printf("Conexion con %s : %s\n", host,serv);
	
	ssize_t bytes;

	
		do{
			bytes = recv(sd_tcp, buffer, 256*sizeof(char), 0);
			

			if(bytes == -1){
				printf("Error al recibir los datos\n");
				close(sd_tcp);
				return -1;

			}else if(bytes ==0){
				printf("El cliente ha cerrado la conexion");
			}
			else{
			buffer[bytes]='\0';
			ssize_t esc = send(sd_tcp, buffer, bytes+1, 0);
				if(esc == -1){
					printf("Error al escribir los datos\n");
					return -1;
				}

			}
		
		}while(bytes >0);
	
	}
close(sd_tcp);

return 0;
}