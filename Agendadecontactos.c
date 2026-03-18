#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"

// typedef struct {
//     char NOMBRE[40];
//     char TELEFONO[20];
//     int DNI ;
//     char ESTADO [15];  
// } contacto;

int main (){
    FILE * lista_contactos;
    contacto X;
    int n, i, menu, dni;
    char archivo[15], modo[4];

    printf ("Ingrese el nombre del archivo que quiere abrir: ");
    scanf ("%s", archivo);

    strcpy(modo, "r+");

    lista_contactos = abrir_archivo2(archivo, modo);

    printf ("Cuál es la acción que desea realizar con su agenda de contactos?\n");
    printf ("Seleccione un número:\n 1.Agendar nuevo contacto\n 2.Modificar contacto existente\n 3.Consultar datos sobre un contacto\n 4.Eliminar contacto existente\n 5.Mostrar la agenda completa de contactos\n");
    scanf ("%d", &menu);
    getchar();

    switch (menu){
        case 1:
         fseek (lista_contactos,0,2); //se envía el puntero del archivo, el desplazamiento del puntero de posición respecto al origen, y el origen que en este caso es 2 (final) 

         X= cargar_contacto (lista_contactos);
         ordenar_y_guardar_contactos (lista_contactos);
         eliminar_duplicados(lista_contactos);
        break;

        case 2:
         printf ("Ingrese el DNI del contacto que quiere modificar. Sin puntos ni caracteres especiales: ");
         scanf ("%d", &dni);
         modificar_contacto(lista_contactos, dni);
         ordenar_y_guardar_contactos (lista_contactos);
        break;

        case 3:
         consultar_contacto(lista_contactos);
        break;

        case 4:
         printf ("Ingrese el DNI del contacto que quiere eliminar. Sin puntos ni caracteres especiales: ");
         scanf ("%d", &dni);
         eliminar_contacto(lista_contactos,dni);
        break;

        case 5:
        mostrar_contactos(lista_contactos);
        break;

        default:
        printf("Opción no válida.\n");
        return 1;
    }

    fclose(lista_contactos);


    return 0;
}

//Cargar una estructura que contiene un contacto
// contacto cargar_contacto (FILE *archivo){
// contacto X;

// printf ("Ingrese el nombre completo siguiendo el formato ''nombre segundonombre apellido segundoapellido'':\n ");
// fgets(X.NOMBRE, sizeof(X.NOMBRE), stdin);
// size_t len = strlen(X.NOMBRE);
// if (len > 0 && X.NOMBRE[len-1] == '\n') {
//     X.NOMBRE[len-1] = '\0';
// }

// printf ("Ingrese el número de teléfono siguiendo el formato ''##-###-###-####'' siendo los dos primeros caracteres el código de área:\n ");
// fgets(X.TELEFONO, sizeof(X.TELEFONO), stdin);
// len = strlen(X.TELEFONO);
// if (len > 0 && X.TELEFONO[len-1] == '\n') {
//     X.TELEFONO[len-1] = '\0';
// }

// printf ("Ingrese el DNI (sólo números sin utilizar ''.''):\n ");
// fgets(X.DNI, sizeof(X.DNI), stdin);

// strcpy(X.ESTADO, "ACTIVO");

// fwrite(&X, sizeof (X), 1, archivo);

// return X;
//  }



// void ordenar_y_guardar_contactos(FILE *archivo) {
//     contacto *contactos = NULL;  
//     int count = 0;
//     int capacidad = 10;  
//     contactos = malloc(capacidad * sizeof(contacto)); //malloc me sirve para trabajar de manera dinamica, asi no tengo que limitar la cantidad de contactos, en un principio inicio la memoria para 10 contactos. 
    
//     if (contactos == NULL) {
//         printf("Error al asignar memoria.\n");
//         return;
//     }

//     rewind(archivo);  
//     while (fread(&contactos[count], sizeof(contacto), 1, archivo)) {
//         count++;
//         if (count >= capacidad) {
//             capacidad *= 2;  
//             contactos = realloc(contactos, capacidad * sizeof(contacto));// Si alcanzo el límite de la capacidad inicial, duplico el tamaño del arreglo utilizando
//             if (contactos == NULL) {
//                 printf("Error al redimensionar la memoria.\n");
//                 return;
//             }
//         }
//     }

//     for (int i = 0; i < count - 1; i++) {
//         for (int j = 0; j < count - i - 1; j++) {
//             if (strcmp(contactos[j].NOMBRE, contactos[j + 1].NOMBRE) > 0) {
//                 contacto temp = contactos[j];
//                 contactos[j] = contactos[j + 1];
//                 contactos[j + 1] = temp;
//             }
//         }
//     }

//     fclose(archivo); 
//     archivo = fopen("agenda_contactos.txt", "wb");  // Reabrir en modo escritura
//     fwrite(contactos, sizeof(contacto), count, archivo);

//     printf("Contactos ordenados y guardados exitosamente.\n");

    
//     free(contactos); // Así libero la memoria dinámica
// }


// //Elimino los contactos duplicados ya ordenados
// void eliminar_duplicados(FILE *archivo) {
//     contacto contacto_anterior, contacto_actual;
//     int posicion_anterior, posicion_actual;
    
//     rewind(archivo); 

//     // Leo el primer contacto
//     if (fread(&contacto_anterior, sizeof(contacto), 1, archivo) != 1) {
//         printf("El archivo está vacío o no se pudo leer.\n");
//         return;
//     }

//     posicion_anterior = ftell(archivo) - sizeof(contacto); // Guardo la posición del primer contacto

   
//     while (fread(&contacto_actual, sizeof(contacto), 1, archivo) == 1) {
//         posicion_actual = ftell(archivo) - sizeof(contacto);  // Guardo la posición actual del segundo contacto

        
//         if (strcmp(contacto_anterior.NOMBRE, contacto_actual.NOMBRE) == 0 &&
//             strcmp(contacto_anterior.TELEFONO, contacto_actual.TELEFONO) == 0 &&
//             contacto_anterior.DNI == contacto_actual.DNI) {

//             // Marco el contacto actual como "INACTIVO"
//             strcpy(contacto_actual.ESTADO, "INACTIVO");

//             fseek(archivo, posicion_actual, SEEK_SET);

//             fwrite(&contacto_actual, sizeof(contacto), 1, archivo);

//             // Mover el puntero de vuelta al siguiente contacto (luego de sobrescribir)
//             fseek(archivo, posicion_actual + sizeof(contacto), SEEK_SET);

//             printf("Se ha marcado como INACTIVO el duplicado con nombre %s.\n", contacto_actual.NOMBRE);
//         }
//         // El contacto actual se convierte en el anterior
//         contacto_anterior = contacto_actual;
//         posicion_anterior = posicion_actual;
//     }
// }

//Modificar un dato de un contacto
// void modificar_contacto(FILE *archivo, int dni) {
//     contacto X;
//     long posicion;
//     int menu, si;

//     rewind(archivo);  

//     while (fread(&X, sizeof(contacto), 1, archivo)) {
//         if (X.DNI == dni && strcmp(X.ESTADO, "ACTIVO") == 0) {
            
//             printf("Es este el contacto que desea modificar?:\n");
//             printf("Nombre: %s\n", X.NOMBRE);
//             printf("Teléfono: %s\n", X.TELEFONO);
//             printf("DNI: %d\n", X.DNI);

//             printf ("Elija un número:\n 1.Si\n 2.No\n");
//             scanf ("%d", &si);

//             if (si == 1){
//             posicion = ftell(archivo) - sizeof(contacto);

            
//             printf("Qué campo desea modificar? Seleccione un número:\n 1.Nombre\n 2.Teléfono\n 3.DNI\n");
//             scanf("%d", &menu);
//             getchar();  

//             switch (menu) {
//                 case 1:
//                     printf("Ingrese el nuevo nombre completo: ");
//                     fgets(X.NOMBRE, sizeof(X.NOMBRE), stdin);
//                     size_t len = strlen(X.NOMBRE);
//                     if (len > 0 && X.NOMBRE[len-1] == '\n') {
//                         X.NOMBRE[len-1] = '\0';
//                     }
//                     break;

//                 case 2:
//                     printf("Ingrese el nuevo número de teléfono: ");
//                     fgets(X.TELEFONO, sizeof(X.TELEFONO), stdin);
//                     len = strlen(X.TELEFONO);
//                     if (len > 0 && X.TELEFONO[len-1] == '\n') {
//                         X.TELEFONO[len-1] = '\0';
//                     }
//                     break;

//                 case 3:
//                     printf("Ingrese el nuevo DNI: ");
//                     scanf("%d", &X.DNI);
//                     break;

//                 default:
//                     printf("Opción no válida.\n");
//                     return;
//             }

//             fseek(archivo, posicion, SEEK_SET);  
//             fwrite(&X, sizeof(contacto), 1, archivo);
//             printf("Contacto modificado exitosamente.\n");
//             return;
//         }
//         printf("Ingrese un DNI válido.\n");
//     }
//     } 
// }


// //Buscar y mostrar un contacto según el criterio seleccionado 
// void consultar_contacto(FILE *archivo) {
//     contacto X;
//     int criterio;
//     char nombre[40];
//     char telefono[20];
//     int dni;
//     int encontrado = 0;

//     printf("Seleccione el criterio de búsqueda:\n 1.Nombre\n 2.DNI\n 3.Teléfono\n");
//     scanf("%d", &criterio);
//     getchar();  

//     rewind(archivo);  // Volver al inicio del archivo

//     switch (criterio) {
//         case 1:
//             printf("Ingrese el nombre completo para buscar: ");
//             fgets(nombre, sizeof(nombre), stdin);
//             size_t len = strlen(nombre);
//             if (len > 0 && nombre[len-1] == '\n') {
//                 nombre[len-1] = '\0';
//             }

//             while (fread(&X, sizeof(contacto), 1, archivo)) {
//                 if (strcmp(X.NOMBRE, nombre) == 0 && strcmp(X.ESTADO, "ACTIVO") == 0) {
//                     printf("Contacto encontrado:\n");
//                     printf("Nombre: %s\n", X.NOMBRE);
//                     printf("Teléfono: %s\n", X.TELEFONO);
//                     printf("DNI: %d\n", X.DNI);
//                     encontrado = 1;
//                     break;
//                 }
//             }
//             break;

//         case 2:
//             printf("Ingrese el DNI para buscar: ");
//             scanf("%d", &dni);

//             while (fread(&X, sizeof(contacto), 1, archivo)) {
//                 if (X.DNI == dni && strcmp(X.ESTADO, "ACTIVO") == 0) {
//                     printf("Contacto encontrado:\n");
//                     printf("Nombre: %s\n", X.NOMBRE);
//                     printf("Teléfono: %s\n", X.TELEFONO);
//                     printf("DNI: %d\n", X.DNI);
//                     encontrado = 1;
//                     break;
//                 }
//             }
//             break;

//         case 3:
//             printf("Ingrese el teléfono para buscar: ");
//             fgets(telefono, sizeof(telefono), stdin);
//             len = strlen(telefono);
//             if (len > 0 && telefono[len-1] == '\n') {
//                 telefono[len-1] = '\0';
//             }

//             while (fread(&X, sizeof(contacto), 1, archivo)) {
//                 if (strcmp(X.TELEFONO, telefono) == 0 && strcmp(X.ESTADO, "ACTIVO") == 0) {
//                     printf("Contacto encontrado:\n");
//                     printf("Nombre: %s\n", X.NOMBRE);
//                     printf("Teléfono: %s\n", X.TELEFONO);
//                     printf("DNI: %d\n", X.DNI);
//                     encontrado = 1;
//                     break;
//                 }
//             }
//             break;

//         default:
//             printf("Criterio no válido.\n");
//             return;
//     }

//     if (!encontrado) {
//         printf("No se encontró un contacto con los datos proporcionados.\n");
//     }
// }


// //Eliminar un contacto según su DNI
// void eliminar_contacto(FILE *archivo, int dni) {
//     contacto X;
//     int encontrado = 0;
//     int posicion, si;

//     rewind(archivo); 

//     while (fread(&X, sizeof(contacto), 1, archivo)) {
//         if (X.DNI == dni && strcmp(X.ESTADO, "ACTIVO") == 0) {
            
//             printf("Confirma la eliminación del siguiente contacto?\n");
//             printf("Nombre: %s\n", X.NOMBRE);
//             printf("Teléfono: %s\n", X.TELEFONO);
//             printf("DNI: %d\n", X.DNI);

//                 printf ("Elija un número:\n 1.Si\n 2.No\n");
//                 scanf ("%d", &si);
//                 if (si == 1){    
//                     strcpy(X.ESTADO, "INACTIVO");

//                     posicion = ftell(archivo) - sizeof(contacto);
//                     fseek(archivo, posicion, SEEK_SET);
//                     fwrite(&X, sizeof(contacto), 1, archivo);

//                     printf("El contacto ha sido eliminado.\n");
//                     encontrado = 1;
//                     break;
//                 }
//                 else {
//                     printf("El contacto no ha sido eliminado.\n");
//                 }
//         }
//     }

//     if (!encontrado) {
//         printf("No se encontró un contacto con el DNI %d o ya fue eliminado.\n", dni);
//     }
// }


// //Mostrar todos los contactos con estado "ACTIVO"
// void mostrar_contactos(FILE *archivo) {
//     contacto X;
//     int encontrado = 0;

//     rewind(archivo); 

//     printf("A continuación se muestran los contactos de la agenda:\n");

//     // Leer hasta que fread no pueda leer más (cuando fread devuelve 0)
//     while (fread(&X, sizeof(contacto), 1, archivo) == 1) {
//         if (strcmp(X.ESTADO, "ACTIVO") == 0) {
//             printf("----------------------------\n");
//             printf("Nombre: %s\n", X.NOMBRE);
//             printf("Teléfono: %s\n", X.TELEFONO);
//             printf("DNI: %d\n", X.DNI);
//             encontrado = 1;
//         }
//     }

//     if (!encontrado) {
//         printf("No hay contactos en la agenda.\n");
//     }
// }

