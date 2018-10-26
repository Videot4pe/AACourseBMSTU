//
//  levenstein_recurs.cpp
//  lab1AA
//
//  Created by Garanya Kvasnikov on 22.09.2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#include "levenstein_recurs.hpp"

int levenshtein_recurs(std::string s1, std::string s2)
{
    int sizeS1 = s1.length();
    int sizeS2 = s2.length();
    int cost = 0;
    if (sizeS1 == 0) {
        return sizeS2;
    }
    if (sizeS2 == 0) {
        return sizeS1;
    }
    
    cost = s1[0] == s2[0] ? 0 : 1;
    
    int result = std::min(std::min(levenshtein_recurs(s1.substr(1, sizeS1), s2) + 1, levenshtein_recurs(s1, s2.substr(1, sizeS2)) + 1), levenshtein_recurs(s1.substr(1, sizeS1), s2.substr(1, sizeS2)) + cost);
    
    return result;
}
