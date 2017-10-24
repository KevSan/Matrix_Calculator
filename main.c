#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define ROW  5
#define COL  5
int matrixA[ROW][COL];
int matrixB[ROW][COL];

void matrixMaker(int matrix[ROW][COL]);//fills a matrix with random values
void matrixPrinter(int matrix[ROW][COL]);//prints the matrix

struct tuple{
    int currRow;
    int currCol;
};//struct used to pass in pthread_create()

void *vectorMultiplication(void *pair);//multiplies vectors

int main(){

    matrixMaker(matrixA);
    sleep(1);//small pause to ensure srand returns different random numbers for
    //each matrix
    matrixMaker(matrixB);

    printf("Matrix A = \n");
    matrixPrinter(matrixA);
    printf("\n");

    printf("Matrix B = \n");
    matrixPrinter(matrixB);
    printf("\n");

    int numOfThreads = ROW * COL, err;//create a thread for each index of product
    pthread_t* threads;
    threads = (pthread_t*) malloc(numOfThreads * sizeof(pthread_t));
    printf("\n");

    printf("A * B = \n");
    //iterates through each cell of the product, creates a thread, and calls
    //the vectorMultiplication() function while filling the pair struct with
    //the necessary parameters needed for the function
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            struct tuple *pair = malloc (sizeof (struct tuple));
            pair->currRow = i;
            pair->currCol = j;
            err = pthread_create(&threads[i], NULL, vectorMultiplication, pair);
            if(err != 0)
                printf("wtf?\n");
            pthread_join(threads[i], NULL);
        }
        printf("\n");
    }

    return 0;
}

void matrixMaker(int matrix[ROW][COL]){

    srand(time(NULL));
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            matrix[i][j] = rand() % 9;
        }
    }
}

void matrixPrinter(int matrix[ROW][COL]){

    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void *vectorMultiplication(void* pair){

    struct tuple *currVec = (struct tuple*)pair;
    int indexVal = 0;
    //each matrix is a square, so the vectors are the length of a ROW
    //this iterates through the current row of matrix A and column of matrix B
    //while multiplying each entry and adding it to the indexVal variable
    for(int i = 0; i < ROW; i++){
        indexVal += matrixA[currVec->currRow][i] * matrixB[i][currVec->currCol];
    }
    printf("%d ", indexVal);

    pthread_exit(0);
}

void *vectorDivision(void * pair){

    struct tuple *currVec = (struct tuple*)pair;
    int indexVal = 0;
    //each matrix is a square, so the vectors are the length of a ROW
    //this iterates through the current row of matrix A and column of matrix B
    //while multiplying each entry and adding it to the indexVal variable
    for(int i = 0; i < ROW; i++){
        indexVal += matrixA[currVec->currRow][i] / matrixB[i][currVec->currCol];
    }
    printf("%d ", indexVal);

    pthread_exit(0);
}

void *vectorAddition(void * pair){

    struct tuple *currVec = (struct tuple*)pair;
    int indexVal = 0;
    //each matrix is a square, so the vectors are the length of a ROW
    //this iterates through the current row of matrix A and column of matrix B
    //while multiplying each entry and adding it to the indexVal variable
    for(int i = 0; i < ROW; i++){
        indexVal += matrixA[currVec->currRow][i] + matrixB[i][currVec->currCol];
    }
    printf("%d ", indexVal);

    pthread_exit(0);
}

void *vectorSubtraction(void * pair){

    struct tuple *currVec = (struct tuple*)pair;
    int indexVal = 0;
    //each matrix is a square, so the vectors are the length of a ROW
    //this iterates through the current row of matrix A and column of matrix B
    //while multiplying each entry and adding it to the indexVal variable
    for(int i = 0; i < ROW; i++){
        indexVal += matrixA[currVec->currRow][i] - matrixB[i][currVec->currCol];
    }
    printf("%d ", indexVal);

    pthread_exit(0);
}