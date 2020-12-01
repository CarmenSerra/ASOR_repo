#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main(){

  time_t tiempo = time(NULL);
  struct tm *info = localtime(&tiempo);

  int anyo = info->tm_year;

  printf("Año actual: %i\n", 1900 + anyo);
  return 1;
}