#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>

int * menu(int data[4]){

    void restart(){
        system("cls");
        printf("�������� �� �� ��� ������� ? ��������� �����.");
        Sleep(2500);
        system("cls");
        menu(data);
    }

    int algorithm_number, sort_type; // ����� �� ���������� �� ���������� ������� ��������� �������� �� ����� �� �������
    int counter = 1;
    int choice_matrix[4][4]; // �������� ������ ��� �������� ������ ������ ��������� ������� (������� ���������) * (������� ���� ����������)

    for (int i = 0; i < 4; i++){ // ���������� �������
        for (int j = 0; j < 4; j++){
            choice_matrix[i][j] = counter;
            counter++;
        }
    }

    printf("���������:\n1. �������� �3\n2. �������� �10\n3. �������� �24\n4. ��������� �� ���������\n\n������ ����� �� ������� �������� ������ ���������: ");
    scanf("%d", &algorithm_number);

    if (algorithm_number < 1 || algorithm_number > 4){
        restart();
    }

    printf("\n��� ����������:\n1. �������������\n2. ���������������\n3. �������� �������������\n4. �� ���� ����������\n\n������ ��� ����������: ");
    scanf("%d", &sort_type);

    if (sort_type < 1 || sort_type > 4){
        restart();
    }

    data[0] = choice_matrix[algorithm_number - 1][sort_type - 1];

    printf("\n\n������ �������� ��������� ������� (P, M, N): ");
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

    if (NULL == Arr3D && 4*P*M*N != 0) printf("Allocation was unsuccessful");

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
    // ��'��� ������ ���, ������ �������, ���������� ������ �������
    int slice_sum[P+1];
    int index_arr[P+1];
    
    for (int i = 0; i < P; i++) {
        slice_sum[i+1] = 0;
        index_arr[i+1] = i;
    }

    time_start = clock();

    // ���������� ������ ���
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                slice_sum[i+1] += Arr3D[i][j][k];
            }
        }
    }

    // ���������� ������ ��� � ����������� ����������� ��������� �������
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

        // ������������ ��������� ������� � �������
        int** temp_slice = Arr3D[index_key];
        Arr3D[index_key] = Arr3D[j + 1];
        Arr3D[j + 1] = temp_slice;
    }

    time_stop = clock();

    return time_stop - time_start;
}

int main(){

    // ����
    // 5. ������������ ���������� ����� �rr3D [P,M,N] ����� ��-
    // ���: ����������� ������� ������ �� ������������ ��� ��
    // ��������.

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(0));

    int data[4];
    menu(data); // ���� ������� ��������� �������� 1-16 �� ������ �������

    int P = data[1];
    int M = data[2];
    int N = data[3];

    int *** Arr3D;
    Arr3D = define_matrix(P, M, N);

    switch (data[0])
    {
    case 1: // �������� 1 ��� ���������� 1
        
        fill_matrix(P, M, N, Arr3D, 1);
        printf("%ld", (long double) Insert3_by_slice_sum(P, M, N, Arr3D));
        
        break;
     
    case 2: // �������� 1 ��� ���������� 2
        fill_matrix(P, M, N, Arr3D, 2);
        printf("%f", (double) Insert3_by_slice_sum(P, M, N, Arr3D) / CLOCKS_PER_SEC);

        break;

    case 3: // �������� 1 ��� ���������� 3
        fill_matrix(P, M, N, Arr3D, 3);
        printf("%Lf", (long double) Insert3_by_slice_sum(P, M, N, Arr3D));
        
        break;
    
    case 4: // �������� 1 ��� ���������� 4 (�� ���� ����������)
        fill_matrix(P, M, N, Arr3D, 1);
        printf("\n%Lf\n", (long double) Insert3_by_slice_sum(P, M, N, Arr3D));
        fill_matrix(P, M, N, Arr3D, 2);
        printf("\n%Lf\n", (long double) Insert3_by_slice_sum(P, M, N, Arr3D));


        fill_matrix(P, M, N, Arr3D, 3);
        printf("\n%Lf\n", (long double) Insert3_by_slice_sum(P, M, N, Arr3D));
        break;

    case 5: // �������� 2 ��� ���������� 1
        /* code */
        break;

    case 6: // �������� 2 ��� ���������� 2
        /* code */
        break;

    case 7: // �������� 2 ��� ���������� 3
        /* code */
        break;
    
    case 8: // �������� 2 ��� ���������� 4 (�� ���� ����������)
        /* code */
        break;
    
    case 9: // �������� 3 ��� ���������� 1
        /* code */
        break;

    case 10: // �������� 3 ��� ���������� 2
        /* code */
        break;
    
    case 11: // �������� 3 ��� ���������� 3
        /* code */
        break;

    case 12: // �������� 3 ��� ���������� 4 (�� ���� ����������)
        /* code */
        break;

    case 13: // �������� 4 ��� ���������� 1
        /* code */
        break;

    case 14: // �������� 4 ��� ���������� 2
        /* code */
        break;

    case 15: // �������� 4 ��� ���������� 3
        /* code */
        break;

    case 16: // �������� 4 ��� ���������� 4 (�� ���� ����������)
        /* code */
        break;

    default:
        break;
    }
    // display_matrix(P, M, N, Arr3D);
    
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

/*
clock_t Insert3(int *A, int N){
    int j;
    clock_t time_start, time_stop;
    time_start = clock();
    for(int i=2; i<N+1; i++){
        A[0]=A[i];
        j=i;
        while (A[0]<A[j-1]) {
            A[j]=A[j-1];
            j=j-1;
        }
        A[j]=A[0];
    }
    time_stop = clock();
    return time_stop - time_start;
}
*/