//
//  generate_string.cpp
//  lab1AA
//
//  Created by Garanya Kvasnikov on 22.09.2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#include "generate_string.hpp"

char getRandomChar()
{
    char c = 'a' + rand()%24;
    return c;
}

std::string generate(int length)
{
    std::string s(length, 'a');
    for (int i = 0; i < length; i++)
        s[i] =  getRandomChar();
    return s;
}
