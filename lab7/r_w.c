#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t wrt, mutex;
int rc = 0;        // number of active readers
int data = 1;      // shared data

void* writer(void* arg) {
    long id = (long)arg;
    while (1) {
        sem_wait(&wrt);   // wait until no reader/writer in critical section

        data = rand() % 100;  
        printf("Writer %ld wrote %d\n", id, data);

        sem_post(&wrt);   // release critical section
        sleep(1);
    }
}

void* reader(void* arg) {
    long id = (long)arg;
    while (1) {
        sem_wait(&mutex);
        rc++;
        if (rc == 1) sem_wait(&wrt);  // first reader locks writers
        sem_post(&mutex);

        // critical section (reading)
        printf("Reader %ld read %d\n", id, data);

        sem_wait(&mutex);
        rc--;
        if (rc == 0) sem_post(&wrt);  // last reader unlocks writers
        sem_post(&mutex);

        sleep(1);
    }
}

int main() {
    int r, w;
    printf("Enter number of readers: ");
    scanf("%d", &r);
    printf("Enter number of writers: ");
    scanf("%d", &w);

    pthread_t R[r], W[w];
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (long i = 0; i < r; i++)
        pthread_create(&R[i], NULL, reader, (void*)i);
    for (long i = 0; i < w; i++)
        pthread_create(&W[i], NULL, writer, (void*)i);

    sleep(20);  // run simulation for 20 seconds
    printf("\nSimulation over.\n");

    return 0;
}
