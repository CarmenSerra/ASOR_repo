//Escribir el cliente para el servidor de hora. El cliente recibirá como argumentos la dirección del servidor, el puerto del servidor y el comando. Por ejemplo, para solicitar la hora, ./time_client 192.128.0.1 3000 t.

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

int main(int argc, char **argv){

	if (argc < 4) {
		printf("Introduce el comando\n");
		return -1;
	}

struct addrinfo filtro;
struct addrinfo *resultado;

//Inicializo a 0 a estructura
memset(&filtro, 0, sizeof(struct addrinfo));

filtro.ai_family =AF_UNSPEC; //Necesito que sean ipv4 o ipv6
filtro.ai_socktype = SOCK_DGRAM; // 2
filtro.ai_flags = AI_PASSIVE;

int rc = getaddrinfo(argv[1],argv[2],&filtro, &resultado);

	if(rc != 0){
		printf("Error: getaddrinfo %s\n", gai_strerror(rc));
	return -1;
	}

int sd_udp = socket(resultado->ai_family, resultado->ai_socktype, 0);


//BIND
int bd =  bind(sd_udp,(struct sockaddr *)resultado->ai_addr, resultado->ai_addrlen);

	if(bd != 0){
		printf("Error: bind\n");
	return -1;
	}

freeaddrinfo(resultado);

char buf[2] ="";
char host[NI_MAXHOST];
char serv[NI_MAXSERV];


	struct sockaddr_storage cliente_addr;
	socklen_t cliente_len = sizeof(struct sockaddr_storage);


	//Ahora primero escribo en el cliente y le paso el comando
	//que viene en el argumento 3
	int escritura =  sendto(sd_udp, argv[3],2,0,resultado->ai_addr,resultado->ai_addr);
		if (escritura == -1) {
			printf("Error escribiendo en cliente");
			return -1;
		}
	printf("%s\n", argv[3]);
	
	//En cuanto al servidor solo tengo que distinguir entre dos casos
	//Y mostrar lo que he recibido

	if (*argv[3] == 'd' || *argv[3] == 't'){
	    char buffer[80];
	    int bytes = recvfrom(sd_udp, buffer, 79, 0, (struct sockaddr *) &cliente_addr, cliente_len);
    buffer[bytes] = '\0';

    printf("%s\n", buffer);
  }
		
	


	
	
close(sd_udp);	


return 0;
}

