#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>

int MEASUREMENTS = 10; // ʳ������ ����� ��� ������� ��������� � ������� ���� ����������
int rejected_number = 2; // ʳ������ ��������� ������ �����
int min_max_number = 2; // ʳ������ ��������� ������������� �����

int * menu(int data[4]){

    int choice1, choice2; // ����� �� ���������� �� ���������� ������� ��������� �������� �� ����� �� �������
    int counter = 1; // ˳������� ��� ������ ��� �������� ���������� (�������� - ����������) ������ �����������
    int choice_matrix[4][4]; // �������� ������ ��� �������� ������ ������ ��������� ������� (������� ���������) * (������� ���� ����������)

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            choice_matrix[i][j] = counter;
            counter++;
        }
    }

    printf("���������:\n1. �������� �3\n2. �������� �10\n3. �������� �24\n4. ��������� �� ���������\n5. ����� � ��������\n\n������ ����� �� ������� �������� ������ ���������: ");
    scanf("%d", &choice1);

    if (choice1 == 5) exit(1);

    if (choice1 < 1 || choice1 > 5){
        system("cls");
        printf("�������� �� �� ��� ������� ? ��������� �����.");
        Sleep(2500);
        system("cls");
        menu(data);
    }

    

    printf("\n��� ����������:\n1. �������������\n2. ���������������\n3. �������� �������������\n4. �� ���� ����������\n\n������ ��� ����������: ");
    scanf("%d", &choice2);

    if (choice2 < 1 || choice2 > 4){
        system("cls");
        printf("�������� �� �� ��� ������� ? ��������� �����.");
        Sleep(2500);
        system("cls");
        menu(data);
    }

    data[0] = choice_matrix[choice1 - 1][choice2 - 1];
    
    printf("\n������ ���������� ������� (P, M, N): \n1. 50000 x 100 x 100\n2. 25000 x 100 x 100\n3. 10000 x 100 x 100\n4. 1000 x 1000 x 1000\n5. 1000 x 100 x 100\n6. ������ ���������\n\n�����: ");
    scanf("%d", &choice1);

    switch (choice1)
    {
    case 1:

        data[1] = 50000;
        data[2] = 100;
        data[3] = 100;

        break;
    case 2:

        data[1] = 25000;
        data[2] = 100;
        data[3] = 100;

        break;
    
    case 3:

        data[1] = 10000;
        data[2] = 100;
        data[3] = 100;

        break;

    case 4:

        data[1] = 1000;
        data[2] = 100;
        data[3] = 100;

        break;
    case 5:

        data[1] = 1000;
        data[2] = 10;
        data[3] = 10;

        break;

    case 6:

        printf("\n������ �������� ��������� ������� (P, M, N): ");
        scanf("%d, %d, %d", &data[1], &data[2], &data[3]);

        break;

    default:
        system("cls");
        printf("�������� �� �� ��� ������� ? ��������� �����.");
        Sleep(2500);
        system("cls");
        menu(data);
    }

    return data;
}

int *** define_matrix(int P, int M, int N, int add){ // ������� ��� �������� ���'�� �� ���������� �����
    int *** Arr3D = (int ***) malloc((P + add) * sizeof(int **));
    for (int k = 0; k < P + add; k++){
        Arr3D[k] = (int **) malloc(M * sizeof(int *));
        for (int i = 0; i < M; i++)
            Arr3D[k][i] = (int *) malloc(N * sizeof(int));
    }

    return Arr3D;
}

void free_memory(int P, int M, int N, int *** Arr3D, int add){ // ������� ��� ������� ���'�� ������� �� ���������� �����
    for (int k = 0; k < P + add; k++){
        for (int i = 0; i < M; i++)
            free(Arr3D[k][i]);
        free(Arr3D[k]);
    }
    free(Arr3D);
}

void fill_matrix(int P, int M, int N, int *** Arr3D, int type, int add){ // ������� ��� ���������� ������� � ��������� �� �������� ���� (������������, ��������������, �������� ������������)

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

clock_t Insert3(int P, int M, int N, int *** Arr3D){ // ???????? ?????????? ?3 ?????? ??? ? ???????????? ??????? ??????? ???????? ???????? ???????

    clock_t time_start, time_stop;

    // ??'??? ?????? ???, ?????? ????????, ?????? ???????? ??? ??????, ?????????? ?????? ????????
    int SliceSum[P + 1];
    int KeySlice[M][N];

    time_start = clock();

    // ?????????? ?????? ???
    for (int i = 1; i < P + 1; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                SliceSum[i] += Arr3D[i][j][k];
            }
        }
    }

    // ?????????? ?????? ??? ? ??????????? ???????????? ??????????? ????????
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

        // ???????????? ??????????? ????????? ? ???????

    }

    time_stop = clock();

    return time_stop - time_start;
}

clock_t Select6(int P, int M, int N, int *** Arr3D){ // �������� ���������� �10 ������ ��� � ������������ ������ ������� ������ ������� �������

    int imin, tmp;
    int temp_slice[M][N];
    int SliceSum[P];

    clock_t time_start, time_stop;
    
    time_start = clock();

    // ���������� ���
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

void QuickSort(int M, int N, int *** Arr3D, int * SliceSum, int L, int R){ // �������� ���������� �24 ������ ��� � ������������ ������ ������� ������ ������� �������

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

clock_t * QuickSortMeasurement(int P, int M, int N, int *** Arr3D, clock_t * Res, int type){ // ������� ��� ����� ���� ����������� �� ���������� ���������� 24

    int L = 0;
    int R = P - 1;
    int SliceSum[P];

    clock_t time_start, time_stop;

    for (int i = 0; i < MEASUREMENTS; i++){

        fill_matrix(P, M, N, Arr3D, type, 0);

        for (int i = 0; i < P; i++) {
            for (int j = 0; j < M; j++) {
                for (int k = 0; k < N; k++) {
                    SliceSum[i] += Arr3D[i][j][k];
                }
            }
        }   

        time_start = clock();

        QuickSort(M, N, Arr3D, SliceSum, L, R);

        time_stop = clock();

        Res[i] = time_stop - time_start;
    }

    return Res;
}

float MeasurementProcessing(clock_t * Res){ // ����������� ���������� ���������� ���������� ������ �� ������������� �������

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

void OutTable(float * measurements){ // ������� ��� ������ ����������� ���������� � ���������� ���
    printf("��������\t�������������\t���������������\t�������� �������������\n");
    printf("�������� 1\t%f\t%f\t%f\n", measurements[0], measurements[1], measurements[2]);
    printf("�������� 2\t%f\t%f\t%f\n", measurements[3], measurements[4], measurements[5]);
    printf("�������� 3\t%f\t%f\t%f\n\n", measurements[6], measurements[7], measurements[8]);
}

int main(){

    // ����
    // 5. ������������ ���������� ����� �rr3D [P,M,N] ����� ��-
    // ���: ����������� ������� ������ �� ������������ ��� ��
    // ��������.

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(0));

    float measurements[9]; // ��'��� ������ ����������� ���������� ��� ������

    int data[4];

    while (TRUE){ // ���� ��� ����������� ��������

        for (int i = 0; i < 9; i++){ // ������������ �������� �������� ��� ����� ��� ������� ���������� ��������� ������� | �������� ������� �� ������� ���� ��������� �������� ����� ��������� ����������
            measurements[i] = -1.0;
        }

        menu(data); // ���� ������� ��������� �������� 1-16 �� ������ �������

        int P = data[1];
        int M = data[2];
        int N = data[3];

        int *** Arr3D;

        clock_t Res[MEASUREMENTS];

        switch (data[0]) // ������� ��������� �������� � ��������� �� ������� ����� � ����, �� ����� case ������� ������ ������ [1 - 16]
        {
        case 1: // �������� 1 ��� ���������� 1

            Arr3D = define_matrix(P, M, N, 1);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 1, 1);
                Res[i] = Insert3(P, M, N, Arr3D);
            }
            measurements[0] = MeasurementProcessing(Res);

            free_memory(P, M, N, Arr3D, 1);

            break;
        
        case 2: // �������� 1 ��� ���������� 2

            Arr3D = define_matrix(P, M, N, 1);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 2, 1);
                Res[i] = Insert3(P, M, N, Arr3D);
            }
            measurements[1] = MeasurementProcessing(Res);

            free_memory(P, M, N, Arr3D, 1);

            break;

        case 3: // �������� 1 ��� ���������� 3

            Arr3D = define_matrix(P, M, N, 1);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 3, 1);
                Res[i] = Insert3(P, M, N, Arr3D);
            }
            measurements[2] = MeasurementProcessing(Res);

            free_memory(P, M, N, Arr3D, 1);

            break;
        
        case 4: // �������� 1 �� ���� ����������

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

        case 5: // �������� 2 ��� ���������� 1

            Arr3D = define_matrix(P, M, N, 0);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 1, 0);
                Res[i] = Select6(P, M, N, Arr3D);
            }
            measurements[3] = MeasurementProcessing(Res);

            free_memory(P, M, N, Arr3D, 0);

            break;

        case 6: // �������� 2 ��� ���������� 2

            Arr3D = define_matrix(P, M, N, 0);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 2, 0);
                Res[i] = Select6(P, M, N, Arr3D);
            }
            measurements[4] = MeasurementProcessing(Res);

            break;

        case 7: // �������� 2 ��� ���������� 3

            Arr3D = define_matrix(P, M, N, 0);

            for (int i = 0; i < MEASUREMENTS; i++){
                fill_matrix(P, M, N, Arr3D, 3, 0);
                Res[i] = Select6(P, M, N, Arr3D);
            }
            measurements[5] = MeasurementProcessing(Res);

            break;
        
        case 8: // �������� 2 �� ���� ����������

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
        
        case 9: // �������� 3 ��� ���������� 1

            Arr3D = define_matrix(P, M, N, 0);

            measurements[6] = MeasurementProcessing(
            QuickSortMeasurement(P, M, N, Arr3D, Res, 1)
            );

            free_memory(P, M, N, Arr3D, 0);

            break;

        case 10: // �������� 3 ��� ���������� 2

            Arr3D = define_matrix(P, M, N, 0);

            measurements[7] = MeasurementProcessing(
            QuickSortMeasurement(P, M, N, Arr3D, Res, 2)
            );
            
            free_memory(P, M, N, Arr3D, 0);

            break;
        
        case 11: // �������� 3 ��� ���������� 3

            Arr3D = define_matrix(P, M, N, 0);

            measurements[8] = MeasurementProcessing(
            QuickSortMeasurement(P, M, N, Arr3D, Res, 3)
            );

            free_memory(P, M, N, Arr3D, 0);


            break;

        case 12: // �������� 3 �� ���� ����������

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

        case 13: // �� ���������, ��� ���������� 1

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

        case 14: // �� ���������, ��� ���������� 2

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

        case 15: // �� ���������, ��� ���������� 3

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

        case 16: // �� ���������, �� ���� ����������
            
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
    
    char c = getchar();

    return 0;
}