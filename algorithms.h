#ifndef ALGORITHMS_H_INCLUDED
#define ALGORITHMS_H_INCLUDED

#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>

clock_t Insert3_Arr1D(int *Vector, int P);
clock_t Select6_Arr1D(int *A, int N);
clock_t Select6_Arr1D(int *A, int N);
clock_t Insert3(int P, int M, int N, int *** Arr3D);
clock_t Select6(int P, int M, int N, int *** Arr3D);
void QuickSort_Arr1D(int L, int R, int * Vector);
void QuickSort(int M, int N, int *** Arr3D, int * SliceSum, int L, int R);

#endif