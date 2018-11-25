#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_ADRESSES_LOGICAL 10000
#define MASKOFFSET 15
#define MASKPAGENUMBER 240

struct adress_logical{
    int number_page;
    int offset;
};

int adresses_logical_numbers[NUMBER_ADRESSES_LOGICAL];
struct adress_logical amountAl[NUMBER_ADRESSES_LOGICAL];

int read_adress(char* name_file){

    FILE* file;
    char c;
    int i = 0;

    file = fopen(name_file, "r");

    if(file == NULL){
        printf("O arquivo não pode ser aberto\n");
        return 1;
    }

    while (!feof(file))
    {
        fscanf(file, "%d ", &adresses_logical_numbers[i]);
        amountAl[i].number_page = adresses_logical_numbers[i] & MASKPAGENUMBER;
        amountAl[i].offset = adresses_logical_numbers[i] & MASKOFFSET;
        i++;
    }

    for(int i = 0; i < NUMBER_ADRESSES_LOGICAL; i++){
        printf("adreess %d %d\n", amountAl[i].number_page, amountAl[i].offset);
    }

    return 0;

}

int main(int argc, char *argv[])
{
    char *name_file;
    name_file = argv[1];

    read_adress(name_file);

    return 0;
}
