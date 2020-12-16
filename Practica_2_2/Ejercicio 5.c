// Escribir un programa que, usando open(2), cree un fichero con los permisos rw-r--r-x. Comprobar el resultado y las características del fichero con la orden ls.

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main( int argc, char **argv){

int fd;

const char pathname[] = "/home/cursoredes/eje5.txt";
		
fd = open(pathname, O_CREAT, 0645);


return 0;
}
