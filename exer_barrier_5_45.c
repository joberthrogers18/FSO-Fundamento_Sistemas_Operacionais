#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define THREAD_COUNT 6

pthread_barrier_t barrier;

void* barrier_point(void *id_ptr) {
  int thread_id = *(int*)id_ptr;
  int wait_second = 1 + rand() % 5;
  printf("Thread %d: entra em espera de %d segundos\n", thread_id, wait_second);
  sleep(wait_second);
  printf("thread %d: Está pronta\n", thread_id);

  pthread_barrier_wait(&barrier);

  printf("thread %d: executando!\n", thread_id);
  return NULL;
}

int main() {
  int i;
  pthread_t ids[THREAD_COUNT];

  srand(time(NULL));
  pthread_barrier_init(&barrier, NULL, THREAD_COUNT + 1);

  for (i=0; i < THREAD_COUNT; i++)
    pthread_create(&ids[i], NULL, barrier_point, &i);

  printf("main() está pronta.\n");

  pthread_barrier_wait(&barrier);

  printf("main() está executando!\n");

  for (i=0; i < THREAD_COUNT; i++) 
    pthread_join(ids[i], NULL);
  
  pthread_barrier_destroy(&barrier);

  return 0;
}