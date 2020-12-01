#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){

struct utsname buffer; 

 uname(&buffer);

printf("sistema : %s\n", buffer.sysname);
printf("nombre del host : %s\n", buffer.nodename);
printf("release del SO  : %s\n", buffer.release);
printf("version : %s\n", buffer.version);
printf("maquina : %s\n", buffer.machine);
//printf("nombre del dominio : %s\n", buffer.domainname);



return 1;
}