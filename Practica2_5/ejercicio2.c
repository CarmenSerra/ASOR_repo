//Escribir un servidor UDP de hora de forma que://
//La dirección y el puerto son el primer y segundo argumento del programa. Las direcciones pueden expresarse en cualquier formato (nombre de host, notación de punto…). Además, el servidor debe funcionar con direcciones IPv4 e IPv6 .
//El servidor recibirá un comando (codificado en un carácter), de forma que ‘t’ devuelva la hora, ‘d’ devuelve la fecha y ‘q’ termina el proceso servidor.
//En cada mensaje el servidor debe imprimir el nombre y puerto del cliente, usar getnameinfo(3).

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

	while (buf[0] != 'q') {
	int bytes =recvfrom(sd_udp, buf,1,0, (struct sockaddr *) &cliente_addr, &cliente_len);

	buf[bytes]='\0';
	getnameinfo((struct sockaddr *)&cliente_addr,cliente_len,host,NI_MAXHOST,serv,NI_MAXSERV,NI_NUMERICHOST|NI_NUMERICSERV);
		
	printf("%i bytes de %s:s%s \n", bytes, host,serv);


	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	size_t m;
	char buffer[50];

	//Si es una t devuelve la hora
	if (buf[0] == 't'){

	int b = strftime(buffer,m,"%I:%M:%S %p ",tm);
	buffer[b] ='\0';

	int escritura =  sendto(sd_udp, buffer, b,0,(struct sockaddr *) &cliente_addr,  cliente_len);
		if (escritura == -1) {
			printf("Error escribiendo en cliente");
			return -1;
		}
	}	
	
	//Si es q se termina el proceso servidor
	else if (buf[0] == 'q'){
	printf("Termina el proceso servidor\n");
	}
	//Si es una d devuelve la fecha, d de date 
	else if (buf[0] == 'd'){
	
	size_t b = strftime(buffer,m,"%Y-%m-%d ",tm);
	buffer[b] ='\0';
	
	int escritura =  sendto(sd_udp, buffer,b,0,(struct sockaddr *) &cliente_addr,  cliente_len);

		if (escritura == -1) {
			printf("Error escribiendo en cliente");
			return -1;
		}
	
	
	}
	else printf("Comando no soportado\n");

}
	
	
close(sd_udp);	


return 0;
}

