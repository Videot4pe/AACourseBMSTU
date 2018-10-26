//
//  test.hpp
//  lab1AA
//
//  Created by Garanya Kvasnikov on 22.09.2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#ifndef test_hpp
#define test_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "levenstein.hpp"
#include "levenstein_recurs.hpp"
#include "generate_string.hpp"
#include "damerau_levenshtein.hpp"

void print_result(std::string s1, std::string s2, int number, int result, unsigned int time, std::string alg);
void test_levenstein_distance();

#endif /* test_hpp */
