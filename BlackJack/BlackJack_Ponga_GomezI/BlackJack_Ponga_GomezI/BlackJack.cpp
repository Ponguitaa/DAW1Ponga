#include <iostream>
#include <cstdlib>
#include <ctime>

// Funci�n para generar un n�mero aleatorio entre min y max
int generarNumeroAleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Funci�n para calcular el valor de una mano de Blackjack
int calcularValorMano(int mano[], int tama�o) {
    int valor = 0;
    int ases = 0;
    for (int i = 0; i < tama�o; ++i) {
        if (mano[i] == 1) {
            ases++;
        }
        valor += mano[i];
    }
    while (ases > 0 && valor + 10 <= 21) {
        valor += 10;
        ases--;
    }
    return valor;
}

// Funci�n principal para el juego de Blackjack
void jugarBlackjack() {
    const int TAMANIO_MANO = 12;
    int manoJugador[TAMANIO_MANO];
    int manoCrupier[TAMANIO_MANO];
    int cartaActual = 0;

    // Inicializar el generador de n�meros aleatorios
    srand(time(0));

    // Inicializar manos
    manoJugador[0] = generarNumeroAleatorio(1, 13);
    manoCrupier[0] = generarNumeroAleatorio(1, 13);
    manoJugador[1] = generarNumeroAleatorio(1, 13);
    manoCrupier[1] = generarNumeroAleatorio(1, 13);
    int tama�oManoJugador = 2;
    int tama�oManoCrupier = 2;

    // Mostrar cartas del jugador y una del crupier
    std::cout << "Tu mano: " << manoJugador[0] << " " << manoJugador[1] << std::endl;
    std::cout << "Mano del crupier: " << manoCrupier[0] << std::endl;

    // Continuar jugando hasta que el jugador decida plantarse o se pase de 21
    char eleccion;
    while (true) {
        std::cout << "�Quieres pedir otra carta? (s/n): ";
        std::cin >> eleccion;
        if (eleccion == 's') {
            manoJugador[tama�oManoJugador++] = generarNumeroAleatorio(1, 13);
            std::cout << "Tu mano: ";
            for (int i = 0; i < tama�oManoJugador; ++i) {
                std::cout << manoJugador[i] << " ";
            }
            std::cout << std::endl;
            if (calcularValorMano(manoJugador, tama�oManoJugador) > 21) {
                std::cout << "Te has pasado de 21. Pierdes." << std::endl;
                return;
            }
        }
        else {
            break;
        }
    }

    // Jugar para el crupier
    while (calcularValorMano(manoCrupier, tama�oManoCrupier) < 17) {
        manoCrupier[tama�oManoCrupier++] = generarNumeroAleatorio(1, 13);
    }

    // Mostrar manos finales
    std::cout << "Tu mano final: ";
    for (int i = 0; i < tama�oManoJugador; ++i) {
        std::cout << manoJugador[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Mano del crupier final: ";
    for (int i = 0; i < tama�oManoCrupier; ++i) {
        std::cout << manoCrupier[i] << " ";
    }
    std::cout << std::endl;

    // Determinar ganador
    int valorJugador = calcularValorMano(manoJugador, tama�oManoJugador);
    int valorCrupier = calcularValorMano(manoCrupier, tama�oManoCrupier);
    if (valorJugador > valorCrupier || valorCrupier > 21) {
        std::cout << "�Felicidades! Has ganado." << std::endl;
    }
    else if (valorJugador < valorCrupier) {
        std::cout << "El crupier gana." << std::endl;
    }
    else {
        std::cout << "Es un empate." << std::endl;
    }
}

int main() {
    char respuesta;
    do {
        jugarBlackjack();
        std::cout << "�Quieres jugar de nuevo? (s/n): ";
        std::cin >> respuesta;
    } while (respuesta == 's');

    return 0;
}