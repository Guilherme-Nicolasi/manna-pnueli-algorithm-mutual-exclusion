#ifndef PNUELI_H_INCLUDED
#define PNUELI_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_SUM 100000
#define NUM_THREADS 4

long soma = 0;
int request = 0, respond = 0;
int count_threads = 0;

void CriticalSection();
void *Client(void *arg);
void *Server(void *arg);

#endif // PNUELI_H_INCLUDED
