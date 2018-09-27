#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

 typedef struct{
  int array[100];
  int id_last;
}Vector;

void *fibonacci(void* arguments){
  Vector *args;
   args = (Vector*)arguments;

    args->array[args->id_last + 1] = args->array[args->id_last] + args->array[args->id_last -1];
    args->id_last += 1;

}

int main(int argc, char *argv[]){
    int number = 0;
    Vector args;

    printf("Entre com a quantidade de numeros: ");
    scanf("%d",&number);

    if(number < 0){
      printf("Esse número eh invalido\n");
      return 0;
    }
    else if(number == 1){
      printf("%d ",0);
      return 0;
    }
    else if(number > 1){
      pthread_t thread_id[number];
      args.array[0] = 0;
      args.array[1] = 1;
      args.id_last = 1;

      for(int i=0; i < number; i++)
        pthread_create(&(thread_id[i]), NULL, fibonacci, &(args));


      for(int i=0; i < number; i++)
        pthread_join(thread_id[i],NULL);

    }

    printf("Serie de fibonacci: ");

    for(int i=0; i<number;i++)
      printf("%d ", args.array[i]);


    return 0;
}
