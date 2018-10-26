//
//  main.cpp
//  lab2
//
//  Created by Garanya Kvasnikov on 20/10/2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#include "functions.h"
#include <time.h>

int main(int argc, const char * argv[]) {
    int alg = 0;
    
    int h;
    printf("Выберите алгоритм: 0 - базовый, 1 - Винограда, 2 - улучшенный Винограда\n");
    scanf("%d", &h);
        switch (h)
    {
        case '0': if (argc < 3) printf("Используется Базовый алгоритм \n");
            alg = 0;
            break;
        case '1': if (argc < 3) printf("Используется алгоритм Винограда\n");
            alg = 1;
            break;
        case '2': if (argc < 3) printf("Используется улучшенный алгоритм Винограда\n");
            alg = 2;
            break;
    }
    
    int a_row, a_col;
    //int** a = read_int_matrix("/Users/garanya/Downloads/lab2 2/input1.txt", &a_row, &a_col);
    int** a = generate_matrix(&a_row, &a_col);
    
    int b_row, b_col;
    //int** b = read_int_matrix("/Users/garanya/Downloads/lab2 2/input2.txt", &b_row, &b_col);
    int** b = generate_matrix(&b_row, &b_col);

    int** result = alloc_int_matrix(a_row, b_col);
    
    void ((*algs[3]))() = {&classic, &winograd, &winograd_plus};
    
    clock_t alg_time = clock();
    algs[alg](a, a_row, a_col, b, b_col, result);
    alg_time = clock() - alg_time;
    
    // print matrices
    if (argc > 2 && argv[2][0] == 's')
    {
        printf("%lu\n", alg_time);
    }
    else
    {
        printf("\nМатрица 1:\n");
        print_int_matrix(a_row, a_col, a);
        printf("\nМатрица 2:\n");
        print_int_matrix(b_row, b_col, b);
        printf("\nРезультат:\n");
        print_int_matrix(a_row, b_col, result);
        printf("Время работы алгоритма (такты): %lu\n", alg_time);
        printf("%c\n", argv[2][0]);
    }
    
    
    return 0;
}
