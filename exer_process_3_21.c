#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>

int main(){

    pid_t pid;

    int variable = 0;
    scanf("%d",&variable);

    pid = fork();

    if(pid == 0){

        printf("%d ", variable);

        while(variable != 1){
            if(variable%2 == 0)
                variable /= 2;
            else
                variable = variable * 3 + 1;
            printf("%d ", variable);
        }
    }
    else if(pid > 0){
        wait(NULL);
        printf("\nchegou");
    }

    return 0;
}