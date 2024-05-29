/*
Tercera implementación
Bayron Jojoa Rosero - 2242917
Miguel Angel Muñoz Piñeros - 2274590
Alejandro Muñoz Guerrero - 2242951
Heidy Lizbeth Gelpud Acosta - 2242550
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

// Estructura para mantener el rango para cada hilo
typedef struct {
    int inicio;
    int fin;
    int id;
    int encontrados;
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
    Rango* rango = (Rango*)arg;
    for (int i = rango->inicio; i <= rango->fin; i++) {
        if (es_primo(i)) {
            rango->encontrados+=1;            
        }
    }
    printf("El numero de primos encontrados por el hilo %d, es: %d \n",rango->id+1, rango->encontrados);
    return NULL;
}

int main() {
    int primos_totales = 0;
    int inicio = 1, fin = 100;
    int num_hilos = 4;
    pthread_t hilos[num_hilos];
    Rango rangos[num_hilos];

    // Dividir el rango en partes para cada hilo
    int tamano_rango = (fin - inicio + 1) / num_hilos;
    for (int i = 0; i < num_hilos; i++) {
        rangos[i].encontrados = 0;
        rangos[i].inicio = inicio + i * tamano_rango;
        rangos[i].id = i;
        rangos[i].fin = (i == num_hilos - 1) ? fin : (inicio + (i + 1) * tamano_rango - 1);
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
        primos_totales += rangos[i].encontrados; 
    }
    printf("El total de primos encontrados es %d\n",primos_totales);    

    return 0;
}
