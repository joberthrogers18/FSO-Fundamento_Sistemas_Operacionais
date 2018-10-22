#include <stdio.h>
#include <pthread.h>
#include<stdlib.h>

double average;
int max_number = 0;
int min_number = 9999999;
int size;

void* average_list (void* args){
  int sum = 0;
  int *vector = (int*)args;

  for(int i = 0; i < size; i++)
    sum += *(vector + i);

  average = (double) sum / size;

  pthread_exit(NULL);
  
}

void* max_number_list (void* args){
  int *vector = (int*)args;

  for(int i = 0; i < size; i++){
    if(*(vector + i) < min_number)
      min_number = *(vector + i);
  }

  pthread_exit(NULL);
}

void* min_number_list (void* args){
  int *vector = (int*)args;

  for(int i = 0; i < size; i++){
    if(*(vector + i) > max_number)
      max_number = *(vector + i);
  }

  pthread_exit(NULL);
}

int main(void) {
  
  int cont = 0;
  int *vector;
  pthread_t thread_id[3];

  printf("Quantidade de numeros");
  scanf("%d", &size);

  vector = (int*) malloc(size*sizeof(int));

  printf("%d", size);

  for(int i = 0; i < size; i++)
    scanf("%d", vector + i);

  pthread_create(&thread_id[0], NULL, average_list, vector);
  pthread_create(&thread_id[1], NULL, max_number_list, vector);
  pthread_create(&thread_id[2], NULL, min_number_list, vector);

  pthread_join(thread_id[0],NULL);
  pthread_join(thread_id[1],NULL);
  pthread_join(thread_id[2],NULL);

  printf("A media dos numero eh: %.2lf \n O menor numero eh: %d \n O maior numero eh %d", average, min_number, max_number);

  return 0;
}