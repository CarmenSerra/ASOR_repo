#include<pwd.h>
#include<sys/types.h>
#include <string.h>
#include <stdio.h>


int main (){

//uid real del user 
//uid efectivo  del user

uid_t u = getuid();


printf("Real: %d\n", getuid());
printf("Efectivo: %d\n", geteuid());

//nombre 
//directorio home
//descripcion del user
 
struct passwd *p;
p = getpwuid(u);

char *nombre = p->pw_name;
char *dir = p->pw_dir;
char *descripcion = p-> pw_gecos;


    printf("Nombre usuario: %s\n", nombre);
    printf("Dir Home: %s\n", dir);
    printf("Descripcion usuario: %s\n",descripcion);



return 1;
}

