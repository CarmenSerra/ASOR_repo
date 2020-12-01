#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

const int MAX_ERR=255;

int main( int argc, char ** argv){

for ( int i =0; i < MAX_ERR; i++){
	printf("Error %d : %s\n", i, strerror(i));
}

return 1;
}