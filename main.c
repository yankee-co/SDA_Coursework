#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>

#include "common.h"
#include "processing.h"
#include "algorithms.h"

// ������� ��� ����� ���� ������� ��������� �������� �� ����� �������� ������ �����

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

    if (choice1 < 1 || choice1 > 4){
        printf("\n������ ������ ���.\n"); exit(0);
    }

    printf("\n��� ����������:\n1. �������������\n2. ���������������\n3. �������� �������������\n4. �� ���� ����������\n\n������ ��� ����������: ");
    scanf("%d", &choice2);

    if (choice2 < 1 || choice2 > 4){
        printf("\n������ ������ ���.\n"); exit(0);
    }

    data[0] = choice_matrix[choice1 - 1][choice2 - 1];
    
    printf("\n������ ������� ������ ��������:\n1. ����������� �����\n2. ���������� �����\n\n");
    printf("�����: ");
    scanf("%d", &choice1);

    if (choice1 == 1){

        printf("\n������ �������� ������� ������� (P): ");
        scanf("%d", &data[1]);

        data[2] = 0;
        data[3] = 0;

        return data;
    }

    printf("\n������ ��������� ������� (P, M, N): \n");
    printf("������� ���������� 1. ����� ������� - �������.\n\n");
    printf("1. 15000 x 1 x 1\n2. 15000 x 2 x 2\n3. 15000 x 4 x 4\n4. 15000 x 8 x 8\n5. 15000 x 16 x 16\n\n");
    printf("������� ���������� 2. ��������� ���� ������ ��������� �� ����� ������� ������\n\n");
    printf("6. 4000 x 2 x 800\n7. 4000 x 4 x 400\n8. 4000 x 8 x 200\n9. 4000 x 16 x 100\n10. 4000 x 100 x 16\n11. 4000 x 200 x 8\n12. 4000 x 400 x 4\n13. 4000 x 800 x 2\n14. ������ ��������� ���������\n\n�����: ");
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

        printf("\n������ �������� ��������� ������� (P, M, N): ");
        scanf("%d, %d, %d", &data[1], &data[2], &data[3]);

        break;

    default:
        break;
    }

    return data;
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

    int data[4]; // ��� ������ ������������

    while (TRUE){ // ���� ��� ����������� ��������

        for (int i = 0; i < 9; i++){ // ������������ �������� �������� ��� ����� ��� ������� ���������� ��������� ������� | �������� ������� �� ������� ���� ��������� �������� ����� ��������� ����������
            measurements[i] = -1.0;
        }

        menu(data); // ���� ������� ��������� �������� 1-16 �� ������ �������

        int P = data[1];
        int M = data[2];
        int N = data[3];

        int *** Arr3D;
        int * Vector;

        clock_t Res[MEASUREMENTS];

        switch (data[0]) // ������� ��������� �������� � ��������� �� ������� ����� � ����, �� ����� case ������� ������ ������ [1 - 16]
        {
        case 1: // �������� 1 ��� ���������� 1

            if (M && N){

                Arr3D = define_matrix(P, M, N, 1);

                for (int i = 0; i < MEASUREMENTS; i++){
                    fill_matrix(P, M, N, Arr3D, 1, 1);
                    Res[i] = Insert3(P, M, N, Arr3D);
                }
                measurements[0] = MeasurementProcessing(Res);

                free_memory(P, M, N, Arr3D, 1);
            }
            else {
                Vector = CreateVector(P, 1);
                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 1, 1);
                    Res[i] = Insert3_Arr1D(Vector, P);
                }
                measurements[0] = MeasurementProcessing(Res);

                free(Vector);
            }   

            break;
        
        case 2: // �������� 1 ��� ���������� 2
            if (M && N){
                Arr3D = define_matrix(P, M, N, 1);
                for (int i = 0; i < MEASUREMENTS; i++){
                    fill_matrix(P, M, N, Arr3D, 2, 1);
                    Res[i] = Insert3(P, M, N, Arr3D);
                }
                measurements[1] = MeasurementProcessing(Res);
                free_memory(P, M, N, Arr3D, 1);
            } else {
                Vector = CreateVector(P, 1);
                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 2, 1);
                    Res[i] = Insert3_Arr1D(Vector, P);
                }
                measurements[1] = MeasurementProcessing(Res);

                free(Vector);
            }
            break;

        case 3: // �������� 1 ��� ���������� 3
            if (M && N){
                Arr3D = define_matrix(P, M, N, 1);

                for (int i = 0; i < MEASUREMENTS; i++){
                    fill_matrix(P, M, N, Arr3D, 3, 1);
                    Res[i] = Insert3(P, M, N, Arr3D);
                }
                measurements[2] = MeasurementProcessing(Res);

                free_memory(P, M, N, Arr3D, 1);
            } else {
                Vector = CreateVector(P, 1);
                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 3, 1);
                    Res[i] = Insert3_Arr1D(Vector, P);
                }
                measurements[2] = MeasurementProcessing(Res);

                free(Vector);
            }
            break;
        
        case 4: // �������� 1 �� ���� ����������

            if (M && N){

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

            } else {
                Vector = CreateVector(P, 1);
                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 1, 1);
                    Res[i] = Insert3_Arr1D(Vector, P);
                }
                measurements[0] = MeasurementProcessing(Res);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 2, 1);
                    Res[i] = Insert3_Arr1D(Vector, P);
                }
                measurements[1] = MeasurementProcessing(Res);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 3, 1);
                    Res[i] = Insert3_Arr1D(Vector, P);
                }
                measurements[2] = MeasurementProcessing(Res);

                free(Vector);
            }


            break;

        case 5: // �������� 2 ��� ���������� 1

            if (M && N){

                Arr3D = define_matrix(P, M, N, 0);

                for (int i = 0; i < MEASUREMENTS; i++){
                    fill_matrix(P, M, N, Arr3D, 1, 0);
                    Res[i] = Select6(P, M, N, Arr3D);
                }
                measurements[3] = MeasurementProcessing(Res);

                free_memory(P, M, N, Arr3D, 0);

            } else {
                Vector = CreateVector(P, 0);
                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 1, 0);
                    Res[i] = Select6_Arr1D(Vector, P);
                }
                measurements[3] = MeasurementProcessing(Res);
                
                free(Vector);
            }   

            break;

        case 6: // �������� 2 ��� ���������� 2
            if (M && N){
                Arr3D = define_matrix(P, M, N, 0);

                for (int i = 0; i < MEASUREMENTS; i++){
                    fill_matrix(P, M, N, Arr3D, 2, 0);
                    Res[i] = Select6(P, M, N, Arr3D);
                }
                measurements[4] = MeasurementProcessing(Res);

                free_memory(P, M, N, Arr3D, 0);
            } else {
                Vector = CreateVector(P, 0);
                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 2, 0);
                    Res[i] = Select6_Arr1D(Vector, P);
                }
                measurements[4] = MeasurementProcessing(Res);

                free(Vector);
            }   
            break;

        case 7: // �������� 2 ��� ���������� 3
            if (M && N){
                Arr3D = define_matrix(P, M, N, 0);

                for (int i = 0; i < MEASUREMENTS; i++){
                    fill_matrix(P, M, N, Arr3D, 3, 0);
                    Res[i] = Select6(P, M, N, Arr3D);
                }
                measurements[5] = MeasurementProcessing(Res);

                free_memory(P, M, N, Arr3D, 0);
                
            } else {

                Vector = CreateVector(P, 0);
                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 3, 0);
                    Res[i] = Select6_Arr1D(Vector, P);
                }
                measurements[5] = MeasurementProcessing(Res);

                free(Vector);
            }  
            break;
        
        case 8: // �������� 2 �� ���� ����������
            if (M && N){
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

            } else {
                Vector = CreateVector(P, 0);
                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 1, 0);
                    Res[i] = Select6_Arr1D(Vector, P);
                }
                measurements[3] = MeasurementProcessing(Res);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 2, 0);
                    Res[i] = Select6_Arr1D(Vector, P);
                }
                measurements[4] = MeasurementProcessing(Res);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 3, 0);
                    Res[i] = Select6_Arr1D(Vector, P);
                }
                measurements[5] = MeasurementProcessing(Res);

                free(Vector);
            }

            break;
        
        case 9: // �������� 3 ��� ���������� 1
            if (M && N){

                Arr3D = define_matrix(P, M, N, 0);

                measurements[6] = MeasurementProcessing(
                QuickSortMeasurement(P, M, N, Arr3D, Res, 1)
                );

                free_memory(P, M, N, Arr3D, 0);

            } else {
                Vector = CreateVector(P, 0);
                measurements[6] =  MeasurementProcessing(
                QuickSortMeasurement_Arr1D(P, Res, 1, 0, Vector)
                );
                free(Vector);
            }
            break;

        case 10: // �������� 3 ��� ���������� 2
            if (M && N){

                Arr3D = define_matrix(P, M, N, 0);

                measurements[7] = MeasurementProcessing(
                QuickSortMeasurement(P, M, N, Arr3D, Res, 2)
                );
                
                free_memory(P, M, N, Arr3D, 0);

            } else {
                Vector = CreateVector(P, 0);
                measurements[7] = MeasurementProcessing(
                QuickSortMeasurement_Arr1D(P, Res, 2, 0, Vector)
                );
                
                free(Vector);
            }
            break;
        
        case 11: // �������� 3 ��� ���������� 3
            if (M && N){
                Arr3D = define_matrix(P, M, N, 0);
        
                measurements[8] = MeasurementProcessing(
                QuickSortMeasurement(P, M, N, Arr3D, Res, 3)
                );

                free_memory(P, M, N, Arr3D, 0);

            } else {
                Vector = CreateVector(P, 0);
                measurements[8] = MeasurementProcessing(
                QuickSortMeasurement_Arr1D(P, Res, 3, 0, Vector)
                );
                free(Vector);
            }


            break;

        case 12: // �������� 3 �� ���� ����������
            if (M && N){
                Arr3D = define_matrix(P, M, N, 0);

                fill_matrix(P, M, N, Arr3D, 1, 0);
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

            } else {

                Vector = CreateVector(P, 0);

                measurements[6] = MeasurementProcessing(
                QuickSortMeasurement_Arr1D(P, Res, 1, 0, Vector)
                );

                measurements[7] = MeasurementProcessing(
                QuickSortMeasurement_Arr1D(P, Res, 2, 0, Vector)
                );

                measurements[8] = MeasurementProcessing(
                QuickSortMeasurement_Arr1D(P, Res, 3, 0, Vector)
                );
                
                free(Vector);

            }
            break;

        case 13: // �� ���������, ��� ���������� 1
            if (M && N){
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
            }
            else {

                Vector = CreateVector(P, 1);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 1, 1);
                    Res[i] = Insert3_Arr1D(Vector, P);
                }
                measurements[0] = MeasurementProcessing(Res);

                free(Vector);

                Vector = CreateVector(P, 0);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 1, 0);
                    Res[i] = Insert3_Arr1D(Vector, P);
                }
                measurements[3] = MeasurementProcessing(Res);

                measurements[6] = MeasurementProcessing(
                QuickSortMeasurement_Arr1D(P, Res, 1, 0, Vector)
                );

                free(Vector);
            }   

            break;

        case 14: // �� ���������, ��� ���������� 2
            if (M && N){
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

            } else {
                
                Vector = CreateVector(P, 1);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 2, 1);
                    Res[i] = Insert3_Arr1D(Vector, P);
                }
                measurements[1] = MeasurementProcessing(Res);

                free(Vector);

                Vector = CreateVector(P, 0);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 2, 0);
                    Res[i] = Insert3_Arr1D(Vector, P);
                }
                measurements[4] = MeasurementProcessing(Res);

                measurements[7] = MeasurementProcessing(
                QuickSortMeasurement_Arr1D(P, Res, 2, 0, Vector)
                );

                free(Vector);
     
            }   

            break;

        case 15: // �� ���������, ��� ���������� 3
            if (M && N){
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

            } else {
                
                Vector = CreateVector(P, 1);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 3, 1);
                    Res[i] = Insert3_Arr1D(Vector, P);
                }
                measurements[2] = MeasurementProcessing(Res);

                free(Vector);

                Vector = CreateVector(P, 0);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 3, 0);
                    Res[i] = Insert3_Arr1D(Vector, P);
                }
                measurements[5] = MeasurementProcessing(Res);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 3, 0);
                    Res[i] = Select6_Arr1D(Vector, P);
                }
                measurements[8] = MeasurementProcessing(
                QuickSortMeasurement_Arr1D(P, Res, 3, 0, Vector)
                );

                free(Vector);
            }   

            break;

        case 16: // �� ���������, �� ���� ����������
            if (M && N){
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
            
            } 
            else{
                
                Vector = CreateVector(P, 1);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 1, 1);
                    Res[i] = Insert3_Arr1D(Vector, P);
                }
                measurements[0] = MeasurementProcessing(Res);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 2, 1);
                    Res[i] = Insert3_Arr1D(Vector, P);
                }
                measurements[1] = MeasurementProcessing(Res);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 3, 1);
                    Res[i] = Insert3_Arr1D(Vector, P);
                }
                measurements[2] = MeasurementProcessing(Res);

                free(Vector);

                Vector = CreateVector(P, 0);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 1, 0);;
                    Res[i] = Select6_Arr1D(Vector, P);
                }
                measurements[3] = MeasurementProcessing(Res);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 2, 0);;
                    Res[i] = Select6_Arr1D(Vector, P);
                }
                measurements[4] = MeasurementProcessing(Res);

                for (int i = 0; i < MEASUREMENTS; i++){
                    FillVector(P, Vector, 3, 0);
                    Res[i] = Select6_Arr1D(Vector, P);
                }
                measurements[5] = MeasurementProcessing(Res);

                measurements[6] = MeasurementProcessing(
                QuickSortMeasurement_Arr1D(P, Res, 1, 0, Vector)
                );

                measurements[7] = MeasurementProcessing(
                QuickSortMeasurement_Arr1D(P, Res, 2, 0, Vector)
                );

                measurements[8] = MeasurementProcessing(
                QuickSortMeasurement_Arr1D(P, Res, 3, 0, Vector)
                );

                free(Vector);
            }

            break;

        default:
            break;
        }
        
        OutTable(measurements); // ���� ������� � ������

    }
    
    char c = getchar();

    return 0;
}