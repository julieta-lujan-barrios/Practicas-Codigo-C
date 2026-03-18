#include <stdio.h>
#include <stdlib.h>

// Estructura del nodo
struct nodo {
    int info;
    struct nodo *punt;
};

// Torres (todas comienzan vacías, por eso pongo NULL)
struct nodo *torreA = NULL;
struct nodo *torreB = NULL;
struct nodo *torreC = NULL;

// Función para insertar un disco en una torre (cualquier torre)
struct nodo* insertar(struct nodo *torre, int disco) { 
    // Tomo el nodo actual de la torre, que puede ser NULL si está vacía.
    struct nodo *nuevo;
    nuevo = malloc(sizeof(struct nodo));  // Reservo memoria para un nuevo nodo (nuevo disco en la torre)
   
    nuevo->info = disco;   // Asigno el valor del disco al nodo recién creado.

    nuevo->punt = torre; // El nuevo nodo apunta al nodo anterior, enlazando la lista. Al principio será NULL si es el primer nodo.
    return nuevo;  // Retorno el nuevo nodo como la nueva "raíz" de la torre
}

// Función para extraer un disco de una torre (cualquier torre)
struct nodo* extraer(struct nodo *torre, int *disco) { 
    // torre es el nodo actual de la torre de donde vamos a extraer el disco y el puntero en disco es para que apunte al tope de la lista
    if (torre == NULL) {
        printf("La torre está vacía\n");
    } else {
        struct nodo *aux;
        aux = torre;  // Guardo el nodo actual en aux para liberarlo después
        *disco = torre->info;  // Asigno el valor del disco extraído al puntero disco
        torre = torre->punt;  // Actualizo el puntero torre al siguiente nodo (el que está debajo)
        free(aux);  // Libero la memoria del nodo extraído
        return torre;  // Retorno la torre actualizada con el nuevo tope
    }
}

// Función para mover un disco de una torre a otra
void moverDisco(int origen, int destino) { 
    int disco;  // Variable para almacenar el disco extraído sin puntero, porque proviene de la funcion extraer
    
    // Extraigo el disco de la torre de origen
    if (origen == 1) { 
        torreA = extraer(torreA, &disco);  // Extraigo el disco de la torre A y asi con los demas
    } else if (origen == 2) {
        torreB = extraer(torreB, &disco);  
    } else {
        torreC = extraer(torreC, &disco);  
    }

    // Inserto el disco en la torre destino
    if (destino == 1) {          
        torreA = insertar(torreA, disco);  // Inserta el disco en la torre A y asi con los demas
    } else if (destino == 2) {
        torreB = insertar(torreB, disco);  
    } else {
        torreC = insertar(torreC, disco);  
    }
    printf("Mover disco %d de Torre %d a Torre %d\n", disco, origen, destino);  
}

// Función recursiva para resolver la Torre de Hanói (Me ayude del patron con internet)
void hanoi(int numDiscos, int origen, int destino, int auxiliar) {
    if (numDiscos == 1) {  // Si solo queda un disco, lo muevo directamente al destino
        moverDisco(origen, destino);
    } else {
        // Muevo los discos de la torre de origen a la torre auxiliar (toma el papel de la torre destino)
        hanoi(numDiscos - 1, origen, auxiliar, destino);
        // Muevo el disco más grande de la torre de origen a la torre de destino (ya que al restar uno queda el disco mas grande solo)
        moverDisco(origen, destino);
        // Muevo los discos de la torre auxiliar (la torre origen) a la torre de destino y uso la torre origen como auxiliar
        hanoi(numDiscos - 1, auxiliar, destino, origen);
    }
}

// Función para mostrar el estado de una torre
void mostrar(struct nodo *torre, char nombre) {
    printf("Torre %c: ", nombre);
    if (torre == NULL) {  // Si la torre está vacía
        printf("(torre vacía)\n");
        return;
    }
    while (torre != NULL) {  // Recorro la lista de nodos (discos) en la torre
        printf("%d ", torre->info);  // Mostrar el valor del disco actual (el del tope)
        torre = torre->punt;  // Avanzar al siguiente nodo (disco) hasta que sea NULL 
    }

}

void DiscosTorreA();

int main() {
    int numDiscos;

    printf("Introduce el número de discos: ");
    scanf("%d", &numDiscos);

    // Coloco los discos en la torre A
    DiscosTorreA(numDiscos);

    printf("\nInicio de las Torres:\n");
    mostrar(torreA, 'A');
    mostrar(torreB, 'B');
    mostrar(torreC, 'C');

    // Resolocion del juego de la Torre de Hanói
    hanoi(numDiscos, 1, 3, 2);

    
    printf("\nResultado de las Torres:\n");
    mostrar(torreA, 'A');
    mostrar(torreB, 'B');
    mostrar(torreC, 'C');

    return 0;
}

// Función para poner los discos en la torre A
void DiscosTorreA(int numDiscos) {
    for (int i = numDiscos; i > 0; i--) {  // pongo desde el disco más grande hasta el más pequeño
        torreA = insertar(torreA, i);  // Inserto cada disco en la torre A
    }
}
