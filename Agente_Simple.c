#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprimir_tablero(char tablero[3][3]) {
    for (int fila = 0; fila < 3; fila++) {
        for (int col = 0; col < 3; col++) {
            printf("%c", tablero[fila][col]);  // Imprime el contenido de la celda
            if (col < 2) {
                printf(" | ");  // Imprime el separador de columnas
            }
        }
        printf("\n");
        if (fila < 2) {
            printf("---------\n");  // Imprime la línea horizontal entre filas
        }
    }
}

int es_ganador(char tablero[3][3], char jugador) {
    // Verifica si el jugador ha ganado en alguna fila
    for (int fila = 0; fila < 3; fila++) {
        if (tablero[fila][0] == jugador && tablero[fila][1] == jugador && tablero[fila][2] == jugador) {
            return 1;  // El jugador ha ganado
        }
    }

    // Verifica si el jugador ha ganado en alguna columna
    for (int col = 0; col < 3; col++) {
        if (tablero[0][col] == jugador && tablero[1][col] == jugador && tablero[2][col] == jugador) {
            return 1;  // El jugador ha ganado
        }
    }

    // Verifica si el jugador ha ganado en alguna diagonal
    if (tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) {
        return 1;  // El jugador ha ganado
    }

    if (tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador) {
        return 1;  // El jugador ha ganado
    }

    return 0;  // El jugador no ha ganado
}

int tablero_lleno(char tablero[3][3]) {
    // Verifica si el tablero está completamente lleno
    for (int fila = 0; fila < 3; fila++) {
        for (int col = 0; col < 3; col++) {
            if (tablero[fila][col] == ' ') {
                return 0;  // El tablero no está lleno
            }
        }
    }
    return 1;  // El tablero está lleno
}

void jugar() {
    char tablero[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };  // Crea un tablero vacío de 3x3
    char jugadores[2] = {'X', 'O'};
    char jugador_actual = jugadores[rand() % 2];  // Selecciona aleatoriamente quién comienza

    printf("¡Bienvenido al juego de Gato!\n");

    while (1) {  // Bucle principal del juego
        imprimir_tablero(tablero);
        printf("Turno del jugador %c\n", jugador_actual);

        if (jugador_actual == 'X') {
            int fila, col;
            while (1) {
                printf("Ingrese el número de fila (0-2): ");
                scanf("%d", &fila);  // Lee la fila ingresada por el jugador
                printf("Ingrese el número de columna (0-2): ");
                scanf("%d", &col);  // Lee la columna ingresada por el jugador

                if (fila >= 0 && fila < 3 && col >= 0 && col < 3 && tablero[fila][col] == ' ') {
                    tablero[fila][col] = jugador_actual;  // Coloca el símbolo del jugador en el tablero
                    break;
                } else {
                    printf("Esa casilla ya está ocupada o los valores son incorrectos. Intente nuevamente.\n");
                }
            }
        } else {
            int fila, col;
            while (1) {
                fila = rand() % 3;  // Genera una fila aleatoria
                col = rand() % 3;  // Genera una columna aleatoria

                if (tablero[fila][col] == ' ') {
                    tablero[fila][col] = jugador_actual;  // Coloca el símbolo del jugador en el tablero
                    break;
                }
            }
        }

        if (es_ganador(tablero, jugador_actual)) {
            imprimir_tablero(tablero);
            printf("¡El jugador %c ha ganado!\n", jugador_actual);
            break;
        } else if (tablero_lleno(tablero)) {
            imprimir_tablero(tablero);
            printf("¡Es un empate!\n");
            break;
        }

        jugador_actual = (jugador_actual == jugadores[0]) ? jugadores[1] : jugadores[0];  // Cambia el turno del jugador
    }
}

int main() {
    srand(time(NULL));  // Inicializa la semilla para números aleatorios
    jugar();  // Inicia el juego llamando a la función jugar()
    return 0;
}
