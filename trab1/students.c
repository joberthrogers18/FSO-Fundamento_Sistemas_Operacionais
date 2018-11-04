#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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
    int numberStudents;
    srand(time(NULL));

    numberStudents =  number_students();

    pthread_t thread_students_id[numberStudents];

    for(int i = 0; i < numberStudents; i++)
        pthread_create(&thread_students_id[i], NULL, hello, NULL);

    for(int i = 0 ; i < numberStudents; i++)
        pthread_join(thread_students_id[i], NULL);


    return 0;
}