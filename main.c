#include <stdio.h>
#include <windows.h>
#include <time.h>

int * menu(){

    void restart(){
        system("cls");
        printf("�������� �� �� ��� ������� ? ��������� �����.");
        Sleep(2500);
        system("cls");
        menu();
    }

    int algorithm_number, sort_type; // ����� �� ���������� �� ���������� ������� ��������� �������� �� ����� �� �������
    int counter = 1;
    int data[2], choice_matrix[4][4]; // �������� ������ ��� �������� ������ ������ ��������� ������� (������� ���������) * (������� ���� ����������)

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

    printf("\n\n������ �������� ��������� ������� (P, M, N): ");
    scanf("%d, %d, %d", &P, &M, &N);

    data[0] = choice_matrix[algorithm_number - 1][sort_type - 1];
    data[1] = P;
    data[2] = M;
    data[3] = N;
    return data;
}

void define_matrix(){
    int ***Arr3D;
    Arr3D = (int***) malloc(P * sizeof(int**));
    for (int k = 0; k < P; k++){
        Arr3D[k] = (int**) malloc(M * sizeof(int*));
        for (int i = 0; i < M; i++)
            Arr3D[k][i] = (int*) malloc(N * sizeof(int));
    }
}

int main(){

    // ����
    // 5. ������������ ���������� ����� �rr3D [P,M,N] ����� ��-
    // ���: ����������� ������� ������ �� ������������ ��� ��
    // ��������.

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int choice = menu(); // ���� ������� ��������� �������� 1-16 �� ������ �������

    switch (choice[0])
    {
    case 1: // �������� 1 ��� ���������� 1
        /* code */
        break;
     
    case 2: // �������� 1 ��� ���������� 2
        /* code */ 
        break;

    case 3: // �������� 1 ��� ���������� 3
        /* code */
        break;
    
    case 4: // �������� 1 ��� ���������� 4 (�� ���� ����������)
        /* code */
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

    return 0;
}

// int ***Arr3D;
// Arr3D = (int***) malloc(P*sizeof(int**));
// for (int k=0; k<P; k++)
// { Arr3D[k] = (int**) malloc(M*sizeof(int*));
// for (int i=0; i<M; i++)
// Arr3D[k][i] = (int*) malloc(N*sizeof(int));
// }

// for (int k=0; k<P; k++)
// { for (int i=0; i<M; i++)�
// free(Arr3D[k][i]);
// free(Arr3D[k]);
// }
// free(Arr3D);