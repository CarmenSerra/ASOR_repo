// link(2) y symlink(2) crean enlaces rígidos y simbólicos, respectivamente. Escribir un programa que reciba una ruta a un fichero como argumento. Si la ruta es un fichero regular, creará un enlace simbólico y rígido con el mismo nombre terminado en .sym y .hard, respectivamente. Comprobar el resultado con la orden ls.

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {


	//Compruebo si se ha introducido la path 
	if (argc < 2){
		printf("Error: No se ha especificado la ruta del archivo. Introducir de nuevo");
	return -1;
	}

	struct stat buffer_s;
	int statint = stat(argv[1], &buffer_s);
	
	mode_t mode = buffer_s.st_mode;

	if(S_ISREG(mode)){ //Fichero ordinario
	printf("%s es un archivo ordinario.\n", argv[1]);
	//Enlace simbolico:
	const char newpath[] = "enlace.sym";
		if(symlink(argv[1], newpath)== -1){
		printf("ERROR AL CREAR EL SYM");
		}else printf("Se ha creado enlace sym.\n");

	//Enlace rigido	
	const char newpath2[] = "enlace.hard";
		if (link(argv[1], newpath2) == -1){
		printf("ERROR AL CREAR EL HARD");
		}else printf("Se ha creado enlace hard.\n");
	}


return 0;
}