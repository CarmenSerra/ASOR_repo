#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main( int argc, char ** argv){

int error;

error = setuid(0);
char c = strerror(error);
        if ( error == -1){
                perror("setuid");
		printf("Num error %error");
		printf("Cadena de error %c");
                return -1;
        }

}
