// Escribir el cliente para conectarse con el servidor del ejercicio anterior. El cliente recibirá la dirección y el puerto del servidor como argumentos y, una vez establecida la conexión con el servidor, le enviará lo que el usuario escriba por teclado. Mostrará en la consola la respuesta recibida desde el servidor. Cuando el usuario escriba el carácter ‘Q’ como único carácter de una línea, el cliente cerrará la conexión con el servidor y terminará.

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

memset(&filtro, 0, sizeof(struct addrinfo));

filtro.ai_socktype = SOCK_STREAM;
filtro.ai_family = AF_UNSPEC;
filtro.ai_flags =  AI_PASSIVE;

	
       int  rc = getaddrinfo(argv[1], argv[2], &filtro, &resultado);
	//int  rc = getaddrinfo("fd00::a:0:0:0:100", "2222", &filtro, &resultado);
                 
	if(rc != 0){
	printf("Error en getaddrinfo : %d\n", gai_strerror(rc));
	return -1;
	}

	//socket
	int sd_tcp = socket(resultado->ai_family, resultado->ai_socktype,0);
	//bind
	int bd = bind(sd_tcp,&resultado->ai_addr, resultado->ai_addrlen);

	if(bd!= 0){
	printf("Error en bind \n");
	return -1;
	}

	int l = listen(sd_tcp,10);
	if(l!= 0){
	printf("Error en listen \n");
	return -1;
	}

	freeaddrinfo(resultado);
	//servidor?

 struct sockaddr_storage cliente_addr;
socklen_t cliente_addrlen = sizeof(struct sockaddr);


char buffer[257] ="";
char host[NI_MAXHOST];
char serv[NI_MAXSERV];
	
ssize_t by,esc;

	while(1){
int ac =  accept(sd_tcp,(struct sockaddr*)&cliente_addr , cliente_addrlen);
 		if ( ac == -1){
			printf("Error en el accept\n");
			return -1;
		}
	 //getnameinfo ((struct sockaddr *)&cliente_addr, cliente_addr,host,NI_MAXHOST,serv,NI_MAXSERV,,NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
	
		while(buffer[0] != 'Q' && buffer[1] !='\n'){
			by = read(0, buffer, 256*sizeof(char));
				if (by == -1) {
					perror("Error leyendo");
					close(sd_tcp);
					return -1;
				}
			buffer[by] = '\0';
			esc = send(sd_tcp,buffer,(by+1)*sizeof(char),0);	
				if (esc == -1) {
					perror("Error enviando al server echo");
					close(sd_tcp);
				return -1;
				}
			by = recv(sd_tcp,buffer, 256*sizeof(char),0);
				if (by == -1) {
					perror("Error leyendo de server");
					close(sd_tcp);
					return -1;
				}
			buffer[by] ='\0';
			printf("%s", buffer);
		}

		
	}
	

	

close(sd_tcp);
return 0;
}