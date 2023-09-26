#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Clase para representar eventos temporales
class Evento {
public:
    Evento* PtrPasado;
    std::string EventoNombre;
    std::string Cientifico;
    int Datos;
    Evento* PtrFuturo;

    Evento(Evento* pasado, const std::string& nombre, const std::string& cientifico, int datos, Evento* futuro)
        : PtrPasado(pasado), EventoNombre(nombre), Cientifico(cientifico), Datos(datos), PtrFuturo(futuro) {}
};

// Función para generar un número aleatorio en el rango [min, max]
int generarNumeroAleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Función para verificar si un número es primo
bool esPrimo(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Función para verificar si dos números son coprimos
bool sonCoprimos(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a == 1;
}

int main() {
    srand(time(0)); // Inicializar la semilla para la generación de números aleatorios

    // Crear eventos temporales
    Evento* eventoA = new Evento(nullptr, "Evento A", "Einstein", generarNumeroAleatorio(1, 100), nullptr);
    Evento* eventoB = new Evento(nullptr, "Evento B", "Einstein", generarNumeroAleatorio(1, 100), nullptr);
    Evento* eventoC = new Evento(nullptr, "Evento C", (generarNumeroAleatorio(1, 2) == 1) ? "Einstein" : "Rosen", generarNumeroAleatorio(1, 100), nullptr);

    // Establecer relaciones de eventos basadas en las restricciones
    if (esPrimo(eventoA->Datos)) {
        eventoA->PtrFuturo = eventoB;
    }

    if (esPrimo(eventoB->Datos) && eventoA->PtrFuturo != nullptr) {
        eventoB->PtrPasado = eventoA;
        eventoB->PtrFuturo = eventoC;
    }

    if (eventoC->PtrFuturo != nullptr) {
        if (sonCoprimos(eventoA->Datos, eventoC->Datos)) {
            if (esPrimo(eventoC->Datos)) {
                // Científico 2 pudo entregar información a Einstein
                eventoC->Cientifico = "Einstein";
            }
        } else {
            // Singularidad sin intercambio de información
            eventoC->Cientifico = "Observador";
        }
    }

    // Imprimir la lista de eventos
    Evento* actual = eventoA;
    int nodoCount = 0;
    while (actual != nullptr) {
        std::cout << "Se ha producido un evento de Tipo " << actual->EventoNombre[actual->EventoNombre.size() - 1] << ": " << actual->Datos << std::endl;
        std::cout << "| " << actual->Datos << "| " << actual->Cientifico[0] << "| " << actual->EventoNombre[actual->EventoNombre.size() - 1] << "| ->" << std::endl;
        actual = actual->PtrFuturo;
        nodoCount++;
    }

    // Mostrar la cantidad de eventos tipo A y tipo B
    int countA = 0;
    int countB = 0;
    actual = eventoA;
    while (actual != nullptr) {
        if (actual->EventoNombre == "Evento A") {
            countA++;
        } else if (actual->EventoNombre == "Evento B") {
            countB++;
        }
        actual = actual->PtrFuturo;
    }

    std::cout << "Se ha encontrado un evento TA " << eventoA->Datos << " en el nodo : " << nodoCount << std::endl;

    // Detectar y mostrar singularidad
    actual = eventoA;
    bool singularidadDetectada = false;
    while (actual != nullptr) {
        if (actual->EventoNombre == "Evento C" && actual->Cientifico == "Observador") {
            singularidadDetectada = true;
            break;
        }
        actual = actual->PtrFuturo;
    }

    if (singularidadDetectada) {
        std::cout << "Se ha viajado en el tiempo y No se han compartido datos " << std::endl;
    } else {
        std::cout << "Se ha viajado en el tiempo y se han compartido datos " << std::endl;
    }

    // Imprimir el total de eventos
    std::cout << "Total de eventos: " << nodoCount << std::endl;

    // Liberar memoria
    delete eventoA;
    delete eventoB;
    delete eventoC;

    return 0;
}
