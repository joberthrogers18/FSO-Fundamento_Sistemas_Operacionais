#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutexSem;
int signal = 0;
int *students_queue;
pthread_mutex_t lock;

void* thread (void* arg){
    int profession = *(int*)arg;
    //int students = rand() % 6;

    printf(" profession %d \n", profession);

    if(profession == 0){
        //wait
        int students = rand() % 6;

        sem_wait(&mutexSem);
        printf("Entrou\n");

        //sleep(students);


        //pthread_mutex_lock(&lock);
          signal -= 1;
        //pthread_mutex_unlock(&lock);

        printf("Saindo\n");
        sem_post(&mutexSem);
    }
    else if(profession == 1){
        while(1){
            if(signal == 0){
                printf("Saiu\n");
                break;
            }
        }

    }

    pthread_exit(NULL);
}

void* student (void* args){
    //printf("Eu sou um estudante\n");

    int time_study = 1 + rand() % 8;

    /*sleep(time_study);

    printf("tempo do estudande %d \n", time_study);

    //wait
    sem_wait(&mutexSem);
    printf("Entrou\n");

    sleep(1);

    printf("Saindo\n");
    sem_post(&mutexSem);
    */
    pthread_exit(NULL);
}

int number_students(){

    int students = 0;

    students = 3 + rand() % 37;
    //students = rand() % 3;

    return students;
}

int main(){

    pthread_mutex_init(&lock, NULL);
    sem_init(&mutexSem, 0, 1);

    int numberStudents;
    int number_chairs = 0;
    srand(time(NULL));

    numberStudents = 5;//number_students();

    printf("numero de estudantes %d\n", numberStudents);

    if(numberStudents%2 == 0)
        number_chairs =  numberStudents/2;
    else if (numberStudents%2 == 1)
        number_chairs = (numberStudents - 1)/ 2;

        printf("aux %d\n", number_chairs);

   students_queue = (int*) calloc(number_chairs,sizeof(int));

    /*for(int i = 0; i < number_chairs; i++)
        printf("%d ", students_queue[i]);*/

    pthread_t thread_students_id[numberStudents];
    pthread_t tAE_id;
    int aux = 1;
    int aux1 = 0;

    signal = numberStudents;

    pthread_create(&tAE_id, NULL, thread, &aux);

    //pthread_create(&thread_students_id[0], NULL, thread, &aux1);

    //aux = 0;

    for(int i = 0; i < numberStudents; i++)
        pthread_create(&thread_students_id[i], NULL, thread, &aux1);

    for(int i = 0 ; i < numberStudents; i++)
        pthread_join(thread_students_id[i], NULL);

   //pthread_join(thread_students_id[0], NULL);

   pthread_join(tAE_id, NULL);
/*
   sleep(2);

   pthread_create(&tAE_id2, NULL, thread, NULL);

   pthread_join(tAE_id, NULL);
   pthread_join(tAE_id2, NULL);


   sem_destroy(&mutexSem);
*/

   pthread_mutex_destroy(&lock);
   free(students_queue);

    return 0;
}
