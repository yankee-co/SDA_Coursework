
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>

int MEASUREMENTS = 16; // Кількість вимірів для кожного алгоритму і кожного типу сортування
int rejected_number = 4; // Кількість відкинутих перших вимірів
int min_max_number = 4; // Кількість відкинутих екстремальних вимірів

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

int main(){
    clock_t Res[MEASUREMENTS];

    int P = 15000, M = 16, N = 16;

    int *** Arr3D = define_matrix(P, M, N, 1);

    for (int i = 0; i < MEASUREMENTS; i++){
        fill_matrix(P, M, N, Arr3D, 2, 1);
        Res[i] = Insert3(P, M, N, Arr3D);
    }
    float res = MeasurementProcessing(Res);

    printf("res = %f m = %d n = %d", res, M, N);

    free_memory(P, M, N, Arr3D, 1);

    return 0;
}