#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>

int MEASUREMENTS = 20; // Кількість вимірів для кожного алгоритму і кожного типу сортування
int rejected_number = 3; // Кількість відкинутих перших вимірів
int min_max_number = 2; // Кількість відкинутих екстремальних вимірів

int * menu(int data[4]){

    void restart(){
        system("cls");
        printf("Попадаєте не по тим клавішам ? Спробуйте знову.");
        Sleep(2500);
        system("cls");
        menu(data);
    }

    int algorithm_number, sort_type; // Числа що відповідають за формування варіанту виконання програми на основі їх значень
    int counter = 1; // Лічильник для номерів всім можливим комбінаціям (алгоритм - сортування) вибору користувача
    int choice_matrix[4][4]; // Порядкові номера всіх можливих варінтів вибору складають матрицю (кількість алгоритмів) * (кількість типів сортування)

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            choice_matrix[i][j] = counter;
            counter++;
        }
    }

    printf("Алгоритми:\n1. Алгоритм №3\n2. Алгоритм №10\n3. Алгоритм №24\n4. Запустити всі алгоритми\n5. Вийти з програми\n\nОберіть пункт що відповідає бажаному номеру алгоритму: ");
    scanf("%d", &algorithm_number);

    if (algorithm_number == 5) exit(1);

    if (algorithm_number < 1 || algorithm_number > 5){
        restart();
    }

    printf("\nТип сортування:\n1. Впорядкований\n2. Невпорядкований\n3. Обернено впорядкований\n4. Всі типи сортування\n\nОберіть тип сортування: ");
    scanf("%d", &sort_type);

    if (sort_type < 1 || sort_type > 4){
        restart();
    }

    data[0] = choice_matrix[algorithm_number - 1][sort_type - 1];

    printf("\nВведіть значення розмірності матриці (P, M, N): ");
    scanf("%d, %d, %d", &data[1], &data[2], &data[3]);

    return data;
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

void free_memory(int P, int M, int N, int *** Arr3D, int add){ // Функція для звілення пам'яті виділеної під тривимірний масив
    for (int k = 0; k < P + add; k++){
        for (int i = 0; i < M; i++)
            free(Arr3D[k][i]);
        free(Arr3D[k]);
    }
    free(Arr3D);
}

void fill_matrix(int P, int M, int N, int *** Arr3D, int type, int add){ // Функція для заповнення матриці в залежності від обраного типу (впорядкована, невпорядкована, обернено впорядкована)

    int counter;

    if (type == 1){
        counter = 1;
        for (int p = 0; p < P; p++){
            for (int m = 0; m < M; m++){
                for (int n = 0; n < N; n++){
                    Arr3D[p + add][m][n] = counter;
                    counter++;
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
                    Arr3D[p + add][m][n] = (rand() % (upper - lower + 1)) + lower;
                }
            }
        }
    }

    else{
        counter = P * M * N;
        for (int p = 0; p < P; p++){
            for (int m = 0; m < M; m++){
                for (int n = 0; n < N; n++){
                    Arr3D[p + add][m][n] = counter;
                    counter--;
                }
            }
        }
    }
}

clock_t Insert3(int P, int M, int N, int *** Arr3D){ // Алгоритм сортування №3 масиву сум з паралельними змінами порядку розрізів головної матриці

    clock_t time_start, time_stop;

    // Об'ява масиву сум, масиву індексів, масиву розрізів для обміну, формування масиву індексів
    int SliceSum[P + 1];
    int index_arr[P + 1];

    int temp_slice[M][N];

    for (int i = 0; i < P; i++) {
        SliceSum[i + 1] = 0;
        index_arr[i + 1] = i;
    }

    time_start = clock();

    // Формування масиву сум
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                SliceSum[i + 1] += Arr3D[i][j][k];
            }
        }
    }

    // Сортування масиву сум з паралельним переміщенням відповідних індексів
    for (int i = 1; i < P; i++) {
        int key = SliceSum[i];
        int index_key = index_arr[i];
        int j = i - 1;
        while (j >= 0 && SliceSum[j] > key) {
            SliceSum[j + 1] = SliceSum[j];
            index_arr[j + 1] = index_arr[j];
            j--;
        }
        SliceSum[j + 1] = key;
        index_arr[j + 1] = index_key;

        // Перестановка відповідних перерізів у матриці

        for (int s1 = 0; s1 < M; s1++){
            for (int s2 = 0; s2 < N; s2++){
                temp_slice[s1][s2] = Arr3D[j + 1][s1][s2];
            }
        }

        for (int s1 = 0; s1 < M; s1++){
            for (int s2 = 0; s2 < N; s2++){
                Arr3D[index_key][s1][s2] = Arr3D[index_key][s1][s2];
            }
        }

        for (int s1 = 0; s1 < M; s1++){
            for (int s2 = 0; s2 < N; s2++){
                Arr3D[j + 1][s1][s2] = temp_slice[s1][s2];
            }
        }
    }

    time_stop = clock();

    return time_stop - time_start;
}

clock_t Select6(int P, int M, int N, int *** Arr3D){ // Алгоритм сортування №10 масиву сум з паралельними змінами порядку розрізів головної матриці

    int imin, tmp;

    int temp_slice[M][N];

    clock_t time_start, time_stop;
    // Об'ява масиву сум
    int SliceSum[P];

    // Онулення всіх сум
    for (int i = 0; i < P; i++) {
        SliceSum[i] = 0;
    }

    time_start = clock();

    // Формування сум
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                SliceSum[i] += Arr3D[i][j][k];
            }
        }
    }

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

    return time_stop - time_start;
}

void QuickSort(int M, int N, int *** Arr3D, int * SliceSum, int L, int R){ // Алгоритм сортування №24 масиву сум з паралельними змінами порядку розрізів головної матриці

    int B, tmp, i, j;
    B = SliceSum[(L + R) / 2];
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
    if (L < j) QuickSort(M, N, Arr3D, SliceSum, L, j);
    if (i < R) QuickSort(M, N, Arr3D, SliceSum, i, R);
}

clock_t * QuickSortMeasurement(int P, int M, int N, int *** Arr3D, clock_t * Res, int type){ // Функція для виміру часу витраченого на сортування алгоритмом 24

    int L = 0;
    int R = P - 1;
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

void OutTable(float * measurements){ // Функція для виводу усереднених результатів у табличному виді
    printf("Алгоритм\tВпорядкований\tНевпорядкований\tОбернено впорядкований\n");
    printf("Алгоритм 1\t%f\t%f\t%f\n", measurements[0], measurements[1], measurements[2]);
    printf("Алгоритм 2\t%f\t%f\t%f\n", measurements[3], measurements[4], measurements[5]);
    printf("Алгоритм 3\t%f\t%f\t%f\n\n", measurements[6], measurements[7], measurements[8]);
}

int main(){

    // Таск
    // 5. Впорядкувати тривимірний масив Аrr3D [P,M,N] таким чи-
    // ном: переставити перерізи масива за незменшенням сум їх
    // елементів.

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(0));

    float measurements[9]; // Об'ява масиву усереднених результатів для виводу

    int data[4];

    while (TRUE){ // Цикл для перезапуску програми

        for (int i = 0; i < 9; i++){ // Установлення базового значення для вимірів для випадків часткового будування таблиці | Скидання значень до базових після виконання програми перед наступним виконанням
            measurements[i] = -1.0;
        }

        menu(data); // Вибір варіанту виконання програми 1-16 всі можливі випадки

        int P = data[1];
        int M = data[2];
        int N = data[3];

        int *** Arr3D;

        clock_t Res[MEASUREMENTS];

        switch (data[0]) // Варіанти виконання програми в залженості від обраних опцій у меню, де кожен case відповідає номеру вибору [1 - 16]
        {
        case 1: // Алгоритм 1 Тип сортування 1

            Arr3D = define_matrix(P, M, N, 1);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 1, 1);
                Res[i] = Insert3(P, M, N, Arr3D);
            }
            measurements[0] = MeasurementProcessing(Res);

            free_memory(P, M, N, Arr3D, 1);

            break;
        
        case 2: // Алгоритм 1 Тип сортування 2

            Arr3D = define_matrix(P, M, N, 1);
            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 2, 1);
                Res[i] = Insert3(P, M, N, Arr3D);
            }
            measurements[1] = MeasurementProcessing(Res);

            free_memory(P, M, N, Arr3D, 1);

            break;

        case 3: // Алгоритм 1 Тип сортування 3

            Arr3D = define_matrix(P, M, N, 1);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 3, 1);
                Res[i] = Insert3(P, M, N, Arr3D);
            }
            measurements[2] = MeasurementProcessing(Res);

            free_memory(P, M, N, Arr3D, 1);

            break;
        
        case 4: // Алгоритм 1 Всі типи сортування

            Arr3D = define_matrix(P, M, N, 1);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 1, 1);
                Res[i] = Insert3(P, M, N, Arr3D);
            }
            measurements[0] = MeasurementProcessing(Res);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 2, 1);
                Res[i] = Insert3(P, M, N, Arr3D);
            }
            measurements[1] = MeasurementProcessing(Res);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 3, 1);
                Res[i] = Insert3(P, M, N, Arr3D);
            }
            measurements[2] = MeasurementProcessing(Res);

            free_memory(P, M, N, Arr3D, 1);

            break;

        case 5: // Алгоритм 2 Тип сортування 1

            Arr3D = define_matrix(P, M, N, 0);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 1, 0);
                Res[i] = Select6(P, M, N, Arr3D);
            }
            measurements[3] = MeasurementProcessing(Res);

            free_memory(P, M, N, Arr3D, 0);

            break;

        case 6: // Алгоритм 2 Тип сортування 2

            Arr3D = define_matrix(P, M, N, 0);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 2, 0);
                Res[i] = Select6(P, M, N, Arr3D);
            }
            measurements[4] = MeasurementProcessing(Res);

            break;

        case 7: // Алгоритм 2 Тип сортування 3

            Arr3D = define_matrix(P, M, N, 0);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 3, 0);
                Res[i] = Select6(P, M, N, Arr3D);
            }
            measurements[5] = MeasurementProcessing(Res);

            break;
        
        case 8: // Алгоритм 2 Всі типи сортування

            Arr3D = define_matrix(P, M, N, 0);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 1, 0);
                Res[i] = Select6(P, M, N, Arr3D);
            }
            measurements[3] = MeasurementProcessing(Res);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 2, 0);
                Res[i] = Select6(P, M, N, Arr3D);
            }
            measurements[4] = MeasurementProcessing(Res);

           for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 3, 0);
                Res[i] = Select6(P, M, N, Arr3D);
            }
            measurements[5] = MeasurementProcessing(Res);

            free_memory(P, M, N, Arr3D, 0);

            break;
        
        case 9: // Алгоритм 3 Тип сортування 1

            Arr3D = define_matrix(P, M, N, 0);

            measurements[6] = MeasurementProcessing(
            QuickSortMeasurement(P, M, N, Arr3D, Res, 1)
            );

            free_memory(P, M, N, Arr3D, 0);

            break;

        case 10: // Алгоритм 3 Тип сортування 2

            Arr3D = define_matrix(P, M, N, 0);

            measurements[7] = MeasurementProcessing(
            QuickSortMeasurement(P, M, N, Arr3D, Res, 2)
            );
            
            free_memory(P, M, N, Arr3D, 0);

            break;
        
        case 11: // Алгоритм 3 Тип сортування 3

            Arr3D = define_matrix(P, M, N, 0);

            measurements[8] = MeasurementProcessing(
            QuickSortMeasurement(P, M, N, Arr3D, Res, 3)
            );

            free_memory(P, M, N, Arr3D, 0);


            break;

        case 12: // Алгоритм 3 Всі типи сортування

            Arr3D = define_matrix(P, M, N, 0);

            measurements[6] = MeasurementProcessing(
            QuickSortMeasurement(P, M, N, Arr3D, Res, 1)
            );

            fill_matrix(P, M, N, Arr3D, 2, 0);
            measurements[7] = MeasurementProcessing(
            QuickSortMeasurement(P, M, N, Arr3D, Res, 2)
            );

            fill_matrix(P, M, N, Arr3D, 3, 0);
            measurements[8] = MeasurementProcessing(
            QuickSortMeasurement(P, M, N, Arr3D, Res, 3)
            );
            break;

        case 13: // Всі алгоритми, Тип сортування 1

            Arr3D = define_matrix(P, M, N, 1);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 1, 1);
                Res[i] = Insert3(P, M, N, Arr3D);
            }
            measurements[0] = MeasurementProcessing(Res);

            free_memory(P, M, N, Arr3D, 1);

            Arr3D = define_matrix(P, M, N, 0);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 1, 0);
                Res[i] = Select6(P, M, N, Arr3D);
            }
            measurements[3] = MeasurementProcessing(Res);

            measurements[6] = MeasurementProcessing(
            QuickSortMeasurement(P, M, N, Arr3D, Res, 1)
            );

            free_memory(P, M, N, Arr3D, 0);

            break;

        case 14: // Всі алгоритми, Тип сортування 2

            Arr3D = define_matrix(P, M, N, 1);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 2, 1);
                Res[i] = Insert3(P, M, N, Arr3D);
            }
            measurements[1] = MeasurementProcessing(Res);

            free_memory(P, M, N, Arr3D, 1);

            Arr3D = define_matrix(P, M, N, 0);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 2, 0);
                Res[i] = Select6(P, M, N, Arr3D);
            }
            measurements[4] = MeasurementProcessing(Res);

            measurements[7] = MeasurementProcessing(
            QuickSortMeasurement(P, M, N, Arr3D, Res, 2)
            );

            free_memory(P, M, N, Arr3D, 0);

            break;

        case 15: // Всі алгоритми, Тип сортування 3

            Arr3D = define_matrix(P, M, N, 1);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 3, 1);
                Res[i] = Insert3(P, M, N, Arr3D);
            }
            measurements[2] = MeasurementProcessing(Res);

            free_memory(P, M, N, Arr3D, 1);

            Arr3D = define_matrix(P, M, N, 0);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 3, 0);
                Res[i] = Select6(P, M, N, Arr3D);
            }
            measurements[5] = MeasurementProcessing(Res);

            measurements[8] = MeasurementProcessing(
            QuickSortMeasurement(P, M, N, Arr3D, Res, 3)
            );

            free_memory(P, M, N, Arr3D, 0);

            break;

        case 16: // Всі алгоритми, Всі типи сортування
            
            Arr3D = define_matrix(P, M, N, 1);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 1, 0);
                Res[i] = Insert3(P, M, N, Arr3D);
            }
            measurements[0] = MeasurementProcessing(Res);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 2, 0);
                Res[i] = Insert3(P, M, N, Arr3D);
            }
            measurements[1] = MeasurementProcessing(Res);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 3, 0);
                Res[i] = Insert3(P, M, N, Arr3D);
            }
            measurements[2] = MeasurementProcessing(Res);

            free_memory(P, M, N, Arr3D, 1);

            Arr3D = define_matrix(P, M, N, 0);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 1, 0);
                Res[i] = Select6(P, M, N, Arr3D);
            }
            measurements[3] = MeasurementProcessing(Res);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 2, 0);
                Res[i] = Select6(P, M, N, Arr3D);
            }
            measurements[4] = MeasurementProcessing(Res);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 3, 0);
                Res[i] = Select6(P, M, N, Arr3D);
            }
            measurements[5] = MeasurementProcessing(Res);

            measurements[6] = MeasurementProcessing(
            QuickSortMeasurement(P, M, N, Arr3D, Res, 1)
            );

            measurements[7] = MeasurementProcessing(
            QuickSortMeasurement(P, M, N, Arr3D, Res, 2)
            );

            measurements[8] = MeasurementProcessing(
            QuickSortMeasurement(P, M, N, Arr3D, Res, 3)
            );

            free_memory(P, M, N, Arr3D, 0);

            break;

        default:
            break;
        }

        OutTable(measurements);

    }
    
    return 0;
}