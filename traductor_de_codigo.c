#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"


int main (){
    FILE * entrada;
    FILE * salida;
    char leer[100][30], s;
    int j=0, i=0, x;

    entrada = abrir_archivo ();
    salida = fopen ("codigo_ingles.txt","r+");
        if (salida == NULL) {
         salida = fopen ("codigo_ingles.txt","w+");    
        }
    
      
     while ((s = fgetc(entrada)) != EOF) {

            if (isspace(s)) {
            leer[i][j] = '\0';  
            traducir_lectura(leer[i], salida);  
            fprintf(salida, "%c", s);  
            j = 0;  
            i++;  

        } else if (ispunct(s)) {
            leer[i][j] = '\0';  
            traducir_lectura(leer[i], salida);  
            fprintf(salida, "%c", s);  
            j = 0;  
            i++;  

        } else {
            leer[i][j++] = s;  
        }
    }

    x=i++;

    if (j > 0) {
        leer[i][j] = '\0';
        traducir_lectura(leer[i], salida);
    }

    fclose(entrada);
    fclose(salida);

    for (i=0; i < x; i++){
        traducir_lectura (leer[i],salida);
    }
    
    printf ("El archivo que contiene la traducción se llama: codigo_ingles.txt \n");
    
    
    return 0;
}

