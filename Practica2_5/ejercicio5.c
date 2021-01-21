//Convertir el servidor UDP en multi-proceso siguiendo el patrón pre-fork. Una vez asociado el socket a la dirección local con bind(2), crear varios procesos que llamen a recvfrom(2) de forma que cada uno atenderá un mensaje de forma concurrente. Imprimir el PID del proceso servidor para comprobarlo.
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


int main ( int argc, int **argv){

struct addrinfo	filtro;
struct addrinfo *resultado;


memset(&filtro,0,sizeof(struct addrinfo));

filtro.ai_family =AF_UNSPEC; //Necesito que sean ipv4 o ipv6
filtro.ai_socktype = SOCK_DGRAM; // 2
filtro.ai_flags = AI_PASSIVE;

int rc = getaddrinfo(argv[1],argv[2],&filtro, &resultado);

		if(rc!=0){
		printf("Error en getaddrinfo %s\n", gai_strerror(rc));
		return -1;
		} 

int sd_udp = socket(resultado->ai_family, resultado->ai_socktype,0);

int bd = bind(sd_udp, (struct sockaddr *)resultado->ai_addr, resultado->ai_addrlen);

		if(bd!=0){
		printf("Error en bind\n");
		return -1;
		} 

freeaddrinfo(resultado);

char buffer[2] ="";
char host[NI_MAXHOST];
char serv[NI_MAXSERV];

struct sockaddr_storage cliente_addr;
socklen_t cliente_addrlen = sizeof(struct sockaddr_storage);

		int i;
		int status;
		for (i = 0; i < 3; i++){

		pid_t pid = fork();
		
			if(pid ==0){
				while(1){
				ssize_t bytes = recvfrom(sd_udp,buffer,2,0,(struct sockaddr*)&cliente_addr, &cliente_addrlen);
				buffer[1] ='\0';
				getnameinfo((struct sockaddr *)&cliente_addr,cliente_addrlen,host,NI_MAXHOST,serv,NI_MAXSERV,NI_NUMERICHOST|NI_NUMERICSERV);
				printf("%i bytes,de %s:%s con pid: %d\n", bytes,host,serv,pid);


				time_t tiempo =time(NULL);
				struct tm *tm = localtime(&tiempo);
				size_t m;
				char buf[50];
	
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

				}
			}else{
			pid = wait(&status);
			}
		}
close(sd_udp);
	
return 0;
}