//
//  main.cpp
//  lab1AA
//
//  Created by Garanya Kvasnikov on 22.09.2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "test.hpp"
#include "levenstein.hpp"
#include "levenstein_recurs.hpp"


int main(int argc, const char * argv[]) {
    
    test_levenstein_distance();

//    std::string s1;
//    std::cin >> s1;
//    std::string s2;
//    std::cin >> s2;
//
//    int result = levenshtein_distance(s1, s2);
//    std::cout << result;
//
//    result = damerau_levenshtein(s1, s2);
//    std::cout << result;
//
//    result = levenshtein_recurs(s1, s2);
//    std::cout << result;
    
    return 0;
}
