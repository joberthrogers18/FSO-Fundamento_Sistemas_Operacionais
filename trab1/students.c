#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutexSem;

void* thread (void* arg){
    //wait
    sem_wait(&mutexSem);
    printf("Entrou\n");

    sleep(1);

    printf("Saindo\n");
    sem_post(&mutexSem);
}

void* hello (void* args){
    printf("Eu sou um estudante\n");

    pthread_exit(NULL);
}

int number_students(){

    int students = 0;

    students = 3 + rand() % 37;

    return students;
}

int main(){

    sem_init(&mutexSem, 0, 1);

    int numberStudents;
    srand(time(NULL));

    numberStudents =  number_students();

    pthread_t thread_students_id[numberStudents];
    pthread_t tAE_id;
    pthread_t tAE_id2;

    pthread_create(&tAE_id, NULL, thread, NULL);

    /*for(int i = 0; i < numberStudents; i++)
        pthread_create(&thread_students_id[i], NULL, hello, NULL);

    for(int i = 0 ; i < numberStudents; i++)
        pthread_join(thread_students_id[i], NULL);
    */

   sleep(2);

   pthread_create(&tAE_id2, NULL, thread, NULL);

   pthread_join(tAE_id, NULL);
   pthread_join(tAE_id2, NULL);


   sem_destroy(&mutexSem);

    return 0;
}