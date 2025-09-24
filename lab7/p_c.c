#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define bsize 5
int buffer[bsize];
int in = 0, out = 0;

sem_t empty, full, mutex;

void *producer() {
    int item;
    while (1) {
        item = rand() % 100;
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        printf("Producer: item %d inserted at index %d\n", item, in);
        in = (in + 1) % bsize;

        sem_post(&mutex);
        sem_post(&full);

        sleep(rand() % 2);
    }
}

void *consumer() {
    int item;
    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);

        item = buffer[out];
        printf("Consumer: item %d removed from index %d\n", item, out);
        out = (out + 1) % bsize;

        sem_post(&mutex);
        sem_post(&empty);

        sleep(rand() % 3);
    }
}

int main() {
    pthread_t prod, cons;

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, bsize);
    sem_init(&full, 0, 0);

    
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

   
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
