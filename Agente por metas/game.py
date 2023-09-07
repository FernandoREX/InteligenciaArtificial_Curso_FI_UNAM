import random  # Importar el módulo random para generar números aleatorios
import math    # Importar el módulo math para cálculos matemáticos
import os      # Importar el módulo os para limpiar la pantalla

# X es el jugador máximo = 1
# O es el jugador mínimo = -1

class Gato:
    def __init__(self):
        # Inicializar el juego con un tablero vacío representado como una lista de 9 elementos '-'
        self.tablero = ['-' for _ in range(9)]
        
        # Decidir aleatoriamente qué jugador comienza (jugador humano o IA)
        if random.randint(0, 1) == 1:
            self.jugadorHumano = 'X'
            self.jugadorBot = "O"
        else:
            self.jugadorHumano = "O"
            self.jugadorBot = "X"

    def mostrar_tablero(self):
        print("")
        # Mostrar el estado actual del tablero en la consola
        for i in range(3):
            print("  ", self.tablero[0 + (i * 3)], " | ", self.tablero[1 + (i * 3)], " | ", self.tablero[2 + (i * 3)])
            print("")

    def tablero_lleno(self, estado):
        # Verificar si el tablero está lleno (sin espacios en blanco '-')
        return not "-" in estado

    def jugador_gana(self, estado, jugador):
        # Verificar si un jugador ha ganado el juego (combinaciones ganadoras)
        if estado[0] == estado[1] == estado[2] == jugador: return True
        if estado[3] == estado[4] == estado[5] == jugador: return True
        if estado[6] == estado[7] == estado[8] == jugador: return True
        if estado[0] == estado[3] == estado[6] == jugador: return True
        if estado[1] == estado[4] == estado[7] == jugador: return True
        if estado[2] == estado[5] == estado[8] == jugador: return True
        if estado[0] == estado[4] == estado[8] == jugador: return True
        if estado[2] == estado[4] == estado[6] == jugador: return True

        return False

    def verificar_ganador(self):
        # Comprobar si hay un ganador o empate en el juego
        if self.jugador_gana(self.tablero, self.jugadorHumano):
            os.system("cls")  # Limpiar la pantalla en Windows (puedes cambiar a "clear" en sistemas Unix)
            print(f"   ¡El jugador {self.jugadorHumano} gana el juego!")
            return True
            
        if self.jugador_gana(self.tablero, self.jugadorBot):
            os.system("cls")
            print(f"   ¡El jugador {self.jugadorBot} gana el juego!")
            return True

        # Comprobar si el juego termina en empate
        if self.tablero_lleno(self.tablero):
            os.system("cls")
            print("   ¡Empate!")
            return True
        return False

    def iniciar(self):
        bot = JugadorMaquina(self.jugadorBot)  # Crear un jugador de IA
        humano = JugadorHumano(self.jugadorHumano)  # Crear un jugador humano
        while True:
            os.system("cls")  # Limpiar la pantalla en Windows (puedes cambiar a "clear" en sistemas Unix)
            print(f"   Turno del jugador {self.jugadorHumano}")
            self.mostrar_tablero()
            
            # Turno del jugador humano
            casilla = humano.movimiento_humano(self.tablero)
            self.tablero[casilla] = self.jugadorHumano
            if self.verificar_ganador():
                break
            
            # Turno de la IA
            casilla = bot.movimiento_maquina(self.tablero)
            self.tablero[casilla] = self.jugadorBot
            if self.verificar_ganador():
                break

        # Mostrar la vista final del tablero
        print()
        self.mostrar_tablero()

class JugadorHumano:
    def __init__(self, letra):
        self.letra = letra

    def movimiento_humano(self, estado):
        # Tomar la entrada del usuario y validarla
        while True:
            casilla = int(input("Ingrese el número de casilla (1-9): "))
            print()
            if estado[casilla - 1] == "-":
                break
        return casilla - 1

class JugadorMaquina(Gato):
    def __init__(self, letra):
        self.jugadorBot = letra
        self.jugadorHumano = "X" if letra == "O" else "O"

    def jugadores(self, estado):
        # Determinar qué jugador es el actual (basado en el número de fichas en el tablero)
        n = len(estado)
        x = 0
        o = 0
        for i in range(9):
            if (estado[i] == "X"):
                x = x + 1
            if (estado[i] == "O"):
                o = o + 1

        if (self.jugadorHumano == "X"):
            return "X" if x == o else "O"
        if (self.jugadorHumano == "O"):
            return "O" if x == o else "X"

    def acciones(self, estado):
        # Obtener una lista de casillas vacías en el tablero
        return [i for i, x in enumerate(estado) if x == "-"]

    def resultado(self, estado, accion):
        # Generar un nuevo estado del tablero después de realizar una acción (movimiento)
        nuevoEstado = estado.copy()
        jugador = self.jugadores(estado)
        nuevoEstado[accion] = jugador
        return nuevoEstado

    def terminal(self, estado):
        # Verificar si el juego ha terminado (alguien ha ganado o empate)
        if (self.jugador_gana(estado, "X")):
            return True
        if (self.jugador_gana(estado, "O")):
            return True
        return False

    def minimax(self, estado, jugador):
        jugadorMax = self.jugadorHumano  # Tú mismo
        otroJugador = 'O' if jugador == 'X' else 'X'

        # Primero, verificamos si el movimiento anterior es un ganador
        if self.terminal(estado):
            # Si el juego ha terminado, asignamos una puntuación basada en el resultado.
            # Si ganó el jugador humano (jugadorMax), la puntuación es alta.
            # Si ganó la IA (otroJugador), la puntuación es baja.
            # Si es un empate, la puntuación es 0.
            return {'posicion': None, 'puntaje': 1 * (len(self.acciones(estado)) + 1) if otroJugador == jugadorMax else -1 * (
                        len(self.acciones(estado)) + 1)}
        elif self.tablero_lleno(estado):
            # Si el juego termina en empate, la puntuación es 0.
            return {'posicion': None, 'puntaje': 0}

        if jugador == jugadorMax:
            mejor = {'posicion': None, 'puntaje': -math.inf}  # Inicializar la puntuación con un valor negativo infinito para maximizar
        else:
            mejor = {'posicion': None, 'puntaje': math.inf}  # Inicializar la puntuación con un valor positivo infinito para minimizar

        for movimiento_posible in self.acciones(estado):
            nuevoEstado = self.resultado(estado, movimiento_posible)  # Simular un movimiento
            sim_puntaje = self.minimax(nuevoEstado, otroJugador)  # Llamada recursiva al minimax para el siguiente nivel del árbol

            sim_puntaje['posicion'] = movimiento_posible  # Registrar la posición del movimiento simulado

            if jugador == jugadorMax:
                # Si es el turno de la IA (jugadorMax), se busca maximizar la puntuación.
                if sim_puntaje['puntaje'] > mejor['puntaje']:
                    mejor = sim_puntaje  # Actualizar el mejor movimiento si la puntuación es mayor
            else:
                # Si es el turno del oponente humano, se busca minimizar la puntuación.
                if sim_puntaje['puntaje'] < mejor['puntaje']:
                    mejor = sim_puntaje  # Actualizar el mejor movimiento si la puntuación es menor

        return mejor  # Devolver el mejor movimiento y su puntuación

    def movimiento_maquina(self, estado):
        # La función principal que decide el movimiento de la IA utilizando el algoritmo Minimax
        casilla = self.minimax(estado, self.jugadorBot)['posicion']
        return casilla

# Iniciar el juego
gato = Gato()
gato.iniciar()