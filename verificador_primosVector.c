/*
Segunda implementación
Bayron Jojoa Rosero - 2242917
Miguel Angel Muñoz Piñeros - 2274590
Alejandro Muñoz Guerrero - 2242951
Heidy Lizbeth Gelpud Acosta - 2242550
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int valores[3];

// Estructura para mantener el rango para cada hilo
typedef struct {
    int inicio;
    int fin;
    int id;
} Rango;

// Función para verificar si un número es primo
int es_primo(int num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}

// Función del hilo para verificar números primos en un rango dado
void* verificar_primo(void* arg) {
    int counter = 0;
    Rango* rango = (Rango*)arg;
    for (int i = rango->inicio; i <= rango->fin; i++) {

    int total_primos = 0;

	if (es_primo(i)) {
        printf("Hilo %d: %d es primo\n", rango->id, i); 
	    counter++; 
	}

    // Cada id representa una posición en el vector, se asigna entonces a cada posición el respectivo conteo 
    valores[rango->id] = counter;
    
    }
    return NULL;
}

int main() {
    int inicio = 1, fin = 100;
    int num_hilos = 4;
    pthread_t hilos[num_hilos];
    Rango rangos[num_hilos];

    // Dividir el rango en partes para cada hilo
    int tamano_rango = (fin - inicio + 1) / num_hilos;
    for (int i = 0; i < num_hilos; i++) {
        rangos[i].inicio = inicio + i * tamano_rango;
        rangos[i].fin = (i == num_hilos - 1) ? fin : (inicio + (i + 1) * tamano_rango - 1);
	    rangos[i].id = i;
	}

    // Crear hilos
    for (int i = 0; i < num_hilos; i++) {
        if (pthread_create(&hilos[i], NULL, verificar_primo, &rangos[i]) != 0) {
            perror("Error al crear el hilo");
            return 1;
        }
    }

    // Unir hilos
    for (int i = 0; i < num_hilos; i++) {
        pthread_join(hilos[i], NULL);
    }
    //printf("El total de primos encontrados es %d\n", total_primos);

    int a = valores[0];
    int b = valores[1];
    int c = valores[2];
    int d = valores[3];

    int result = a + b + c + d;

    printf("El total de primos es: %i\n", result);

    return 0;
}