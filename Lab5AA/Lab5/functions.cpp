//
//  functions.cpp
//  lab2
//
//  Created by Garanya Kvasnikov on 30/11/2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#include "functions.hpp"

int** alloc_int_matrix(int n, int m)
{
    int **data = (int**)calloc(n * sizeof(int*) + n * m, sizeof(int));
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
    m = n;
    *row = n;
    *column = m;
    
    int** matrix = alloc_int_matrix(n, m);
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (!fscanf(f, "%d", &matrix[i][j]))
                return NULL;
        }
    
    fclose(f);
    return matrix;
}

void print_int_matrix(int row, int coloumn, int** matrix)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < coloumn; j++)
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
    //scanf("%d", &m);
    m = n;
    *row = n;
    *column = m;
    
    int** matrix = alloc_int_matrix(n, m);
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] = rand() & 1;
        }
    return matrix;
}

void winograd(int** A, int n, int m, int** B, int q, int** result)
{
    auto begin = std::chrono::steady_clock::now();

    // row factor A
    int row_factor[n];
    
    for (int i = 0; i < n; i++)
    {
        row_factor[i] = A[i][0] * A[i][1];
        for (int j = 1; j < m/2; j++)
            row_factor[i] = row_factor[i] + A[i][2*j] * A[i][2*j+1];
    }

    // column factor B
    int col_factor[q];
    
    for (int i = 0; i < q; i++)
    {
        col_factor[i] = B[0][i] * B[1][i];
        for (int j = 1; j < m/2; j++)
            col_factor[i] = col_factor[i] + B[2*j][i] * B[2*j+1][i];
    }

    //multiplying
    for (int i = 0; i < n; i++)
        for (int j = 0; j < q; j++)
        {
            result[i][j] = -(row_factor[i] + col_factor[j]);
            for (int k = 0; k < m/2; ++k)
            {
                result[i][j] = result[i][j] + (A[i][2*k] + B[2*k+1][j]) * (A[i][2*k+1] + B[2*k][j]);
            }
        }
    
    // if odd m
    if (m%2 != 0)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < q; j++)
            {
                result[i][j] += A[i][m-1] * B[m-1][j];
            }
    }
    
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "Время работы последовательного алгоритма: " << elapsed_ms.count() << "мс\n";
}

void winogradParallel(int** A, int n, int m, int** B, int q, int** result, int quantity)
{
    auto begin = std::chrono::steady_clock::now();
    
    std::vector <std::thread> threadVector;

    double rowFactorThreadSize =  (double)((double)n / (double)quantity);
    int minRow = 0;
    
    int *rowFactor = (int*)malloc(n * sizeof(int*));
    int *columnFactor = (int*)malloc(q * sizeof(int*));

    for (int i = 0; i < quantity; i++, minRow += rowFactorThreadSize) {
        threadVector.push_back(std::thread(countRowFactor, A, minRow, n, q, rowFactorThreadSize, rowFactor));
    }
    
    for (int i = 0; i < threadVector.size(); i++) {
        if (threadVector[i].joinable())
            threadVector[i].join();
    }
    threadVector.clear();
    //проверка join
    
    double columnFactorThreadSize = (double)((double)q / (double)quantity);
    int minColumn = 0;
    for (int i = 0; i < quantity; i++, minColumn += columnFactorThreadSize) {
        threadVector.push_back(std::thread(countColumnFactor, B, minColumn, n, q, columnFactorThreadSize, columnFactor));
    }
    for (int i = 0; i < threadVector.size(); i++) {
        if (threadVector[i].joinable())
            threadVector[i].join();
    }
    threadVector.clear();

    double rowByThread = (double)((double)n / (double)quantity);
    minRow = 0;
    for (int i = 0; i < quantity; i++, minRow += rowByThread) {
        threadVector.push_back(std::thread(partialVinograd, A, B, minRow, rowByThread, n, q, rowFactor, columnFactor, result));
    }
    for (int i = 0; i < threadVector.size(); i++) {
        threadVector[i].join();
    }
    threadVector.clear();

    if (q % 2 != 0) {
        minRow = 0;
        for (int i = 0; i < quantity; i++, minRow += rowByThread) {
            threadVector.push_back(std::thread(unevenPartialVinograd, A, B, minRow, rowByThread, n, q, rowFactor, columnFactor, result));
        }
        for (int i = 0; i < threadVector.size(); i++) {
            threadVector[i].join();
        }
    }
    threadVector.clear();
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "Время работы параллельного алгоритма при " << quantity << " потоках (такты): " << elapsed_ms.count() << "мс\n";
}

void unevenPartialVinograd(int** A, int** B, int minRow, double rowByThread, int n, int m, int *rowFactor, int *columnFactor, int **result)
{
    double maxRow = (double)minRow + rowByThread;
    if (maxRow > n) {
        maxRow = n;
    }
    if (m%2 != 0)
    {
        for (int i = minRow; i < maxRow; i++)
            for (int j = 0; j < m; j++)
            {
                result[i][j] += A[i][m-1] * B[m-1][j];
            }
    }
}

void partialVinograd(int** A, int** B, int minRow, double rowByThread, int n, int m, int *row_factor, int *column_factor, int **result)
{
    double maxRow = (double)minRow + rowByThread;
    if (maxRow > n) {
        maxRow = n;
    }
    for (int i = minRow; i < maxRow; i++)
        for (int j = 0; j < m; j++)
        {
            result[i][j] = -(row_factor[i] + column_factor[j]);
            for (int k = 0; k < m/2; ++k)
            {
                result[i][j] = result[i][j] + (A[i][2*k] + B[2*k+1][j]) * (A[i][2*k+1] + B[2*k][j]);
            }
            //printf("\n");
        }
}
                               
void countRowFactor(int** A, int minRow, int n, int m, double rowFactorThreadSize, int *row_factor)
{
    double maxRow = (double)minRow + rowFactorThreadSize;
    if (maxRow > n) {
        maxRow = n;
    }
    for (int i = minRow; i < maxRow; i++)
    {
        row_factor[i] = A[i][0] * A[i][1];
        for (int j = 1; j < m/2; j++)
            row_factor[i] = row_factor[i] + A[i][2*j] * A[i][2*j+1];
    }
}

void countColumnFactor(int** A, int minColumn, int n, int m, double columnFactorThreadSize, int *column_factor)
{
    double maxColumn = (double)minColumn + columnFactorThreadSize;
    if (maxColumn > m) {
        maxColumn = m;
    }
    for (int i = minColumn; i < maxColumn; i++)
    {
        column_factor[i] = A[i][0] * A[i][1];
        for (int j = 1; j < m/2; j++)
            column_factor[i] = column_factor[i] + A[i][2*j] * A[i][2*j+1];
    }
}
