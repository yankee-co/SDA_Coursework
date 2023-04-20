#include <stdio.h>
#include <windows.h>
#include <time.h>

int * menu(){

    void restart(){
        system("cls");
        printf("Попадаєте не по тим клавішам ? Спробуйте знову.");
        Sleep(2500);
        system("cls");
        menu();
    }

    int algorithm_number, sort_type; // Числа що відповідають за формування варіанту виконання програми на основі їх значень
    int counter = 1;
    int data[2], choice_matrix[4][4]; // Порядкові номера всіх можливих варінтів вибору складають матрицю (кількість алгоритмів) * (кількість типів сортування)

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

    printf("\n\nВведіть значення розмірності матриці (P, M, N): ");
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

    // Таск
    // 5. Впорядкувати тривимірний масив Аrr3D [P,M,N] таким чи-
    // ном: переставити перерізи масива за незменшенням сум їх
    // елементів.

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int choice = menu(); // Вибір варіанту виконання програми 1-16 всі можливі випадки

    switch (choice[0])
    {
    case 1: // Алгоритм 1 Тип сортування 1
        /* code */
        break;
     
    case 2: // Алгоритм 1 Тип сортування 2
        /* code */ 
        break;

    case 3: // Алгоритм 1 Тип сортування 3
        /* code */
        break;
    
    case 4: // Алгоритм 1 Тип сортування 4 (всі типи сортування)
        /* code */
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
// { for (int i=0; i<M; i++)з
// free(Arr3D[k][i]);
// free(Arr3D[k]);
// }
// free(Arr3D);