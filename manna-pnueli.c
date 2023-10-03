#include "manna-pnueli.h"

int main(int argc, char **argv) {
    pthread_t clients[NUM_THREADS], server;
    if(pthread_create(&server, NULL, Server, NULL) != 0) {
        printf("Error: Wasn't possible create server thread.\n");
        return -1;
    }

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

    pthread_join(server, NULL);

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
        //non-critical section
        while(respond != i) {
            request = i;
        }
        //critical section
        CriticalSection();
        if(soma > MAX_SUM) break;
        printf("Sum: %ld | Thread: %ld\n", soma, i);

        respond = 0;
    }

    count_threads++;
    pthread_exit(NULL);
}

void *Server(void *arg) {
    while(true) {
        while(request == 0);
        respond = request;
        while(respond != 0);
        request = 0;
        if(count_threads == NUM_THREADS) break;
    }
    pthread_exit(NULL);
}
