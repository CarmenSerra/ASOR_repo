#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>


int main (){


 struct timeval tv;

  int n1 = gettimeofday(&tv,NULL);
  int inicio = tv.tv_usec;


for (int i = 0; i < 1000000; i++);

int n2 = gettimeofday(&tv,NULL);
int final = tv.tv_usec;


printf("Microsegundos (ms) :%i\n",  final - inicio);

return 1;
}