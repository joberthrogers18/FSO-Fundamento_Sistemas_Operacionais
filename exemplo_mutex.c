#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
 
/* Protótipo de Funções */
void *threadFunction(void *p);
 
/* Variáveis Globais */
int counter;
pthread_mutex_t lock; // iniciando mutex de forma estatica.

int main(){
 pthread_t thread_id[5];
 int i, ret;
 
 	// Zera contador
 	counter = 0;

    //iniciando mutex
    if(pthread_mutex_init(&lock,NULL) != 0){
        fprintf(stderr,"Erro ao criar o mutex!");
        exit(EXIT_FAILURE);
    }
 
	// Cria cinco threads que executarão a mesma função
	for(i=0; i<5; ++i){
		ret = pthread_create(&thread_id[i], NULL, threadFunction, NULL);
		if(ret != 0){
			fprintf(stderr, "Erro thread %d. Código %d: %s\n", (i+1), ret, strerror(ret));
			exit(EXIT_FAILURE);
		}
	}
	// Aguarda o fim das threads
	for(i=0; i<5; ++i)
		pthread_join(thread_id[i], NULL);

    //Destruindo o mutex
    pthread_mutex_destroy(&lock);
 
	return 0;
}
 
void *threadFunction(void *p){
 unsigned long i = 0;

    //Travar mutex
    pthread_mutex_lock(&lock);
 
 	// Incrementa contador global
	counter++;
 
	printf("Trabalho %d iniciado.\n", counter);
	
	// Faz uma contagem representando um trabalho qualquer
	for(i=0; i<0xFFFFFFF; ++i);
	
	printf("Trabalho %d finalizado.\n", counter);

    pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}