#ifndef PROCESSING_H_INCLUDED
#define PROCESSING_H_INCLUDED

#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>

clock_t * QuickSortMeasurement_Arr1D(int P, clock_t * Res, int type, int add, int * Vector);
clock_t * QuickSortMeasurement(int P, int M, int N, int *** Arr3D, clock_t * Res, int type);
float MeasurementProcessing(clock_t * Res);
int *** define_matrix(int P, int M, int N, int add);
void free_memory(int P, int M, int N, int *** Arr3D, int add);
void fill_matrix(int P, int M, int N, int *** Arr3D, int type, int add);
int * CreateVector(int P, int add);
void FillVector(int P, int * Vector, int type, int add);

#endif