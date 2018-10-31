#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int m[9][9];

void verifica_linha(){
    int** m_aux;
    int verification = 1;

    m_aux = (int**)calloc(9,sizeof(int*));
    for(int i = 0; i < 9; i ++ )
        m_aux[i] =(int*)calloc(9,sizeof(int));

    int aux = 0;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            aux = m[i][j];
            m_aux[i][aux - 1] += 1; 
        }
    }

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(m_aux[i][j] != 1){
                verification = 0;
                break;
            } 
        }
    }

    for(int i = 0; i < 9; i++ ){
        for(int j = 0; j < 9; j++){
            printf("%d ", m_aux[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < 9; i++)
        free(m_aux[i]);

    free(m_aux);

    if(verification == 1){
        printf("sim");
    }
    else{
        printf("Não");
    }

}

void verifica_colunas(){
    int** m_aux;
    int verification = 1;

    m_aux = (int**)calloc(9,sizeof(int*));
    for(int i = 0; i < 9; i ++ )
        m_aux[i] =(int*)calloc(9,sizeof(int));

    int aux = 0;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            aux = m[j][i];
            m_aux[j][aux - 1] += 1; 
        }
    }

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(m_aux[i][j] != 1){
                verification = 0;
                break;
            } 
        }
    }

    for(int i = 0; i < 9; i++ ){
        for(int j = 0; j < 9; j++){
            printf("%d ", m_aux[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < 9; i++)
        free(m_aux[i]);

    free(m_aux);

    if(verification == 1){
        printf("sim");
    }
    else{
        printf("Não");
    }

}

void verify_submatrix(int range){

    int* m_aux;
    int aux;
    int verification = 1;
    int start_row;
    int finish_row;
    int start_col;
    int finish_col;

    if(range == 1){
        start_row = 0;
        finish_row = 3;
        start_col = 0;
        finish_col = 3;
    }
    else if(range == 2){
        start_row = 0;
        finish_row = 3;
        start_col = 3;
        finish_col = 6;
    }
    else if(range == 3){
        start_row = 0;
        finish_row = 3;
        start_col = 6;
        finish_col = 9;
    }
    else if(range == 4){
        start_row = 3;
        finish_row = 6;
        start_col = 0;
        finish_col = 3;
    }
    else if(range == 5){
        start_row = 3;
        finish_row = 6;
        start_col = 3;
        finish_col = 6;
    }
    else if(range == 6){
        start_row = 3;
        finish_row = 6;
        start_col = 6;
        finish_col = 9;
    }
    else if(range == 7){
        start_row = 6;
        finish_row = 9;
        start_col = 0;
        finish_col = 3;
    }
    else if(range == 8){
        start_row = 6;
        finish_row = 9;
        start_col = 3;
        finish_col = 6;
    }
    else if(range == 9){
        start_row = 6;
        finish_row = 9;
        start_col = 6;
        finish_col = 9;
    }
    
    m_aux =(int*)calloc(9,sizeof(int));

    for(int i = start_row; i < finish_row; i++){
        for(int j = start_col; j < finish_col; j++){
            aux = m[i][j];
            m_aux[aux - 1]++;
        }
    }

    for(int i = 0; i < 9; i++){
        if(m_aux[i] != 1){
            verification = 0;
            break;
        } 

        printf("%d ", m_aux[i]);
    }

    /*for(int i = 0; i < 9; i++){
        printf("");
    }*/

    free(m_aux);

    if(verification == 1){
        printf("sim");
    }
    else{
        printf("Não");
    }
}

int main(){

    FILE *file;
    
    char url[]="1.txt";

    file = fopen(url,"r");

    if(file == NULL){
        printf("Problema ao abrir o arquivo");
        return 0;
    }

    int number_file;

   /* printf("Escolha um arquivo entre 1 a 10\n");
    scanf("%d", &number_file);

    while(number_file < 0 || number_file > 10){
        printf("Entrada invalida!Digite novamente.\n");
        scanf("%d", &number_file);
    }*/

    int i = 0;
    

    while(!feof(file)){
        fscanf(file,"%d %d %d %d %d %d %d %d %d\n", &m[i][0],&m[i][1], &m[i][2], &m[i][3], &m[i][4], &m[i][5], &m[i][6],&m[i][7], &m[i][8]);
        i++;
    }

    for(int i = 0; i < 9; i++ ){
        for(int j = 0; j < 9; j++){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }

    verifica_linha();
    verifica_colunas();
    verify_submatrix(1);

    fclose(file);

    return 0;
}