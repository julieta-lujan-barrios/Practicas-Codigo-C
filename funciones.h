#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


//ESTRUCTURAS
typedef struct {
    char NOMBRE[40];
    char TELEFONO[20];
    int DNI ;
    char ESTADO [15];
    
} contacto;

//DECLARACIÓN DE FUNCIONES
void invertir (int N, char X []); 
void mayusculas (int N, char X[]);
void minusculas (int N, char X[]);
FILE * abrir_archivo ();
FILE * abrir_archivo2 (char * nombre, char * modo);
void traducir_lectura (char palabra[], FILE * archivo);
contacto cargar_contacto (FILE *archivo);
void ordenar_y_guardar_contactos(FILE *archivo);
void eliminar_duplicados(FILE *archivo);
void modificar_contacto(FILE *archivo, int dni);
void consultar_contacto(FILE *archivo);
void eliminar_contacto(FILE *archivo, int dni);
void mostrar_contactos(FILE *archivo);


//***** FUNCIONES *****//


//Invertir un vector
void invertir (int N, char X []) {
    char y;
    int i;
    
    for (i = 0; i < N; i ++) {
    y = X [i];
    N --;
    X [i] = X [N];
    X [N] = y;
  }
}


//Pasar toda una palabra a mayúsculas
void mayusculas (int N, char X[]) {
    char y;
    int i;
    
    for (i = 0; i < N; i ++) {
    y = X [i];
    y = toupper(y);
    X[i] = y;
}
}


//Pasar toda una palabra a minúsculas
void minusculas (int N, char X[]) {
    char y;
    int i;
    
    for (i = 0; i < N; i ++) {
    y = X [i];
    y = tolower(y);
    X[i] = y;
}
}


//Abrir un archivo con parámetros y devuelve un archivo
FILE * abrir_archivo () {
    FILE * archivo;
    char nombre[20], modo[3];
    int x;
    printf ("Ingrese el nombre del archivo que quiere abrir: ");
    scanf ("%s", nombre);
    printf ("\nDe qué manera desea abrir su archivo? Seleccione un número: \n ");
    printf ("1. Solo lectura\n");
    printf ("2. Lectura y escritura\n");
    scanf ("%d", &x);

    if ( x == 1 ){
        modo[0] = 'r';
        modo [1] = '\0';
    }
    else {
        modo[0] = 'w';
        modo [1] = '+';
        modo [2] = '\0';
    }

   archivo = fopen (nombre,modo);

   return archivo;
}


//Abrir un archivo sin parámetros y devuelve un archivo
FILE * abrir_archivo2 (char * nombre, char * modo){
FILE * X;

X = fopen (nombre,modo);
        if (X == NULL) {
         X = fopen (nombre,"w+");    
        }   
        
return X;
}


//Traducir a español palabras de un código
void traducir_lectura (char palabra[], FILE * archivo) {

    if (strcmp(palabra, "si") == 0) {
        fprintf(archivo, "if");
    }   else if (strcmp(palabra, "sino") == 0) {
         fprintf(archivo, "else");
        }       else if (strcmp(palabra, "mientras") == 0) {
                 fprintf(archivo, "while");
                }   else if (strcmp(palabra, "para") == 0) {
                     fprintf(archivo, "for");
                    }   else if (strcmp(palabra, "imprimir") == 0) {
                         fprintf(archivo, "printf");
                        }   else if (strcmp(palabra, "escanear") == 0) {
                             fprintf(archivo, "scanf");
                             }  else if (strcmp(palabra, "entero") == 0) {
                                 fprintf(archivo, "int");
                                }   else if (strcmp(palabra, "principal") == 0) {
                                     fprintf(archivo, "main");
                                    }   else if (strcmp(palabra, "caracter") == 0) {
                                         fprintf(archivo, "char");
                                        }   else if (strcmp(palabra, "incluir") == 0) {
                                             fprintf(archivo, "include");
                                            }   else if (strcmp(palabra, "devolver") == 0) {
                                                 fprintf(archivo, "return");
                                                }   else {
                                                     fprintf(archivo, "%s", palabra);
                                                    }
}


//Cargar una estructura que contiene un contacto
contacto cargar_contacto (FILE *archivo){
contacto X;
char y;

printf ("Ingrese el nombre completo siguiendo el formato ''nombre segundonombre apellido segundoapellido'':\n ");
fgets(X.NOMBRE, sizeof(X.NOMBRE), stdin);
size_t len = strlen(X.NOMBRE);
if (len > 0 && X.NOMBRE[len-1] == '\n') {
    X.NOMBRE[len-1] = '\0';
}

minusculas(strlen (X.NOMBRE),X.NOMBRE);
X.NOMBRE[0]= toupper (X.NOMBRE[0]);


printf ("Ingrese el número de teléfono siguiendo el formato ''##-###-###-####'' siendo los dos primeros caracteres el código de área:\n ");
fgets(X.TELEFONO, sizeof(X.TELEFONO), stdin);
len = strlen(X.TELEFONO);
if (len > 0 && X.TELEFONO[len-1] == '\n') {
    X.TELEFONO[len-1] = '\0';
}

printf ("Ingrese el DNI (sólo números sin utilizar ''.''):\n ");
scanf("%d", &X.DNI);

strcpy(X.ESTADO, "ACTIVO");

fwrite(&X, sizeof (X), 1, archivo);


return X;
 }


//Ordenar los contactos de la agenda
void ordenar_y_guardar_contactos(FILE *archivo) {
    contacto *contactos = NULL;  
    int count = 0;
    int capacidad = 10;  
    contactos = malloc(capacidad * sizeof(contacto)); //malloc me sirve para trabajar de manera dinamica, asi no tengo que limitar la cantidad de contactos, en un principio inicio la memoria para 10 contactos. 
    
    if (contactos == NULL) {
        printf("Error al asignar memoria.\n");
        return;
    }

    rewind(archivo);  
    while (fread(&contactos[count], sizeof(contacto), 1, archivo)) { //(dirección de memoria de la variable en la que se almacena, tamaño del dato a guadar, cantidad de datos, archivo del que se obtiene)
        count++;
        if (count >= capacidad) {
            capacidad *= 2;  
            contactos = realloc(contactos, capacidad * sizeof(contacto));// Si alcanzo el límite de la capacidad inicial, duplico el tamaño del arreglo utilizando
            if (contactos == NULL) {
                printf("Error al redimensionar la memoria.\n");
                return;
            }
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(contactos[j].NOMBRE, contactos[j + 1].NOMBRE) > 0) {
                contacto temp = contactos[j];
                contactos[j] = contactos[j + 1];
                contactos[j + 1] = temp;
            }
        }
    }

    fclose(archivo); 
    archivo = fopen("agenda_contactos.txt", "wb");  // Reabrir en modo escritura de binario
    fwrite(contactos, sizeof(contacto), count, archivo);

    printf("Contactos ordenados y guardados exitosamente.\n");

    
    free(contactos); // Así libero la memoria dinámica
}


//Elimino los contactos duplicados ya ordenados
void eliminar_duplicados(FILE *archivo) {
    contacto contacto_anterior, contacto_actual;
    int posicion_anterior, posicion_actual;
    
    rewind(archivo); 

    // Leo el primer contacto
    if (fread(&contacto_anterior, sizeof(contacto), 1, archivo) != 1) {
        //printf("El archivo está vacío o no se pudo leer.\n");
        return;
    }

    posicion_anterior = ftell(archivo) - sizeof(contacto); // Guardo la posición del primer contacto

   
    while (fread(&contacto_actual, sizeof(contacto), 1, archivo) == 1) {
        posicion_actual = ftell(archivo) - sizeof(contacto);  // Guardo la posición actual del segundo contacto

        
        if (strcmp(contacto_anterior.NOMBRE, contacto_actual.NOMBRE) == 0 &&
            strcmp(contacto_anterior.TELEFONO, contacto_actual.TELEFONO) == 0 &&
            contacto_anterior.DNI == contacto_actual.DNI) {

            // Marco el contacto actual como "INACTIVO"
            strcpy(contacto_actual.ESTADO, "INACTIVO");

            fseek(archivo, posicion_actual, SEEK_SET);

            fwrite(&contacto_actual, sizeof(contacto), 1, archivo);

            // Mover el puntero de vuelta al siguiente contacto (luego de sobrescribir)
            fseek(archivo, posicion_actual + sizeof(contacto), SEEK_SET);

            printf("Se ha marcado como INACTIVO el duplicado con nombre %s.\n", contacto_actual.NOMBRE);
        }
        // El contacto actual se convierte en el anterior
        contacto_anterior = contacto_actual;
        posicion_anterior = posicion_actual;
    }
}


//Modificar un dato de un contacto
void modificar_contacto(FILE *archivo, int dni) {
    contacto X;
    long posicion;
    int menu, si;

    rewind(archivo);  

    while (fread(&X, sizeof(contacto), 1, archivo)) {
        if (X.DNI == dni && strcmp(X.ESTADO, "ACTIVO") == 0) {
            
            printf("Es este el contacto que desea modificar?:\n");
            printf("Nombre: %s\n", X.NOMBRE);
            printf("Teléfono: %s\n", X.TELEFONO);
            printf("DNI: %d\n", X.DNI);

            printf ("Elija un número:\n 1.Si\n 2.No\n");
            scanf ("%d", &si);

            if (si == 1){
            posicion = ftell(archivo) - sizeof(contacto);

            
            printf("Qué campo desea modificar? Seleccione un número:\n 1.Nombre\n 2.Teléfono\n 3.DNI\n");
            scanf("%d", &menu);
            getchar();  

            switch (menu) {
                case 1:
                    printf("Ingrese el nuevo nombre completo: ");
                    fgets(X.NOMBRE, sizeof(X.NOMBRE), stdin);
                    size_t len = strlen(X.NOMBRE);
                    if (len > 0 && X.NOMBRE[len-1] == '\n') {
                        X.NOMBRE[len-1] = '\0';
                    }
                    break;

                case 2:
                    printf("Ingrese el nuevo número de teléfono: ");
                    fgets(X.TELEFONO, sizeof(X.TELEFONO), stdin);
                    len = strlen(X.TELEFONO);
                    if (len > 0 && X.TELEFONO[len-1] == '\n') {
                        X.TELEFONO[len-1] = '\0';
                    }
                    break;

                case 3:
                    printf("Ingrese el nuevo DNI: ");
                    scanf("%d", &X.DNI);
                    break;

                default:
                    printf("Opción no válida.\n");
                    break;
            }

            fseek(archivo, posicion, SEEK_SET);  
            fwrite(&X, sizeof(contacto), 1, archivo);
            printf("Contacto modificado exitosamente.\n");
            return;
        }
        printf("Ingrese un DNI válido.\n");
    }
    }
    
}


//Buscar y mostrar un contacto según el criterio seleccionado 
void consultar_contacto(FILE *archivo) {
    contacto X;
    int criterio;
    char nombre[40];
    char telefono[20];
    int dni;
    int encontrado = 0;

    printf("Seleccione el criterio de búsqueda:\n 1.Nombre\n 2.DNI\n 3.Teléfono\n");
    scanf("%d", &criterio);
    getchar();  

    rewind(archivo);  // Volver al inicio del archivo

    switch (criterio) {
        case 1:
            printf("Ingrese el nombre completo para buscar: ");
            fgets(nombre, sizeof(nombre), stdin);
            size_t len = strlen(nombre);
            if (len > 0 && nombre[len-1] == '\n') {
                nombre[len-1] = '\0';
            }

            while (fread(&X, sizeof(contacto), 1, archivo)) {
                if (strcmp(X.NOMBRE, nombre) == 0 && strcmp(X.ESTADO, "ACTIVO") == 0) {
                    printf("Contacto encontrado:\n");
                    printf("Nombre: %s\n", X.NOMBRE);
                    printf("Teléfono: %s\n", X.TELEFONO);
                    printf("DNI: %d\n", X.DNI);
                    encontrado = 1;
                    break;
                }
            }
            break;

        case 2:
            printf("Ingrese el DNI para buscar: ");
            scanf("%d", &dni);

            while (fread(&X, sizeof(contacto), 1, archivo)) {
                if (X.DNI == dni && strcmp(X.ESTADO, "ACTIVO") == 0) {
                    printf("Contacto encontrado:\n");
                    printf("Nombre: %s\n", X.NOMBRE);
                    printf("Teléfono: %s\n", X.TELEFONO);
                    printf("DNI: %d\n", X.DNI);
                    encontrado = 1;
                    break;
                }
            }
            break;

        case 3:
            printf("Ingrese el teléfono para buscar: ");
            fgets(telefono, sizeof(telefono), stdin);
            len = strlen(telefono);
            if (len > 0 && telefono[len-1] == '\n') {
                telefono[len-1] = '\0';
            }

            while (fread(&X, sizeof(contacto), 1, archivo)) {
                if (strcmp(X.TELEFONO, telefono) == 0 && strcmp(X.ESTADO, "ACTIVO") == 0) {
                    printf("Contacto encontrado:\n");
                    printf("Nombre: %s\n", X.NOMBRE);
                    printf("Teléfono: %s\n", X.TELEFONO);
                    printf("DNI: %d\n", X.DNI);
                    encontrado = 1;
                    break;
                }
            }
            break;

        default:
            printf("Criterio no válido.\n");
            break;
    }

    if (!encontrado) {
        printf("No se encontró un contacto con los datos proporcionados.\n");
    }
}


//Eliminar un contacto según su DNI
void eliminar_contacto(FILE *archivo, int dni) {
    contacto X;
    int encontrado = 0;
    int posicion, si;

    rewind(archivo); 

    while (fread(&X, sizeof(contacto), 1, archivo)) {
        if (X.DNI == dni && strcmp(X.ESTADO, "ACTIVO") == 0) {
            
            printf("Confirma la eliminación del siguiente contacto?\n");
            printf("Nombre: %s\n", X.NOMBRE);
            printf("Teléfono: %s\n", X.TELEFONO);
            printf("DNI: %d\n", X.DNI);

                printf ("Elija un número:\n 1.Si\n 2.No\n");
                scanf ("%d", &si);
                if (si == 1){    
                    strcpy(X.ESTADO, "INACTIVO");

                    posicion = ftell(archivo) - sizeof(contacto);
                    fseek(archivo, posicion, SEEK_SET);
                    fwrite(&X, sizeof(contacto), 1, archivo);

                    printf("El contacto ha sido eliminado.\n");
                    encontrado = 1;
                    break;
                }
                else {
                    printf("El contacto no ha sido eliminado.\n");
                }
        }
    }

    if (!encontrado) {
        printf("No se encontró un contacto con el DNI %d o ya fue eliminado.\n", dni);
    }
}


//Mostrar todos los contactos con estado "ACTIVO"
void mostrar_contactos(FILE *archivo) {
    contacto X;
    int encontrado = 0;

    rewind(archivo); 

    printf("A continuación se muestran los contactos de la agenda:\n");

    // Leer hasta que fread no pueda leer más (cuando fread devuelve 0)
    while (fread(&X, sizeof(contacto), 1, archivo) == 1) {
        if (strcmp(X.ESTADO, "ACTIVO") == 0) {
            printf("----------------------------\n");
            printf("Nombre: %s\n", X.NOMBRE);
            printf("Teléfono: %s\n", X.TELEFONO);
            printf("DNI: %d\n", X.DNI);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("No hay contactos en la agenda.\n");
    }
}
