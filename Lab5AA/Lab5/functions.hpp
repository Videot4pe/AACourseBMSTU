//
//  functions.hpp
//  lab2
//
//  Created by Garanya Kvasnikov on 30/11/2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#ifndef functions_hpp
#define functions_hpp

#include <stdio.h>
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <chrono>

int** alloc_int_matrix(int n, int m);
int** read_int_matrix(char const* filename, int* row, int* column);
void print_int_matrix(int row, int coloumn, int** matrix);
int** generate_matrix(int* row, int* column);
void classic(int** A, int n, int m, int** B, int q, int** result);
void winograd(int** A, int n, int m, int** B, int q, int** result);

void winogradParallel(int** A, int n, int m, int** B, int q, int** result, int quantity);
void countRowFactor(int** A, int minRow, int n, int m, double rowFactorThreadSize, int *row_factor);
void countColumnFactor(int** A, int minColumn, int n, int m, double columnFactorThreadSize, int *row_factor);
void partialVinograd(int** A, int** B, int minRow, double rowByThread, int n, int m, int *rowFactor, int *columnFactor, int **result);
void unevenPartialVinograd(int** A, int** B, int minRow, double rowByThread, int n, int m, int *rowFactor, int *columnFactor, int **result);

void printSth();

#endif /* functions_hpp */
