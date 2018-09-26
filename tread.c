#include <stdio.h>
#include <pthread.h>

void *primos(void *argumentos){
  int id = *(int *)argumentos;
  
  pthread_exit(NULL);
}

int main(){

  pthread_t thread_id;
  int flag, status;

  int number = 0;

  printf("Entre com um numero: ");
  scanf("%d", &number);

  flag = pthread_create(&thread_id, NULL, primos, &number);
  if(flag != 0) printf("Erro na criação da nova thread");

  status = pthread_join(thread_id, NULL);

  return 0;
}
