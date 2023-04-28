#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>
#include "algorithms.h"
#include "common.h"

clock_t Insert3_Arr1D(int *Vector, int P)
{
    int j;
    clock_t time_start, time_stop;

    time_start = clock();

    for(int i = 2; i < P + 1; i++){
        Vector[0] = Vector[i];
        j = i;

        while (Vector[0] < Vector[j-1]) {
            Vector[j] = Vector[j - 1];
            j = j - 1;
            }
            Vector[j] = Vector[0];
    }
    time_stop = clock();

    return time_stop - time_start;
}

// Алгоритм №10 для сортування вектора
clock_t Select6_Arr1D(int *A, int N)
{
    int imin, tmp;
    clock_t time_start, time_stop;
    time_start = clock();
    for(int s=0; s<N-1; s++){
        imin=s;
        for(int i=s+1; i<N; i++)
            if (A[i]<A[imin]) imin=i;
        if (imin!=s) {
        tmp=A[imin];
        A[imin]=A[s];
        A[s]=tmp;
        }
    }
    time_stop = clock();
    return time_stop - time_start;
}

// Алгоритм сортування вставками №3 з пошуком справа від елементу що вставляється або з бар'єром змінений для паралельного переміщення перерізів 

clock_t Insert3(int P, int M, int N, int *** Arr3D){

    clock_t time_start, time_stop;

    // Масив для сум перерізів

    int * SliceSum = (int *) malloc(sizeof(int) * (P + 1));
    // int SliceSum[P + 1];
    int KeySlice[M][N];

    time_start = clock();

    // Заповнення масиву сумами перерізів
    for (int i = 1; i < P + 1; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                SliceSum[i] += Arr3D[i][j][k];
            }
        }
    }

    // Сортування
    for (int i = 1; i < P; i++) {
        int key = SliceSum[i];

        for (int m = 0; m < M; m++){
            for (int n = 0; n < N; n++){
                KeySlice[m][n] = Arr3D[i][m][n];
            }
        }

        int j = i - 1;
        while (j >= 0 && SliceSum[j] > key) {
            SliceSum[j + 1] = SliceSum[j];

            for (int m = 0; m < M; m++){
                for (int n = 0; n < N; n++){
                    Arr3D[j + 1][m][n] = Arr3D[j][m][n];
                }
            }

            j--;
        }
        SliceSum[j + 1] = key;

        for (int m = 0; m < M; m++){
            for (int n = 0; n < N; n++){
                Arr3D[j + 1][m][n] = KeySlice[m][n];
            }
        }

    }

    time_stop = clock();

    free(SliceSum);

    return time_stop - time_start;
}

clock_t Select6(int P, int M, int N, int *** Arr3D){ // Алгоритм сортування №10 масиву сум з паралельними змінами порядку розрізів головної матриці

    int imin, tmp;
    int temp_slice[M][N]; // матриця для тимчасового зберігання перерізу
    // int SliceSum[P];
    int * SliceSum = (int *) malloc(sizeof(int) * P); // Об'ява масиву сум, виділення пам'яті
    clock_t time_start, time_stop;
    
    time_start = clock();

    // Формування сум
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                SliceSum[i] += Arr3D[i][j][k];
            }
        }
    }

    // Сортування
    for(int s = 0; s < P - 1; s++){
        imin = s;
        for(int i = s + 1; i < P; i++)
            if (SliceSum[i] < SliceSum[imin]) imin = i;
            if (imin != s) {
                tmp = SliceSum[imin];
                SliceSum[imin] = SliceSum[s];
                SliceSum[s] = tmp;

                for (int s1 = 0; s1 < M; s1++){
                    for (int s2 = 0; s2 < N; s2++){
                        temp_slice[s1][s2] = Arr3D[imin][s1][s2];
                        }
                    }

                for (int s1 = 0; s1 < M; s1++){
                    for (int s2 = 0; s2 < N; s2++){
                        Arr3D[imin][s1][s2] = Arr3D[s][s1][s2];
                    }
                }

                for (int s1 = 0; s1 < M; s1++){
                    for (int s2 = 0; s2 < N; s2++){
                        Arr3D[s][s1][s2] = temp_slice[s1][s2];
                    }
                }
            }
    }

    time_stop = clock();
    free(SliceSum);
    return time_stop - time_start;
}
// Алгоритм №24 для сортування вектора

void QuickSort_Arr1D(int L, int R, int * Vector)
{
    int B, tmp, i, j;
    B=Vector[(L+R)/2];
    i=L; j=R;
    while (i<=j) {
        while (Vector[i] < B) i=i+1;
        while (Vector[j] > B) j=j-1;
        if (i<=j) {
            tmp=Vector[i];
            Vector[i]=Vector[j];
            Vector[j]=tmp;
            i=i+1;
            j=j-1;
        }
    }
    if (L<j) QuickSort_Arr1D(L,j, Vector);
    if (i<R) QuickSort_Arr1D(i,R, Vector);
}

void QuickSort(int M, int N, int *** Arr3D, int * SliceSum, int L, int R){ // Алгоритм сортування №24 масиву сум з паралельними змінами порядку розрізів головної матриці

    int B, tmp, i, j; // Змінні для сортування алгоритмом QuickSort
    B = SliceSum[(L + R) / 2]; // Центральний опорний елемент поділу
    i = L; j = R;

    int temp_slice[M][N];

    while (i <= j) {
        while (SliceSum[i] < B) i = i + 1;
        while (SliceSum[j] > B) j = j - 1;

        if (i <= j) {
            tmp = SliceSum[i];
            SliceSum[i] = SliceSum[j];
            SliceSum[j] = tmp;

            for (int s1 = 0; s1 < M; s1++){
                for (int s2 = 0; s2 < N; s2++){
                    temp_slice[s1][s2] = Arr3D[i][s1][s2];
                    }
                }

            for (int s1 = 0; s1 < M; s1++){
                for (int s2 = 0; s2 < N; s2++){
                    Arr3D[i][s1][s2] = Arr3D[j][s1][s2];
                }
            }

            for (int s1 = 0; s1 < M; s1++){
                for (int s2 = 0; s2 < N; s2++){
                    Arr3D[j][s1][s2] = temp_slice[s1][s2];
                }
            }

            i = i + 1;
            j = j - 1;
        }
    }
    if (L < j) QuickSort(M, N, Arr3D, SliceSum, L, j); // Виклики для сортування менших частин
    if (i < R) QuickSort(M, N, Arr3D, SliceSum, i, R);
}
