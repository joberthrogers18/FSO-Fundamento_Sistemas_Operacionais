#include <stdio.h>
#include <pthread.h>

void *print_prime_numbers(void *argumentos){
  int number = *(int *)argumentos;
  int i, j ,times = 0;
  for(i=0; i < number; i++){
    times = 0;
    for(j= i; j > 0; j--){
      if(i % j == 0 ){
        times += 1;
      }
    }
    if(times <= 2 ){
      printf("%d ", i);
    }
  }

  pthread_exit(NULL);
}

int main(){

  pthread_t thread_id;
  int flag, status;

  int number = 0;

  printf("Entre com um numero: ");
  scanf("%d", &number);

  flag = pthread_create(&thread_id, NULL, print_prime_numbers, &number);
  if(flag != 0) printf("Erro na criação da nova thread");

  status = pthread_join(thread_id, NULL);

  return 0;
}
