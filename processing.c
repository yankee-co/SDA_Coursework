#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>

#include "processing.h"
#include "common.h"
#include "algorithms.h"

clock_t * QuickSortMeasurement_Arr1D(int P, clock_t * Res, int type, int add, int * Vector)
{
    clock_t time_start, time_stop;
    for (int i=0; i < MEASUREMENTS; i++)
    {
        FillVector(P, Vector, type, add);
        time_start = clock();
        QuickSort_Arr1D(0, P - 1, Vector);
        time_stop = clock();
        Res[i] = time_stop - time_start;
    }
    
    return Res;
}

clock_t * QuickSortMeasurement(int P, int M, int N, int *** Arr3D, clock_t * Res, int type){ // Функція для виміру часу витраченого на сортування алгоритмом №24 QuickSort

    int L = 0;
    int R = P - 1;
    // int * SliceSum = (int *) malloc(sizeof(int) * P);
    int SliceSum[P];
    clock_t time_start, time_stop;

    for (int i = 0; i < MEASUREMENTS; i++){

        fill_matrix(P, M, N, Arr3D, type, 0);

        time_start = clock();

        for (int i = 0; i < P; i++) {
            for (int j = 0; j < M; j++) {
                for (int k = 0; k < N; k++) {
                    SliceSum[i] += Arr3D[i][j][k];
                }
            }
        }   

        QuickSort(M, N, Arr3D, SliceSum, L, R);

        time_stop = clock();

        Res[i] = time_stop - time_start;
    }
    // free(SliceSum);
    return Res;
}

float MeasurementProcessing(clock_t * Res){ // Усереднення результатів вимірювання відкиданням перших та екстремальних значень

    long int Sum;
    float AverageValue;

    clock_t buf;
    int L = rejected_number, R = MEASUREMENTS - 1;
    int k = rejected_number;

    for (int j = 0; j < min_max_number; j++) {
        for (int i = L; i < R; i++) {
            if (Res[i] > Res[i + 1]) {
                buf = Res[i];
                Res[i] = Res[i + 1];
                Res[i + 1] = buf;
                k = i;     
            }
        }

        R = k;

        for (int i = R - 1; i >= L; i--) {
            if (Res[i] > Res[i + 1]) {
                buf = Res[i];
                Res[i] = Res[i + 1];
                Res[i + 1] = buf;
                k = i;
            }
        }

        L = k + 1;
    }

    Sum = 0;

    for (int i = rejected_number + min_max_number; i < MEASUREMENTS - min_max_number; i++)
        Sum = Sum + Res[i];

    AverageValue = (float) Sum / (float) (MEASUREMENTS - 2 * min_max_number - rejected_number);

    return AverageValue;
}

// Функція що виділяє память для тривимірного масиву
// int add - зсув для сортування Insert3 

int *** define_matrix(int P, int M, int N, int add){ // Функція для виділення пам'яті під тривимірний масив
    int *** Arr3D = (int ***) malloc((P + add) * sizeof(int **));
    for (int k = 0; k < P + add; k++){
        Arr3D[k] = (int **) malloc(M * sizeof(int *));
        for (int i = 0; i < M; i++)
            Arr3D[k][i] = (int *) malloc(N * sizeof(int));
    }

    return Arr3D;
}

// Функція що звільняє память виділену раніше для тривимірного масиву
// int add - зсув для сортування Insert3 

void free_memory(int P, int M, int N, int *** Arr3D, int add){ // Функція для звілення пам'яті виділеної під тривимірний масив
    for (int k = 0; k < P + add; k++){
        for (int i = 0; i < M; i++)
            free(Arr3D[k][i]);
        free(Arr3D[k]);
    }
    free(Arr3D);
}

// Функція яка заповнює матрицю числами.
// int type - визначає впорядкованість
// int add - зсув для сортування Insert3 

void fill_matrix(int P, int M, int N, int *** Arr3D, int type, int add){ // Функція для заповнення матриці в залежності від обраного типу (впорядкована, невпорядкована, обернено впорядкована)

    int counter;

    if (type == 1){
        counter = 1 - add;
        for (int p = 0; p < P + add; p++){
            for (int m = 0; m < M; m++){
                for (int n = 0; n < N; n++){
                    Arr3D[p][m][n] = counter;
                    counter++;
                }
            }
        }
    }

    else if (type == 2){
        int upper = 100;
        int lower = 0;
        for (int p = 0; p < P + add; p++){
            for (int m = 0; m < M; m++){
                for (int n = 0; n < N; n++){
                    Arr3D[p][m][n] = rand() % (P*M*N);
                }
            }
        }
    }

    else{
        counter = P * M * N + add;
        for (int p = 0; p < P; p++){
            for (int m = 0; m < M; m++){
                for (int n = 0; n < N; n++){
                    Arr3D[p][m][n] = counter;
                    counter--;
                }
            }
        }
    }
}

// Функція що створює і повертає одновимірний масив

int * CreateVector(int P, int add){
    int * Vector = (int *) malloc(sizeof(int) * (P + add));
    return Vector;
}

// Функція для заповнення одновимірного масива числами

void FillVector(int P, int * Vector, int type, int add){
    // int Vector[P+add];

    // Заповнення
    switch (type)
    {
    case 1:
        for (int p = 0; p < P + add; p++){
            Vector[p] = p - 1;
        }
        break;
    case 2:
        for (int p = 0; p < P + add; p++){
            Vector[p] == rand() % P;
        }
        break;
    case 3:
        for (int p = (P + add); p > 0; p--){
            Vector[p] = p;
        }
        break;
    default:
        break;
    }

}