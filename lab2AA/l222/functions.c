//
//  functions.cpp
//  lab2
//
//  Created by Garanya Kvasnikov on 20/10/2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#include "functions.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int** alloc_int_matrix(int n, int m)
{
    int **data = calloc(n * sizeof(int*) + n * m, sizeof(int));
    if (!data)
        return NULL;
    
    for(int i = 0; i < n; i++)
        data[i] = (int*)((char*) data + n * sizeof(int*) + i * m * sizeof(int));
    
    return data;
}

int** read_int_matrix(char const* filename, int* row, int* column)
{
    FILE* f = fopen(filename, "r");
    
    int n;
    int m;
    fscanf(f, "%d", &n);
    fscanf(f, "%d", &m);
    *row = n;
    *column = m;
    
    int** matrix = alloc_int_matrix(n, m);
    
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            if (!fscanf(f, "%d", &matrix[i][j]))
                return NULL;
        }
    
    fclose(f);
    return matrix;
}

void print_int_matrix(int row, int coloumn, int** matrix)
{
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < coloumn; ++j)
        {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int** generate_matrix(int* row, int* column)
{
    int n;
    int m;
    printf("Введите столбцы и строки: \n");
    scanf("%d", &n);
    scanf("%d", &m);
    *row = n;
    *column = m;
    
    int** matrix = alloc_int_matrix(n, m);
    
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            matrix[i][j] = rand() & 1;
        }
    return matrix;
}


void classic(int** A, int n, int m, int** B, int q, int** result)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < q; j++)
            for (int k = 0; k < m; k++)
                result[i][j] = result[i][j] + A[i][k] * B[k][j];
}

void winograd(int** A, int n, int m, int** B, int q, int** result)
{
    int d = m / 2;
    
    // row factor A
    int row_factor[n];
    
    for (int i = 0; i < n; ++i)
    {
        row_factor[i] = A[i][0] * A[i][1];
        for (int j = 1; j < m/2; ++j)
            row_factor[i] = row_factor[i] + A[i][2*j] * A[i][2*j+1];
    }
    
    // column factor B
    int col_factor[q];
    
    for (int i = 0; i < q; ++i)
    {
        col_factor[i] = B[0][i] * B[1][i];
        for (int j = 1; j < m/2; ++j)
            col_factor[i] = col_factor[i] + B[2*j][i] * B[2*j+1][i];
    };
    
    // multiplying
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < q; ++j)
        {
            result[i][j] = -(row_factor[i] + col_factor[j]);
            for (int k = 0; k < m/2; ++k)
            {
                result[i][j] = result[i][j] + \
                (A[i][2*k] + B[2*k+1][j]) * (A[i][2*k+1] + B[2*k][j]);
            }
            //printf("\n");
        }
    
    // if odd m
    if (m%2 != 0)
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < q; ++j)
            {
                result[i][j] += A[i][m-1] * B[m-1][j];
            }
    }
}

void winograd_plus(int** A, int n, int m, int** B, int q, int** result)
{
    int d = m / 2;
    int odd = m % 2 ? 1 : 0;
    
    // row factor A
    int row_factor[n];
    
    for (int i = 0; i < n; ++i)
    {
        row_factor[i] = 0;
        for (int j = 0; j < d; ++j)
            row_factor[i] += A[i][2*j] * A[i][2*j+1];
    }
    
    // column factor B
    int col_factor[q];
    
    for (int i = 0; i < q; ++i)
    {
        col_factor[i] = 0;
        for (int j = 0; j < d; ++j)
            col_factor[i] += B[2*j][i] * B[2*j+1][i];
    }
    
    int temp;
    
    // multiplying
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < q; ++j)
        {
            temp = odd ? A[i][m-1] * B[m-1][j] : 0;
            temp -= row_factor[i] + col_factor[j];
            
            for (int k = 0; k < d; ++k)
                temp +=  \
                (A[i][2*k] + B[2*k+1][j]) * (A[i][2*k+1] + B[2*k][j]);
            
            result[i][j] = temp;
        }
}
