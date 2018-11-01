#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int m[9][9];

void* verify_row(void* args){
    int** m_aux;
    int *verification;

    verification = (int*)malloc(sizeof(int));
    *verification = 1; 

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
                *verification = 0;
                break;
            } 
        }
    }

    for(int i = 0; i < 9; i++)
        free(m_aux[i]);

    free(m_aux);
    pthread_exit(verification);

}

void* verify_col(void* args){
    int** m_aux;
    int *verification;

    verification = (int*)malloc(sizeof(int));
    *verification = 1;

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
                *verification = 0;
                break;
            } 
        }
    }

    for(int i = 0; i < 9; i++)
        free(m_aux[i]);

    free(m_aux);
    pthread_exit(verification);

}

void* verify_submatrix(void* args){

    int range; 
    
    range = *((int*)args);

    int *m_aux;
    int aux;
    int *verification;

    verification = (int*)malloc(sizeof(int));
    m_aux = (int*)calloc(9,sizeof(int));

    *verification = 1;
    int start_row = 0;
    int finish_row = 3;
    int start_col = 0;
    int finish_col = 3;

    if(range == 1){
        int start_row = 0;
        int finish_row = 3;
        int start_col = 0;
        int finish_col = 3;
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
    
    for(int i = start_row; i < finish_row; i++){
        for(int j = start_col; j < finish_col; j++){
            aux = m[i][j];
            m_aux[aux - 1]++;
        }
    }

    for(int i = 0; i < 9; i++){
        if(m_aux[i] != 1){
            *verification = 0;
            break;
        } 
    }

    pthread_exit(verification);
}

int main(){


    FILE *file;

    int return_vals[11]; 

    int *ret;
    int *ret2;

    char url[]="sudokus/10.txt";

    file = fopen(url,"r");

    for(int i = 0; i < 11; i++){
        return_vals[i] = 0;
    }

    if(file == NULL){
        printf("Problema ao abrir o arquivo");
        return 0;
    }

    for(int i = 0; i < 11; i++){
        printf("%d ", *(return_vals + i));
    }

    int number_file;

    int i = 0;
    pthread_t t_col;
    pthread_t t_row;
    pthread_t t_submatrix[9];

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

    pthread_create(&t_row, NULL, verify_col, NULL);
    pthread_create(&t_col, NULL, verify_row, NULL);
    
    int aux = 1;

    for(int i = 0; i < 9; i++){
        int *arg = malloc(sizeof(*arg));
        *arg = i + 1;
        pthread_create(&t_submatrix[i], NULL, verify_submatrix,arg);
    }

    pthread_join(t_row,(void**) &ret);
    return_vals[0] = *ret;
    pthread_join(t_col, (void**) &ret);
    return_vals[1] = *ret;
    
    for(int i = 0; i < 9; i++){
        pthread_join(t_submatrix[i],(void**) &ret);
        return_vals[i + 2] = *ret;
    }

    printf("\n");

    for(int i = 0; i < 11; i++){
        printf("%d ", return_vals[i]);
    }

  /*pthread_t thid;
  void *ret;

  if (pthread_create(&thid, NULL, thread, NULL) != 0) {
    perror("pthread_create() error");
    exit(1);
  }

  if (pthread_join(thid, &ret) != 0) {
    perror("pthread_create() error");
    exit(3);
  }

  printf("thread exited with '%d'\n", *(int*)ret);*/

    //verifica_linha();
    //verifica_colunas();
    //verify_submatrix(1);

    fclose(file);

    //free(return_vals);

    return 0;
}