#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define AUTOS 8
#define PLAZAS 3

sem_t plazas;

void* auto_hilo(void* arg) {
    int id = *(int*)arg;

    sem_wait(&plazas);
    printf("Auto %d estacionado\n", id);
    sleep(2);
    printf("Auto %d saliendo\n", id);
    sem_post(&plazas);

    return NULL;
}

int main() {
    pthread_t hilos[AUTOS];
    int ids[AUTOS];

    sem_init(&plazas, 0, PLAZAS);

    for (int i = 0; i < AUTOS; i++) {
        ids[i] = i + 1;
        pthread_create(&hilos[i], NULL, auto_hilo, &ids[i]);
    }

    for (int i = 0; i < AUTOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    sem_destroy(&plazas);
    return 0;
}
