//Escribir un programa que obtenga todas las posibles direcciones con las que se podría crear un socket asociado a un host dado como primer argumento del programa. Para cada dirección, mostrar la IP numérica, la familia de protocolos y tipo de socket. Comprobar el resultado para

//Carmen Serrano Avilés

  
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc,char **argv){

	if (argc < 2) {
	    printf("Introduce una dirección.\n");
	    return -1;
	}

struct addrinfo filtro;
struct addrinfo *resultado, *i;

//Pongo a 0 la estructura
	memset(&filtro, 0, sizeof(struct addrinfo)); 
 
	filtro.ai_flags = AI_PASSIVE; //Nos devuelve 'localhost si no especif. nada
	filtro.ai_family = AF_UNSPEC; //Both ipv4 y 6

	int rc = getaddrinfo(argv[1],NULL,&filtro,&resultado);

	if(rc != 0){
		printf("Error: getaddrinfo %s\n", gai_strerror(rc));
	return -1;
	}

	for(i = resultado; i!= NULL; i = i->ai_next){
	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];
	

	getnameinfo(i->ai_addr,i->ai_addrlen,host,NI_MAXHOST,serv,NI_MAXSERV,NI_NUMERICHOST);
	
	printf("IP numerica: %s\n",host);
	printf("Familia de protocolos: %i\n",i->ai_family);
	printf("Tipo socket: %i\n",i->ai_socktype);
	}


freeaddrinfo(resultado);

return 0;
}