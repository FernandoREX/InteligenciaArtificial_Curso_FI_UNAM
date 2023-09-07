// grafo.c

#include <stdio.h>
#include <stdlib.h>

// Estructura para representar un nodo en el grafo
typedef struct Nodo {
    int estado[3][3]; // Estado del tablero del juego
    struct Nodo* hijos[9]; // Nodos hijos correspondientes a las 9 posibles tiradas "X"
} Nodo;

// Función para crear un nuevo nodo en el grafo con el tablero inicializado
Nodo* crearNodo() {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) {
        perror("Error al asignar memoria para el nodo");
        exit(EXIT_FAILURE);
    }
    
    // Inicializar el tablero del juego como vacío
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            nuevoNodo->estado[i][j] = 0;
        }
    }

    // Inicializar los hijos como NULL
    for (int i = 0; i < 9; i++) {
        nuevoNodo->hijos[i] = NULL;
    }

    return nuevoNodo;
}

// Función para agregar una arista (nodo hijo) al grafo
void agregarArista(Nodo* padre, int tiradaX[3][3], int indiceHijo) {
    if (padre->hijos[indiceHijo] == NULL) {
        padre->hijos[indiceHijo] = crearNodo();
    }
    
    // Copiar el estado del tablero correspondiente a la tirada "X"
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            padre->hijos[indiceHijo]->estado[i][j] = tiradaX[i][j];
        }
    }
}

// Función para imprimir el grafo desde un nivel específico junto con información sobre el padre
void imprimirGrafoDesdeNivelConPadre(Nodo* nodo, int nivelDeseado, int nivelActual, Nodo* padre) {
    if (nodo == NULL) {
        return;
    }

    if (nivelActual == nivelDeseado) {
        printf("Nivel %d - Estado del tablero:\n", nivelActual);
        printf("Padre: Estado del tablero:\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d ", padre->estado[i][j]);
            }
            printf("\n");
        }
        printf("Actual: Estado del tablero:\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d ", nodo->estado[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    for (int i = 0; i < 9; i++) {
        imprimirGrafoDesdeNivelConPadre(nodo->hijos[i], nivelDeseado, nivelActual + 1, nodo);
    }
}

// Función principal (main) para probar el grafo
int main() {
    
    Nodo* grafo = crearNodo(); // Nodo inicial con el tablero vacío

    // Generar y agregar las 9 tiradas "X" posibles al grafo
    int tiradas10[9][3][3] = {
        {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}},//0
        {{0, 1, 0}, {0, 0, 0}, {0, 0, 0}},//1
        {{0, 0, 1}, {0, 0, 0}, {0, 0, 0}},//2
        {{0, 0, 0}, {1, 0, 0}, {0, 0, 0}},//3
        {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}},//4
        {{0, 0, 0}, {0, 0, 1}, {0, 0, 0}},//5
        {{0, 0, 0}, {0, 0, 0}, {1, 0, 0}},//6
        {{0, 0, 0}, {0, 0, 0}, {0, 1, 0}},//7
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 1}}//8
    };

    for (int i = 0; i < 9; i++) {
        agregarArista(grafo, tiradas10[i], i);
    }

    // Generar y agregar las 8 tiradas "O" posibles en el segundo movimiento
    int tiradas20[8][3][3] = {
        {{1, 2, 0}, {0, 0, 0}, {0, 0, 0}},
        {{1, 0, 2}, {0, 0, 0}, {0, 0, 0}},
        {{1, 0, 0}, {2, 0, 0}, {0, 0, 0}},
        {{1, 0, 0}, {0, 2, 0}, {0, 0, 0}},
        {{1, 0, 0}, {0, 0, 2}, {0, 0, 0}},
        {{1, 0, 0}, {0, 0, 0}, {2, 0, 0}},
        {{1, 0, 0}, {0, 0, 0}, {0, 2, 0}},
        {{1, 0, 0}, {0, 0, 0}, {0, 0, 2}}
    };

    int tiradas21[8][3][3] = {
        {{2, 1, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 1, 2}, {0, 0, 0}, {0, 0, 0}},
        {{0, 1, 0}, {2, 0, 0}, {0, 0, 0}},
        {{0, 1, 0}, {0, 2, 0}, {0, 0, 0}},
        {{0, 1, 0}, {0, 0, 2}, {0, 0, 0}},
        {{0, 1, 0}, {0, 0, 0}, {2, 0, 0}},
        {{0, 1, 0}, {0, 0, 0}, {0, 2, 0}},
        {{0, 1, 0}, {0, 0, 0}, {0, 0, 2}}
    };

    int tiradas22[8][3][3] = {
        {{2, 0, 1}, {0, 0, 0}, {0, 0, 0}},
        {{0, 2, 1}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 1}, {2, 0, 0}, {0, 0, 0}},
        {{0, 0, 1}, {0, 2, 0}, {0, 0, 0}},
        {{0, 0, 1}, {0, 0, 2}, {0, 0, 0}},
        {{0, 0, 1}, {0, 0, 0}, {2, 0, 0}},
        {{0, 0, 1}, {0, 0, 0}, {0, 2, 0}},
        {{0, 0, 1}, {0, 0, 0}, {0, 0, 2}}
    };

    int tiradas23[8][3][3] = {
        {{2, 0, 0}, {1, 0, 0}, {0, 0, 0}},
        {{0, 2, 0}, {1, 0, 0}, {0, 0, 0}},
        {{0, 0, 2}, {1, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {1, 2, 0}, {0, 0, 0}},
        {{0, 0, 0}, {1, 0, 2}, {0, 0, 0}},
        {{0, 0, 0}, {1, 0, 0}, {2, 0, 0}},
        {{0, 0, 0}, {1, 0, 0}, {0, 2, 0}},
        {{0, 0, 0}, {1, 0, 0}, {0, 0, 2}}
    };

    int tiradas24[8][3][3] = {
        {{2, 0, 0}, {0, 1, 0}, {0, 0, 0}},
        {{0, 2, 0}, {0, 1, 0}, {0, 0, 0}},
        {{0, 0, 2}, {0, 1, 0}, {0, 0, 0}},
        {{0, 0, 0}, {2, 1, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 1, 2}, {0, 0, 0}},
        {{0, 0, 0}, {0, 1, 0}, {2, 0, 0}},
        {{0, 0, 0}, {0, 1, 0}, {0, 2, 0}},
        {{0, 0, 0}, {0, 1, 0}, {0, 0, 2}}
    };

    int tiradas25[8][3][3] = {
        {{2, 0, 0}, {0, 0, 1}, {0, 0, 0}},
        {{0, 2, 0}, {0, 0, 1}, {0, 0, 0}},
        {{0, 0, 2}, {0, 0, 1}, {0, 0, 0}},
        {{0, 0, 0}, {2, 0, 1}, {0, 0, 0}},
        {{0, 0, 0}, {0, 2, 1}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 1}, {2, 0, 0}},
        {{0, 0, 0}, {0, 0, 1}, {0, 2, 0}},
        {{0, 0, 0}, {0, 0, 1}, {0, 0, 2}}
    };

    int tiradas26[8][3][3] = {
        {{2, 0, 0}, {0, 0, 0}, {1, 0, 0}},
        {{0, 2, 0}, {0, 0, 0}, {1, 0, 0}},
        {{0, 0, 2}, {0, 0, 0}, {1, 0, 0}},
        {{0, 0, 0}, {2, 0, 0}, {1, 0, 0}},
        {{0, 0, 0}, {0, 2, 0}, {1, 0, 0}},
        {{0, 0, 0}, {0, 0, 2}, {1, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {1, 2, 0}},
        {{0, 0, 0}, {0, 0, 0}, {1, 0, 2}}
    };

    int tiradas27[8][3][3] = {
        {{2, 0, 0}, {0, 0, 0}, {0, 1, 0}},
        {{0, 2, 0}, {0, 0, 0}, {0, 1, 0}},
        {{0, 0, 2}, {0, 0, 0}, {0, 1, 0}},
        {{0, 0, 0}, {2, 0, 0}, {0, 1, 0}},
        {{0, 0, 0}, {0, 2, 0}, {0, 1, 0}},
        {{0, 0, 0}, {0, 0, 2}, {0, 1, 0}},
        {{0, 0, 0}, {0, 0, 0}, {2, 1, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 1, 2}}
    };

    int tiradas28[8][3][3] = {
        {{2, 0, 0}, {0, 0, 0}, {0, 0, 1}},
        {{0, 2, 0}, {0, 0, 0}, {0, 0, 1}},
        {{0, 0, 2}, {0, 0, 0}, {0, 0, 1}},
        {{0, 0, 0}, {2, 0, 0}, {0, 0, 1}},
        {{0, 0, 0}, {0, 2, 0}, {0, 0, 1}},
        {{0, 0, 0}, {0, 0, 2}, {0, 0, 1}},
        {{0, 0, 0}, {0, 0, 0}, {2, 0, 1}},
        {{0, 0, 0}, {0, 0, 0}, {0, 2, 1}}
    };

    // Agregar las 9 tiradas "O" al grafo
    for (int i = 0; i < 8; i++) {
        agregarArista(grafo->hijos[0], tiradas20[i], i);
        agregarArista(grafo->hijos[1], tiradas21[i], i);
        agregarArista(grafo->hijos[2], tiradas22[i], i);
        agregarArista(grafo->hijos[3], tiradas23[i], i);
        agregarArista(grafo->hijos[4], tiradas24[i], i);
        agregarArista(grafo->hijos[5], tiradas25[i], i);
        agregarArista(grafo->hijos[6], tiradas26[i], i);
        agregarArista(grafo->hijos[7], tiradas27[i], i);
        agregarArista(grafo->hijos[8], tiradas28[i], i);
        printf("Se agrego un nodo\n");
    }

    int tiradas30[7][3][3] = {
        {{1, 2, 1}, {0, 0, 0}, {0, 0, 0}},
        {{1, 2, 0}, {1, 0, 0}, {0, 0, 0}},
        {{1, 2, 0}, {0, 1, 0}, {0, 0, 0}},
        {{1, 2, 0}, {0, 0, 1}, {0, 0, 0}},
        {{1, 2, 0}, {0, 0, 0}, {1, 0, 0}},
        {{1, 2, 0}, {0, 0, 0}, {0, 1, 0}},
        {{1, 2, 0}, {0, 0, 0}, {0, 0, 1}}
    };

    int tiradas31[7][3][3] = {
        {{1, 1, 2}, {0, 0, 0}, {0, 0, 0}},
        {{1, 0, 2}, {1, 0, 0}, {0, 0, 0}},
        {{1, 0, 2}, {0, 1, 0}, {0, 0, 0}},
        {{1, 0, 2}, {0, 0, 1}, {0, 0, 0}},
        {{1, 0, 2}, {0, 0, 0}, {1, 0, 0}},
        {{1, 0, 2}, {0, 0, 0}, {0, 1, 0}},
        {{1, 0, 2}, {0, 0, 0}, {0, 0, 1}}
    };

    int tiradas32[7][3][3] = {
        {{1, 1, 0}, {2, 0, 0}, {0, 0, 0}},
        {{1, 0, 1}, {2, 0, 0}, {0, 0, 0}},
        {{1, 0, 0}, {2, 1, 0}, {0, 0, 0}},
        {{1, 0, 0}, {2, 0, 1}, {0, 0, 0}},
        {{1, 0, 0}, {2, 0, 0}, {1, 0, 0}},
        {{1, 0, 0}, {2, 0, 0}, {0, 1, 0}},
        {{1, 0, 0}, {2, 0, 0}, {0, 0, 1}}
    };

    int tiradas33[7][3][3] = {
        {{1, 1, 0}, {0, 2, 0}, {0, 0, 0}},
        {{1, 0, 1}, {0, 2, 0}, {0, 0, 0}},
        {{1, 0, 0}, {1, 2, 0}, {0, 0, 0}},
        {{1, 0, 0}, {0, 2, 1}, {0, 0, 0}},
        {{1, 0, 0}, {0, 2, 0}, {1, 0, 0}},
        {{1, 0, 0}, {0, 2, 0}, {0, 1, 0}},
        {{1, 0, 0}, {0, 2, 0}, {0, 0, 1}}
    };

    int tiradas34[7][3][3] = {
        {{1, 1, 0}, {0, 0, 2}, {0, 0, 0}},
        {{1, 0, 1}, {0, 0, 2}, {0, 0, 0}},
        {{1, 0, 0}, {1, 0, 2}, {0, 0, 0}},
        {{1, 0, 0}, {0, 1, 2}, {0, 0, 0}},
        {{1, 0, 0}, {0, 0, 2}, {1, 0, 0}},
        {{1, 0, 0}, {0, 0, 2}, {0, 1, 0}},
        {{1, 0, 0}, {0, 0, 2}, {0, 0, 1}}
    };

    int tiradas35[7][3][3] = {
        {{1, 1, 0}, {0, 0, 0}, {2, 0, 0}},
        {{1, 0, 1}, {0, 0, 0}, {2, 0, 0}},
        {{1, 0, 0}, {1, 0, 0}, {2, 0, 0}},
        {{1, 0, 0}, {0, 1, 0}, {2, 0, 0}},
        {{1, 0, 0}, {0, 0, 1}, {2, 0, 0}},
        {{1, 0, 0}, {0, 0, 0}, {2, 1, 0}},
        {{1, 0, 0}, {0, 0, 0}, {2, 0, 1}}
    };

    int tiradas36[7][3][3] = {
        {{1, 1, 0}, {0, 0, 0}, {0, 2, 0}},
        {{1, 0, 1}, {0, 0, 0}, {0, 2, 0}},
        {{1, 0, 0}, {1, 0, 0}, {0, 2, 0}},
        {{1, 0, 0}, {0, 1, 0}, {0, 2, 0}},
        {{1, 0, 0}, {0, 0, 1}, {0, 2, 0}},
        {{1, 0, 0}, {0, 0, 0}, {1, 2, 0}},
        {{1, 0, 0}, {0, 0, 0}, {0, 2, 1}}
    };

    int tiradas37[7][3][3] = {
        {{1, 1, 0}, {0, 0, 0}, {0, 0, 2}},
        {{1, 0, 1}, {0, 0, 0}, {0, 0, 2}},
        {{1, 0, 0}, {1, 0, 0}, {0, 0, 2}},
        {{1, 0, 0}, {0, 1, 0}, {0, 0, 2}},
        {{1, 0, 0}, {0, 0, 1}, {0, 0, 2}},
        {{1, 0, 0}, {0, 0, 0}, {1, 0, 2}},
        {{1, 0, 0}, {0, 0, 0}, {0, 1, 2}}
    };

    int tiradas30_1[7][3][3] = {
        {{2, 1, 1}, {0, 0, 0}, {0, 0, 0}},
        {{2, 1, 0}, {1, 0, 0}, {0, 0, 0}},
        {{2, 1, 0}, {0, 1, 0}, {0, 0, 0}},
        {{2, 1, 0}, {0, 0, 1}, {0, 0, 0}},
        {{2, 1, 0}, {0, 0, 0}, {1, 0, 0}},
        {{2, 1, 0}, {0, 0, 0}, {0, 1, 0}},
        {{2, 1, 0}, {0, 0, 0}, {0, 0, 1}}
    };

    int tiradas31_1[7][3][3] = {
        {{1, 1, 2}, {0, 0, 0}, {0, 0, 0}},
        {{0, 1, 2}, {1, 0, 0}, {0, 0, 0}},
        {{0, 1, 2}, {0, 1, 0}, {0, 0, 0}},
        {{0, 1, 2}, {0, 0, 1}, {0, 0, 0}},
        {{0, 1, 2}, {0, 0, 0}, {1, 0, 0}},
        {{0, 1, 2}, {0, 0, 0}, {0, 1, 0}},
        {{0, 1, 2}, {0, 0, 0}, {0, 0, 1}}
    };

    int tiradas32_1[7][3][3] = {
        {{1, 1, 0}, {2, 0, 0}, {0, 0, 0}},
        {{1, 0, 1}, {2, 0, 0}, {0, 0, 0}},
        {{1, 0, 0}, {2, 1, 0}, {0, 0, 0}},
        {{1, 0, 0}, {2, 0, 1}, {0, 0, 0}},
        {{1, 0, 0}, {2, 0, 0}, {1, 0, 0}},
        {{1, 0, 0}, {2, 0, 0}, {0, 1, 0}},
        {{1, 0, 0}, {2, 0, 0}, {0, 0, 1}}
    };

    //Aqui estan bien, de aqui para abajo me falata modificar

    int tiradas33_1[7][3][3] = {
        {{1, 1, 0}, {0, 2, 0}, {0, 0, 0}},
        {{1, 0, 1}, {0, 2, 0}, {0, 0, 0}},
        {{1, 0, 0}, {1, 2, 0}, {0, 0, 0}},
        {{1, 0, 0}, {0, 2, 1}, {0, 0, 0}},
        {{1, 0, 0}, {0, 2, 0}, {1, 0, 0}},
        {{1, 0, 0}, {0, 2, 0}, {0, 1, 0}},
        {{1, 0, 0}, {0, 2, 0}, {0, 0, 1}}
    };

    int tiradas34_1[7][3][3] = {
        {{1, 1, 0}, {0, 0, 2}, {0, 0, 0}},
        {{1, 0, 1}, {0, 0, 2}, {0, 0, 0}},
        {{1, 0, 0}, {1, 0, 2}, {0, 0, 0}},
        {{1, 0, 0}, {0, 1, 2}, {0, 0, 0}},
        {{1, 0, 0}, {0, 0, 2}, {1, 0, 0}},
        {{1, 0, 0}, {0, 0, 2}, {0, 1, 0}},
        {{1, 0, 0}, {0, 0, 2}, {0, 0, 1}}
    };

    int tiradas35_1[7][3][3] = {
        {{1, 1, 0}, {0, 0, 0}, {2, 0, 0}},
        {{1, 0, 1}, {0, 0, 0}, {2, 0, 0}},
        {{1, 0, 0}, {1, 0, 0}, {2, 0, 0}},
        {{1, 0, 0}, {0, 1, 0}, {2, 0, 0}},
        {{1, 0, 0}, {0, 0, 1}, {2, 0, 0}},
        {{1, 0, 0}, {0, 0, 0}, {2, 1, 0}},
        {{1, 0, 0}, {0, 0, 0}, {2, 0, 1}}
    };

    int tiradas36_1[7][3][3] = {
        {{1, 1, 0}, {0, 0, 0}, {0, 2, 0}},
        {{1, 0, 1}, {0, 0, 0}, {0, 2, 0}},
        {{1, 0, 0}, {1, 0, 0}, {0, 2, 0}},
        {{1, 0, 0}, {0, 1, 0}, {0, 2, 0}},
        {{1, 0, 0}, {0, 0, 1}, {0, 2, 0}},
        {{1, 0, 0}, {0, 0, 0}, {1, 2, 0}},
        {{1, 0, 0}, {0, 0, 0}, {0, 2, 1}}
    };

    int tiradas37_1[7][3][3] = {
        {{1, 1, 0}, {0, 0, 0}, {0, 0, 2}},
        {{1, 0, 1}, {0, 0, 0}, {0, 0, 2}},
        {{1, 0, 0}, {1, 0, 0}, {0, 0, 2}},
        {{1, 0, 0}, {0, 1, 0}, {0, 0, 2}},
        {{1, 0, 0}, {0, 0, 1}, {0, 0, 2}},
        {{1, 0, 0}, {0, 0, 0}, {1, 0, 2}},
        {{1, 0, 0}, {0, 0, 0}, {0, 1, 2}}
    };

    // Agregar las 7*8 tiradas "x" al grafo
    for (int i = 0; i < 8; i++) {
        agregarArista(grafo->hijos[0]->hijos[0], tiradas30[i], i);
        agregarArista(grafo->hijos[0]->hijos[1], tiradas31[i], i);
        agregarArista(grafo->hijos[0]->hijos[2], tiradas32[i], i);
        agregarArista(grafo->hijos[0]->hijos[3], tiradas33[i], i);
        agregarArista(grafo->hijos[0]->hijos[4], tiradas34[i], i);
        agregarArista(grafo->hijos[0]->hijos[5], tiradas35[i], i);
        agregarArista(grafo->hijos[0]->hijos[6], tiradas36[i], i);
        agregarArista(grafo->hijos[0]->hijos[7], tiradas37[i], i);

        agregarArista(grafo->hijos[1]->hijos[0], tiradas30_1[i], i);
        agregarArista(grafo->hijos[1]->hijos[1], tiradas31_1[i], i);
        agregarArista(grafo->hijos[1]->hijos[2], tiradas32_1[i], i);
        agregarArista(grafo->hijos[1]->hijos[3], tiradas33_1[i], i);
        agregarArista(grafo->hijos[1]->hijos[4], tiradas34_1[i], i);
        agregarArista(grafo->hijos[1]->hijos[5], tiradas35_1[i], i);
        agregarArista(grafo->hijos[1]->hijos[6], tiradas36_1[i], i);
        agregarArista(grafo->hijos[1]->hijos[7], tiradas37_1[i], i);
        printf("Se agrego un nodo\n");
    }

    // Imprimir el grafo desde un nivel específico
    int nivelDeseado = 3; // Cambia esto al nivel que desees imprimir
    imprimirGrafoDesdeNivelConPadre(grafo, nivelDeseado, 0, NULL);
    return 0;
}