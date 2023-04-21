#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>

int * menu(int data[4]){

    void restart(){
        system("cls");
        printf("Попадаєте не по тим клавішам ? Спробуйте знову.");
        Sleep(2500);
        system("cls");
        menu(data);
    }

    int algorithm_number, sort_type; // Числа що відповідають за формування варіанту виконання програми на основі їх значень
    int counter = 1;
    int choice_matrix[4][4]; // Порядкові номера всіх можливих варінтів вибору складають матрицю (кількість алгоритмів) * (кількість типів сортування)

    for (int i = 0; i < 4; i++){ // Заповнення матриці
        for (int j = 0; j < 4; j++){
            choice_matrix[i][j] = counter;
            counter++;
        }
    }

    printf("Алгоритми:\n1. Алгоритм №3\n2. Алгоритм №10\n3. Алгоритм №24\n4. Запустити всі алгоритми\n\nОберіть пункт що відповідає бажаному номеру алгоритму: ");
    scanf("%d", &algorithm_number);

    if (algorithm_number < 1 || algorithm_number > 4){
        restart();
    }

    printf("\nТип сортування:\n1. Впорядкований\n2. Невпорядкований\n3. Обернено впорядкований\n4. Всі типи сортування\n\nОберіть тип сортування: ");
    scanf("%d", &sort_type);

    if (sort_type < 1 || sort_type > 4){
        restart();
    }

    data[0] = choice_matrix[algorithm_number - 1][sort_type - 1];

    printf("\n\nВведіть значення розмірності матриці (P, M, N): ");
    scanf("%d, %d, %d", &data[1], &data[2], &data[3]);

    return data;
}

int *** define_matrix(int P, int M, int N){
    int *** Arr3D = (int***) malloc(P * sizeof(int**));
    for (int k = 0; k < P; k++){
        Arr3D[k] = (int**) malloc(M * sizeof(int*));
        for (int i = 0; i < M; i++)
            Arr3D[k][i] = (int*) malloc(N * sizeof(int));
    }
    return Arr3D;
}

void free_memory(int P, int M, int N, int *** Arr3D){
    for (int k=0; k<P; k++){
        for (int i=0; i<M; i++)
            free(Arr3D[k][i]);
        free(Arr3D[k]);
    }
    free(Arr3D);
}

void fill_matrix(int P, int M, int N, int *** Arr3D, int type){

    int counter;

    if (type == 1){
        counter = 1;
        for (int p = 0; p < P; p++){
            for (int m = 0; m < M; m++){
                for (int n = 0; n < N; n++){
                    Arr3D[p][m][n] = counter++;
                }
            }
        }
    }

    else if (type == 2){
        int upper = 100;
        int lower = 0;
        for (int p = 0; p < P; p++){
            for (int m = 0; m < M; m++){
                for (int n = 0; n < N; n++){
                    Arr3D[p][m][n] = (rand() % (upper - lower + 1)) + lower;
                }
            }
        }
    }

    else{
        counter = P * M * N;
        for (int p = 0; p < P; p++){
            for (int m = 0; m < M; m++){
                for (int n = 0; n < N; n++){
                    Arr3D[p][m][n] = counter--;
                }
            }
        }
    }
}

void display_matrix(int P, int M, int N, int *** Arr3D){
    for (int i = 0; i < P; i++) {
        printf("Slice %d:\n", i);
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                printf("%d ", Arr3D[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

clock_t Insert3_by_slice_sum(int P, int M, int N, int *** Arr3D){

    clock_t time_start, time_stop;

    time_start = clock();

    // initialize the slice sum array and index array
    int slice_sum[P];
    int index_arr[P];
    for (int i = 0; i < P; i++) {
        slice_sum[i] = 0;
        index_arr[i] = i;
    }

    // calculate the sum of each slice and store in the slice sum array
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                slice_sum[i] += Arr3D[i][j][k];
            }
        }
    }

    // sort the slice sum array and index array using insertion sort
    for (int i = 1; i < P; i++) {
        int key = slice_sum[i];
        int index_key = index_arr[i];
        int j = i - 1;
        while (j >= 0 && slice_sum[j] > key) {
            slice_sum[j + 1] = slice_sum[j];
            index_arr[j + 1] = index_arr[j];
            j--;
        }
        slice_sum[j + 1] = key;
        index_arr[j + 1] = index_key;
    }

    // create a temporary array to store the sorted slices
    int*** temp_arr = malloc(P * sizeof(int**));
    for (int i = 0; i < P; i++) {
        temp_arr[i] = malloc(M * sizeof(int*));
        for (int j = 0; j < M; j++) {
            temp_arr[i][j] = malloc(N * sizeof(int));
        }
    }

    // copy the sorted slices to the temporary array
    for (int i = 0; i < P; i++) {
        int index = index_arr[i];
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                temp_arr[i][j][k] = Arr3D[index][j][k];
            }
        }
    }

    // copy the sorted slices back to the original array
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                Arr3D[i][j][k] = temp_arr[i][j][k];
            }
        }
    }

    // copy the sorted slices to the temporary array
    for (int i = 0; i < P; i++) {
        int index = index_arr[i];
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                temp_arr[i][j][k] = Arr3D[index][j][k];
            }
        }
    }

    // copy the sorted slices from the temporary array to the original array
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                Arr3D[i][j][k] = temp_arr[i][j][k];
            }
        }
    }

    // free the memory allocated for the temporary array
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < M; j++) {
            free(temp_arr[i][j]);
        }
        free(temp_arr[i]);
    }

    free(temp_arr);
    
    time_stop = clock();

    return time_stop - time_start;
}

int main(){

    // Таск
    // 5. Впорядкувати тривимірний масив Аrr3D [P,M,N] таким чи-
    // ном: переставити перерізи масива за незменшенням сум їх
    // елементів.

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(0));

    int data[4];
    menu(data); // Вибір варіанту виконання програми 1-16 всі можливі випадки

    int P = data[1];
    int M = data[2];
    int N = data[3];

    int *** Arr3D = define_matrix(P, M, N);

    switch (data[0])
    {
    case 1: // Алгоритм 1 Тип сортування 1
        fill_matrix(P, M, N, Arr3D, 1);
        printf("%Lf", (long double) Insert3_by_slice_sum(P, M, N, Arr3D));

        break;
     
    case 2: // Алгоритм 1 Тип сортування 2
        fill_matrix(P, M, N, Arr3D, 2);
        printf("%Lf", (long double) Insert3_by_slice_sum(P, M, N, Arr3D));

        break;

    case 3: // Алгоритм 1 Тип сортування 3
        fill_matrix(P, M, N, Arr3D, 3);
        printf("%Lf", (long double) Insert3_by_slice_sum(P, M, N, Arr3D));
        
        break;
    
    case 4: // Алгоритм 1 Тип сортування 4 (всі типи сортування)
        fill_matrix(P, M, N, Arr3D, 1);
        printf("\n%Lf\n", (long double) Insert3_by_slice_sum(P, M, N, Arr3D));

        fill_matrix(P, M, N, Arr3D, 2);
        printf("\n%Lf\n", (long double) Insert3_by_slice_sum(P, M, N, Arr3D));


        fill_matrix(P, M, N, Arr3D, 3);
        printf("\n%Lf\n", (long double) Insert3_by_slice_sum(P, M, N, Arr3D));
        break;

    case 5: // Алгоритм 2 Тип сортування 1
        /* code */
        break;

    case 6: // Алгоритм 2 Тип сортування 2
        /* code */
        break;

    case 7: // Алгоритм 2 Тип сортування 3
        /* code */
        break;
    
    case 8: // Алгоритм 2 Тип сортування 4 (всі типи сортування)
        /* code */
        break;
    
    case 9: // Алгоритм 3 Тип сортування 1
        /* code */
        break;

    case 10: // Алгоритм 3 Тип сортування 2
        /* code */
        break;
    
    case 11: // Алгоритм 3 Тип сортування 3
        /* code */
        break;

    case 12: // Алгоритм 3 Тип сортування 4 (всі типи сортування)
        /* code */
        break;

    case 13: // Алгоритм 4 Тип сортування 1
        /* code */
        break;

    case 14: // Алгоритм 4 Тип сортування 2
        /* code */
        break;

    case 15: // Алгоритм 4 Тип сортування 3
        /* code */
        break;

    case 16: // Алгоритм 4 Тип сортування 4 (всі типи сортування)
        /* code */
        break;

    default:
        break;
    }

    
    free_memory(P, M, N, Arr3D);

    return 0;
}

// int ***Arr3D;
// Arr3D = (int***) malloc(P*sizeof(int**));
// for (int k=0; k<P; k++)
// { Arr3D[k] = (int**) malloc(M*sizeof(int*));
// for (int i=0; i<M; i++)
// Arr3D[k][i] = (int*) malloc(N*sizeof(int));
// }

// for (int p=0; p<P; k++){
//     for (int i=0; i<M; i++)
//         free(Arr3D[k][i]);
//     free(Arr3D[k]);
// }
// free(Arr3D);