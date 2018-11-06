#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#define NUM_ESTUDANTES 7

int *fila;
int ultimo = 0;

pthread_mutex_t m_fila;

void* alunos (void* arg){

  int tempo_estudo_comeco = rand() % 6;

  sleep(tempo_estudo_comeco);

  int id_aluno = *(int*)arg;
  printf("Passou %d\n", id_aluno);

  pthread_mutex_lock(&m_fila);
      if(fila[ultimo] == -1)
        fila[ultimo] = id_aluno;

      ultimo++;

  pthread_mutex_unlock(&m_fila);

  /*for(int i = 0; i < NUM_ESTUDANTES; i++){
    if(fila[i] == -1)

  }*/

  pthread_exit(NULL);
}

int zerar_fila(){
  for(int i = 0; i < NUM_ESTUDANTES; i++) // definindo como -1
    fila[i] = -1;
}

int main(){

  srand(time(NULL));

  pthread_mutex_init(&m_fila, NULL);
  pthread_t threads_alunos[NUM_ESTUDANTES];
  int aux[7];

  fila = (int*)malloc(5*sizeof(int));

  zerar_fila();

  for(int i = 0; i < NUM_ESTUDANTES; i++){
    aux[i] = i;
    pthread_create(&threads_alunos[i], NULL, alunos,&(aux[i]));
  }

  /*for(int i = 0; i < 2; i++)
    printf("%d ", fila[i]);*/

  for(int i = 0; i < NUM_ESTUDANTES; i++)
    pthread_join(threads_alunos[i], NULL);

    for(int i = 0; i < 5; i++)
      printf("%d ", fila[i]);

  pthread_mutex_destroy(&m_fila);

  free(fila);

  return 0;
}
