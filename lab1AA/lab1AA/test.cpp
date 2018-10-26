//
//  test.cpp
//  lab1AA
//
//  Created by Garanya Kvasnikov on 22.09.2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#include "test.hpp"

void print_result(std::string s1, std::string s2, int number, int result, unsigned int time, std::string alg)
{
    std::cout << "Test №" << number << ": \n" << "Algorhytm: " << alg << "\nFirst string: " << s1 << '\n' << "Second string: " << s2 << '\n' << "Result: " << result << '\n' << "Time of work: " << time << '\n' << std::endl;
}

void test_levenstein_distance()
{
    std::string s1;
    std::string s2;
    int result = 0;
    unsigned int start_time =  clock();
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    std::string alg1 = "Levenshtein";
    std::string alg2 = "Levenshtein recurs";
    std::string alg3 = "Damerau-Levenshtein";

    //------------Case 1
    
    s1 = generate(4);
    s2 = generate(3);
    start_time = clock();
    result = levenshtein_distance(s1, s2);
    end_time = clock();
    search_time = end_time - start_time;
    print_result(s1, s2, 1, result, search_time, alg1);
    
    start_time = clock();
    result = damerau_levenshtein(s1, s2);
    end_time = clock();
    search_time = end_time - start_time;
    print_result(s1, s2, 1, result, search_time, alg3);
    
    start_time = clock();
    result = levenshtein_recurs(s1, s2);
    end_time = clock();
    search_time = end_time - start_time;
    print_result(s1, s2, 1, result, search_time, alg2);
    
    //------------Case 2

    s1 = generate(5);
    s2 = generate(5);
    start_time = clock();
    result = levenshtein_distance(s1, s2);
    end_time = clock();
    search_time = end_time - start_time;
    print_result(s1, s2, 2, result, search_time, alg1);
    
    start_time = clock();
    result = damerau_levenshtein(s1, s2);
    end_time = clock();
    search_time = end_time - start_time;
    print_result(s1, s2, 2, result, search_time, alg3);
    
    start_time = clock();
    result = levenshtein_recurs(s1, s2);
    end_time = clock();
    search_time = end_time - start_time;
    print_result(s1, s2, 2, result, search_time, alg2);
    
    //------------Case 3

    s1 = generate(8);
    s2 = generate(7);
    start_time = clock();
    result = levenshtein_distance(s1, s2);
    end_time = clock();
    search_time = end_time - start_time;
    print_result(s1, s2, 3, result, search_time, alg1);
    
    start_time = clock();
    result = damerau_levenshtein(s1, s2);
    end_time = clock();
    search_time = end_time - start_time;
    print_result(s1, s2, 3, result, search_time, alg3);
    
    start_time = clock();
    result = levenshtein_recurs(s1, s2);
    end_time = clock();
    search_time = end_time - start_time;
    print_result(s1, s2, 3, result, search_time, alg2);
    
    //------------Case 4

    s1 = generate(10);
    s2 = generate(10);
    start_time = clock();
    result = levenshtein_distance(s1, s2);
    end_time = clock();
    search_time = end_time - start_time;
    print_result(s1, s2, 4, result, search_time, alg1);
    
    start_time = clock();
    result = damerau_levenshtein(s1, s2);
    end_time = clock();
    search_time = end_time - start_time;
    print_result(s1, s2, 4, result, search_time, alg3);
    
    start_time = clock();
    result = levenshtein_recurs(s1, s2);
    end_time = clock();
    search_time = end_time - start_time;
    print_result(s1, s2, 4, result, search_time, alg2);
    
    //------------Case 5

    s1 = generate(15);
    s2 = generate(10);
    start_time = clock();
    result = levenshtein_distance(s1, s2);
    end_time = clock();
    search_time = end_time - start_time;
    print_result(s1, s2, 5, result, search_time, alg1);

    start_time = clock();
    result = damerau_levenshtein(s1, s2);
    end_time = clock();
    search_time = end_time - start_time;
    print_result(s1, s2, 5, result, search_time, alg3);
    
    start_time = clock();
    result = levenshtein_recurs(s1, s2);
    end_time = clock();
    search_time = end_time - start_time;
    print_result(s1, s2, 5, result, search_time, alg2);
    
}
