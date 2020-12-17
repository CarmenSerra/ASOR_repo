//Ejercicio 7. Modificar el ejercicio 5 para que, antes de crear el fichero, se fije la máscara igual que en el ejercicio 6. Comprobar el resultado con el comando ls. Comprobar que la máscara del proceso padre (la shell) no cambia.

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	mode_t prev = umask(027);

	int fd;
	fd = open("ejercicio7.txt", O_CREAT | O_RDONLY, 0777);

	return 0;
}

