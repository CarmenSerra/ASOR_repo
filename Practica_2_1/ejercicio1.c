#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char ** argv){


int error;

error = setuid(0);

        if ( error == -1){
                perror("setuid");
                return -1;
        }

}
