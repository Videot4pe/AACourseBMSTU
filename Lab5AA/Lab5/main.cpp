//
//  main.cpp
//  lab2
//
//  Created by Garanya Kvasnikov on 30/11/2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#include "functions.hpp"
#include <time.h>

int main() {
    int a_row, a_col;
    int** a = generate_matrix(&a_row, &a_col);
    
    int b_row, b_col;
    int** b = generate_matrix(&b_row, &b_col);
    
    int** result = alloc_int_matrix(a_row, b_col);
    
    for (int i = 2; i < 11; i = i + 2)
    {
        winogradParallel(a, a_row, a_col, b, b_col, result, i);
        result = alloc_int_matrix(a_row, b_col);
    }

    std::cout << std::endl;
    winograd(a, a_row, a_col, b, b_col, result);

    return 0;
}
