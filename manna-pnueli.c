#include "manna-pnueli.h"

int main(int argc, char **argv) {
    pthread_t clients[NUM_THREADS];

    long i;
    for(i = 0; i < NUM_THREADS; i++) {
        if(pthread_create(&clients[i], NULL, Client, (void*)i) != 0) {
            printf("Error: Wasn't possible create client thread.\n");
            return -1;
        }
    }

    for(i = 0; i < NUM_THREADS; i++) {
        pthread_join(clients[i], NULL);
    }

    return 0;
}

void CriticalSection() {
    int local = soma;
    sleep((rand() % 2) / 1000);
    soma = local + 1;
}

void *Client(void *arg) {
    long i = (long)arg;
    while(true) {
        //critical section
        CriticalSection();
        if(soma > MAX_SUM) break;
        printf("Sum: %ld | Thread: %ld\n", soma, i);
    }

    pthread_exit(NULL);
}
