#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define THREAD_COUNT 5

// Declaration of thread condition variable 
pthread_cond_t cond1[THREAD_COUNT] = PTHREAD_COND_INITIALIZER;

pthread_mutex_t vet_mutex[THREAD_COUNT];
pthread_mutex_t block;
int cont = 0;

void* func_thread(void* args){

    int aux = cont;

    //printf("thread\n");

    pthread_mutex_lock(&vet_mutex[aux]);

    //printf("%d", cont);

    if (cont < 4) { 
        //printf("Waiting on condition variable cond1\n"); 
        cont++;
        //printf("%d\n",cont);
        pthread_cond_wait(&cond1[aux], &vet_mutex[aux]); 
    } 
    else { 
        // Let's signal condition variable cond1 
        //printf("Signaling condition variable cond1\n");
        cont++;
        pthread_cond_signal(&cond1[0]);
        pthread_cond_signal(&cond1[1]);
        pthread_cond_signal(&cond1[2]);
        pthread_cond_signal(&cond1[3]);
        pthread_cond_signal(&cond1[4]);
        //printf("Liberei\n");

    } 

    pthread_mutex_unlock(&vet_mutex[aux]);

    printf("Saiu\n");
    pthread_exit(0);
}

int main(){

    pthread_t threads_id[THREAD_COUNT];

    for(int i = 0; i < THREAD_COUNT; i++){
        pthread_mutex_init(&vet_mutex[i], NULL);
        cont = 0;
    }

    pthread_mutex_init(&block, NULL);

    int aux;

    for(int i = 0; i < THREAD_COUNT; i++){
        aux = i;
        printf("Thread criada\n");
        pthread_create(&threads_id[i], NULL, func_thread,&aux);
    }

    for(int i = 0; i < THREAD_COUNT; i++){
        //printf("Thread Executando");
        pthread_join(threads_id[i], NULL);
    }

    pthread_mutex_destroy(&block);

    for(int i = 0; i < THREAD_COUNT; i++)
        pthread_mutex_destroy(&vet_mutex[i]);

    printf("%d\n", cont);

    return 0;
}

