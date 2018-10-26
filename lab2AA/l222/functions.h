//
//  functions.hpp
//  lab2
//
//  Created by Garanya Kvasnikov on 20/10/2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#ifndef functions_hpp
#define functions_hpp

#include <stdio.h>
int** alloc_int_matrix(int n, int m);
int** read_int_matrix(char const* filename, int* row, int* column);
void print_int_matrix(int row, int coloumn, int** matrix);
int** generate_matrix(int* row, int* column);
void classic(int** A, int n, int m, int** B, int q, int** result);
void winograd(int** A, int n, int m, int** B, int q, int** result);
void winograd_plus(int** A, int n, int m, int** B, int q, int** result);

#endif /* functions_hpp */
