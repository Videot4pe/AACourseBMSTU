//
//  levenstein.cpp
//  lab1AA
//
//  Created by Garanya Kvasnikov on 22.09.2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#include "levenstein.hpp"

int levenshtein_distance(std::string s1, std::string s2) {
    int sizeS1 = s1.length();
    int sizeS2 = s2.length();
    if (sizeS1 == 0) {
        return sizeS2;
    }
    if (sizeS2 == 0) {
        return sizeS1;
    }
    
    std::vector< std::vector<int>>matrix(sizeS1 + 1);
    for (int i = 0; i <= sizeS1; i++) {
        matrix[i].resize(sizeS2 + 1);
        matrix[i][0] = i;
    }
    for (int i = 0; i <= sizeS2; i++) {
        matrix[0][i] = i;
    }
    int turn = 0;
    for (int i = 1; i <= sizeS1; i++) {
        for(int j = 1; j <= sizeS2; j++) {
            turn = s1[i - 1] == s2[j - 1] ? 0 : 1;
            matrix[i][j] = std::min(std::min(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1), matrix[i - 1][j - 1] + turn);
        }
    }
    return matrix[sizeS1][sizeS2];
}
