#include <stdio.h>
#include <stdlib.h>

int read_adress(){

    FILE* file;

    file = fopen("adress.txt", "read");

    char c;

    do{
        c = getc(file);    
        printf("%c" , c);    
    }while (c != EOF);

}

int main(int argc, char const *argv[])
{
    
    read_adress();

    return 0;
}
