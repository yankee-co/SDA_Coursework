#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>

int MEASUREMENTS = 16; // Кількість вимірів для кожного алгоритму і кожного типу сортування
int rejected_number = 4; // Кількість відкинутих перших вимірів
int min_max_number = 4; // Кількість відкинутих екстремальних вимірів

// Функція яка формує вибір варіанту виконання програми на основі введених юзером даних

int * menu(int data[4]){

    int choice1, choice2; // Числа що відповідають за формування варіанту виконання програми на основі їх значень
    int counter = 1; // Лічильник для номерів всім можливим комбінаціям (алгоритм - сортування) вибору користувача
    int choice_matrix[4][4]; // Порядкові номера всіх можливих варінтів вибору складають матрицю (кількість алгоритмів) * (кількість типів сортування)

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            choice_matrix[i][j] = counter;
            counter++;
        }
    }

    printf("Алгоритми:\n1. Алгоритм №3\n2. Алгоритм №10\n3. Алгоритм №24\n4. Запустити всі алгоритми\n5. Вийти з програми\n\nОберіть пункт що відповідає бажаному номеру алгоритму: ");
    scanf("%d", &choice1);

    if (choice1 < 1 || choice1 > 4){
        printf("Невірно введені дані."); exit(0);
    }

    printf("\nТип сортування:\n1. Впорядкований\n2. Невпорядкований\n3. Обернено впорядкований\n4. Всі типи сортування\n\nОберіть тип сортування: ");
    scanf("%d", &choice2);

    if (choice2 < 1 || choice2 > 4){
        printf("Невірно введені дані."); exit(0);
    }

    data[0] = choice_matrix[choice1 - 1][choice2 - 1];
    
    printf("Оберіть предмет роботи програми:\n1. Одновимірний масив\n2. Тривимірний масив\n\n");
    printf("Опція: ");
    scanf("%d", &choice1);

    if (choice1 == 1){

        printf("Розмір масиву:\n1. 15000\n2. 5000\n\n");
        printf("Опція: ");

        scanf("%d ", &choice2);

        if (choice2 < 1 || choice2 > 2){
            printf("Невірно введені дані."); exit(0);
        }

        if (choice2 == 1)
        {
            data[1] = 15000;
        }
        else if (choice2 == 2){
            data[1] = 5000;
        }

        data[2] = 0;
        data[3] = 0;

        return data;
    }

    printf("\nОберіть розмірність матриці (P, M, N): \n");
    printf("Випадок дослідження 1. Форма перерізу - квадрат.\n\n");
    printf("1. 15000 x 1 x 1\n2. 15000 x 2 x 2\n3. 15000 x 4 x 4\n4. 15000 x 8 x 8\n5. 15000 x 16 x 16\n\n");
    printf("Випадок дослідження 2. Залежність часу роботи алгоритмів від форми перерізів масива\n\n");
    printf("6. 4000 x 2 x 800\n7. 4000 x 4 x 400\n8. 4000 x 8 x 200\n9. 4000 x 16 x 100\n10. 4000 x 100 x 16\n11. 4000 x 100 x 8\n12. 4000 x 200 x 4\n13. 4000 x 800 x 2\n14. Задати розмірність власноруч\n\nОпція: ");
    scanf("%d", &choice1);

    switch (choice1)
    {
    case 1:

        data[1] = 15000;
        data[2] = 1;
        data[3] = 1;

        break;
    case 2:

        data[1] = 15000;
        data[2] = 2;
        data[3] = 2;

        break;
    
    case 3:

        data[1] = 15000;
        data[2] = 4;
        data[3] = 4;

        break;

    case 4:

        data[1] = 15000;
        data[2] = 8;
        data[3] = 8;

        break;
    case 5:

        data[1] = 15000;
        data[2] = 16;
        data[3] = 16;

        break;

    case 6:

        data[1] = 4000;
        data[2] = 2;
        data[3] = 800;

        break;
    case 7:

        data[1] = 4000;
        data[2] = 4;
        data[3] = 400;

        break;
    
    case 8:

        data[1] = 4000;
        data[2] = 8;
        data[3] = 200;

        break;

    case 9:

        data[1] = 4000;
        data[2] = 16;
        data[3] = 100;

        break;
    case 10:

        data[1] = 4000;
        data[2] = 100;
        data[3] = 16;

        break;

    case 11:

        data[1] = 4000;
        data[2] = 200;
        data[3] = 8;

        break;

    case 12:

        data[1] = 4000;
        data[2] = 400;
        data[3] = 4;

        break;

    case 13:

        data[1] = 4000;
        data[2] = 800;
        data[3] = 2;

        break;

    case 14:

        printf("\nВведіть значення розмірності матриці (P, M, N): ");
        scanf("%d, %d, %d", &data[1], &data[2], &data[3]);

        break;

    default:
        break;
    }

    return data;
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
                    Arr3D[p][m][n] = (rand() % (upper - lower + 1)) + lower;
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

clock_t Insert3_Arr1D(int P){

    clock_t time_start, time_stop;

    // Масив для сум перерізів

    int * Arr1D = (int *) malloc(sizeof(int) * (P + 1));

    for (int p = 0; p < P + 1; p++){
        Arr1D[p] = p - 1;
    }

    time_start = clock();

    // Сортування
    for (int i = 1; i < P; i++) {
        int key = Arr1D[i];

        int j = i - 1;
        while (j >= 0 && Arr1D[j] > key) {
            Arr1D[j + 1] = Arr1D[j];
            j--;
        }
        Arr1D[j + 1] = key;

    }

    time_stop = clock();

    free(Arr1D);

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
    if (L < j) QuickSort(M, N, Arr3D, SliceSum, L, j); // Виклик для сортування меншої частини
    if (i < R) QuickSort(M, N, Arr3D, SliceSum, i, R);
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

    int data[4]; // Дані вибору користувачем

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

            if (!M && !N){

                Arr3D = define_matrix(P, M, N, 1);

                for (int i = 0; i < MEASUREMENTS; i++){
                    fill_matrix(P, M, N, Arr3D, 1, 1);
                    Res[i] = Insert3(P, M, N, Arr3D);
                }
                measurements[0] = MeasurementProcessing(Res);

                free_memory(P, M, N, Arr3D, 1);
            }
            else {
                for (int i = 0; i < MEASUREMENTS; i++){
                    Res[i] = Insert3_Arr1D(P);
                }
                measurements[0] = MeasurementProcessing(Res);
            }   

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

        OutTable(measurements); // Вивід таблиці з даними

    }
    
    char c = getchar();

    return 0;
}