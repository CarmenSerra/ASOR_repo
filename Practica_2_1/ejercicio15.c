#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>


int main(){
    time_t t = time(NULL);
    struct tm *datos = localtime(&t);

    int anyo = datos->tm_year;

    char buf1[50];
    strftime(buf1, 50, "%A, %d de %B de ", datos);

    char buf2[50];
    strftime(buf2, 50, ", %r", datos);

    printf("Hoy es %s %i %s\n", buf1, anyo + 1900, buf2);

    return 1;
}

//lunes, 29 de octubre de 2018, 10:34