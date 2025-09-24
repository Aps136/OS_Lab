#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5   // number of philosophers

sem_t chopstick[N];   // one chopstick per philosopher

void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);

        // pick left chopstick
        sem_wait(&chopstick[id]);
        // pick right chopstick
        sem_wait(&chopstick[(id + 1) % N]);

        printf("Philosopher %d is eating...\n", id);
        sleep(2);

        // put down chopsticks
        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);

        printf("Philosopher %d finished eating...\n", id);
        sleep(1);
    }
}

int main() {
    pthread_t philo[N];
    int ids[N];

    // initialize semaphores (chopsticks)
    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);

    // create philosopher threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philo[i], NULL, philosopher, &ids[i]);
    }

    // wait for threads (they run infinitely here)
    for (int i = 0; i < N; i++)
        pthread_join(philo[i], NULL);

    return 0;
}
