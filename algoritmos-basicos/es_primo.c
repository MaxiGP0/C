

/*
 Ejercicio 11. Escribı un programa que lea por teclado un numero entero n mayor que 1, y
determine si es primo o no, usando un while que pruebe los posibles divisores de n
 */



#include <stdio.h>




int main() {

    int numero;
    printf("numero: ");
    scanf("%d", &numero);

    if (numero > 1) {

        int cant=0;
        int temp=1;

        while (temp < numero) {
            if ((numero % temp) == 0) cant++;
            temp++;
        }

        if (cant==1) printf("El numero %d es primo.\n", numero);
        else printf("El numero %d no es primo.\n", numero);


    } else {
        printf("Debe ingresar un numero mayor que uno(1).\n");
        return 1;
    }



    return 0;

}

