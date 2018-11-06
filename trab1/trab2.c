#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#define NUM_ESTUDANTES 7

int *fila;
int numero_fila = 0;
int ultimo = 0;
int a_termino =0;

pthread_mutex_t m_fila;
pthread_mutex_t m_aTerminados;
sem_t s_alunos[7];
sem_t s_assistente;
int atual = 0;

void* ativaidadeAlunos (void* arg){

  int tempo_estudo_comeco = rand() % 6;
  int na_fila = 0;
  sleep(tempo_estudo_comeco);

  int id_aluno = *(int*)arg;
  printf("Passou %d\n", id_aluno);

    pthread_mutex_lock(&m_fila);
    atual++;
    pthread_mutex_unlock(&m_fila);

    printf("atual: %d\n", atual);
    if(id_aluno < 5){

          //sem_post(&s_alunos[id_aluno - 1]);
        sem_wait(&s_alunos[id_aluno]);

    }
    else{
      //sem_post(&s_alunos[id_aluno - 1]);
      printf("É não deu\n");
    }





/*
  if(ultimo < numero_fila){
    pthread_mutex_lock(&m_fila);
        if(fila[ultimo] == -1)
          fila[ultimo] = id_aluno;

        ultimo++;

        na_fila = 1;

        printf("Aluno %d entrou\n", id_aluno);

    pthread_mutex_unlock(&m_fila);
  }
  else{
    tempo_estudo_comeco = rand() % 6;

    sleep(tempo_estudo_comeco);
    printf("Aluno %d não entrou na fila\n", id_aluno);
  }

  printf("Entrou? %d\n", na_fila);*/
  /*for(int i = 0; i < NUM_ESTUDANTES; i++){
    if(fila[i] == -1)

  }*/

  pthread_exit(NULL);
}

void* atividadeAssistente (void* args){

  int aux = 0;
  int cont = 0;
  int dormindo = 0; // não esta dormindo

  sleep(5);

  while(1){//a_termino != 0){
    /*if(fila[ultimo] == -1){
      printf("Monitor dormindo\n");
      sem_wait(&s_assistente);
    }
    else {
      if(dormindo){
        printf("Monitor Acordou\n", );
        sem_post(&s_assistente);
      }
    }*/

    aux = fila[cont];


    sem_post(&s_alunos[cont]);
    printf("Assistente atendendo aluno %d\n", cont);
    cont++;
    sleep(3);

    if(cont == 5){
      break;
    }
  }
  //  aux = fila[cont];
    //printf("Assistente atendendo aluno %d\n", aux);
  //}
}

int zerar_fila(){
  for(int i = 0; i < NUM_ESTUDANTES; i++) // definindo como -1
    fila[i] = -1;
}

int main(){

  srand(time(NULL));

  pthread_mutex_init(&m_fila, NULL);
  pthread_mutex_init(&m_aTerminados, NULL);

  sem_init(&s_assistente,0,0);

  for(int i = 0; i < 7; i++){
    sem_init(&s_alunos[i], 0 ,0);
  }

  pthread_t threads_alunos[NUM_ESTUDANTES];
  pthread_t thread_assistente;
  int id_alunos[7];

  a_termino = 7; // numero de treads que serão alocadas

  fila = (int*)malloc(5*sizeof(int));

  numero_fila = 5;

  zerar_fila();

  pthread_create(&thread_assistente, NULL, atividadeAssistente,NULL);

  for(int i = 0; i < NUM_ESTUDANTES; i++){
    id_alunos[i] = i;
    pthread_create(&threads_alunos[i], NULL, ativaidadeAlunos,&(id_alunos[i]));
  }

  /*for(int i = 0; i < 2; i++)
    printf("%d ", fila[i]);*/

  for(int i = 0; i < NUM_ESTUDANTES; i++){
      pthread_join(threads_alunos[i], NULL);

      pthread_mutex_lock(&m_aTerminados);
        a_termino--;  // decrementa os estudantes que forem acabando
      pthread_mutex_unlock(&m_aTerminados);
  }

    for(int i = 0; i < 5; i++)
      printf("%d ", fila[i]);

  pthread_mutex_destroy(&m_fila);
  pthread_mutex_destroy(&m_aTerminados);

  free(fila);

  return 0;
}
