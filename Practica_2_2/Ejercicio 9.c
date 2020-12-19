//Escribir un programa que emule el comportamiento del comando stat y muestre:
//El número major y minor asociado al dispositivo.  st_dev , poniendo ( minor()y major() delante) 
//El número de i-nodo del fichero. ino_t st_ino  
//El tipo de fichero  st_mode, (directorio (S_ISDIR(mode)), enlace simbólico(S_ISLNK(mode)) o fichero ordinario (S_ISREG(mode))).
//La hora en la que se accedió el fichero por última vez. ¿Qué diferencia hay entre st_mtime y st_ctime?  time_t st_atime; 
//RESPUESTA: st_mtime es la ultima modificación mientras que st_ctime es la última vez que cambio de estado, que puede no haber sido mediante una modificación dentro del archivo.

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <time.h>

       int stat(const char *pathname, struct stat *buf);
       int fstat(int fd, struct stat *buf);
       int lstat(const char *pathname, struct stat *buf);

int main( int argc, char **argv){

//Compruebo si se ha introducido la path 
	if (argc < 2){
		printf("Error: No se ha especificado la ruta del archivo. Introducir de nuevo");
	return -1;
	}

	struct stat buffer_s;

	//Major

	printf("Major: %li\n", (long) major(buffer_s.st_dev));

	//Minor 

	printf("Minor: %li\n", (long) minor(buffer_s.st_dev));


	//i-nodo
	printf("i-nodo: %li", buffer_s.st_ino);


	//Mostrar el tipo de fichero que es 
	mode_t mode = buffer_s.st_mode; 

	if(S_ISDIR(mode)){ //Si es un directorio
	printf("%s es un directorio.\n", argv[1]);
	}
	else if(S_ISLNK(mode)){ //Si es un enlace simbólico
	printf("%s es un enlace simbólico.\n", argv[1]);
	}
	else if(S_ISREG(mode)){ //Fichero ordinario
	printf("%s es un fichero ordinario.\n", argv[1]);
	}

	//Ultimo acceso al fichero
	//time_t t = buffer_s.st_atime;

	//struct tim *tm1= localtime(&t);
	//printf("Ultimo acceso : %d:%d\n", tm1->tim_hour, tm1->tim_min); 


	return 0;
}