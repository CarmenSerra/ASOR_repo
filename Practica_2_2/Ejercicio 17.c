//El programa tiene un único argumento que es la ruta a un directorio. El programa debe comprobar la corrección del argumento.
//El programa recorrerá las entradas del directorio de forma que:
//Si es un fichero normal, escribirá el nombre. DT_REG
//Si es un directorio, escribirá el nombre seguido del carácter ‘/’. DT_DIR
//Si es un enlace simbólico, escribirá su nombre seguido de ‘->’ y el nombre del  fichero enlazado. Usar readlink(2) y dimensionar adecuadamente el buffer. DT_LNK
//Si el fichero es ejecutable, escribirá el nombre seguido del carácter ‘*’.


#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



/*
struct dirent {
               ino_t          d_ino;       /* inode number */
             //off_t          d_off;       /* not an offset; see NOTES */
             //unsigned short d_reclen;    /* length of this record */
             // unsigned char  d_type;      /* type of file; not supported by all file system types */
            //   char           d_name[256]; /* filename */
          // };


int main(int argc, char **argv) {

	if (argc < 2){
	printf("Error: No se ha especificado la ruta del directorio. Introducir de nuevo");
	return -1;
	}

	unsigned short tam_fich = 0;

	//DIR *opendir(const char *name);
	DIR *directorio = opendir(argv[1]);
	
//	struct dirent *readdir(DIR *dir);
	struct dirent* direntp;
	direntp = readdir(directorio);

	while(direntp != NULL){
	if (direntp->d_type == DT_REG){
		tam_fich += direntp->d_reclen;
		printf("El nombre del archivo es : %c\n", direntp->d_name);	
	}
	else if(direntp->d_type == DT_DIR){
		printf("El nombre del directorio es :%c/ \n",direntp->d_name);
	}
	else if(direntp->d_type == DT_LNK){
		printf("El nombre del enlace simbólico es :%c-> \n", direntp->d_name);
	}
	

	direntp = readdir(directorio);	
	}

	printf("El tamanyo total de los ficheros en el directorio es de: %d\n", tam_fich);	

return 0;
}