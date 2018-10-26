//
//  main.cpp
//  lab4
//
//  Created by Garanya Kvasnikov on 22/10/2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#include <stdio.h>
#include <time.h>
typedef int bool;
#define true 1
#define false 0

void swap (int *i, int *j)
{
    int *k = i;
    i = j;
    j = k;
}
void bubblesort(int* l, int* r) {
    int sz = r - l;
    if (sz <= 1) return;
    bool b = true;
    while (b) {
        b = false;
        for (int* i = l; i + 1 < r; i++) {
            if (*i > *(i + 1)) {
                swap(*i, *(i + 1));
                b = true;
            }
        }
        r--;
    }
}

void selectionsort(int* l, int* r) {
    for (int *i = l; i < r; i++) {
        int minz = *i, *ind = i;
        for (int *j = i + 1; j < r; j++) {
            if (*j < minz) minz = *j, ind = j;
        }
        swap(*i, *ind);
    }
}

void shellsort(int* l, int* r) {
    int sz = r - l;
    int step = sz / 2;
    while (step >= 1) {
        for (int *i = l + step; i < r; i++) {
            int *j = i;
            int *diff = j - step;
            while (diff >= l && *diff > *j) {
                swap(*diff, *j);
                j = diff;
                diff = j - step;
            }
        }
        step /= 2;
    }
}

int main(int argc, const char * argv[]) {
    unsigned int start_time = clock();
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    
    printf("\n\n Bubble\n");
    for (int i = 1000; i < 10000; i = i + 1000)
    {
        int a[i];
        int k = 0;
        for (int j = 0; i < i; j++)
            a[j] = j;

        start_time = clock();
        bubblesort(a, a+i);
        end_time = clock();
        search_time = end_time - start_time;
        printf("Лучший случай: %d для %d\n", search_time/18, i);
        
        for (int j = i; j > 0; j--)
        {
            a[k] = j;
            k++;
        }
        start_time = clock();
        bubblesort(a, a+i);
        end_time = clock();
        search_time = end_time - start_time;
        printf("Худший случай: %d для %d\n", search_time/18, i);
    }
    printf("\n\n Selection\n");
    for (int i = 1000; i < 10000; i = i + 1000)
    {
        int a[i];
        int k = 0;
        for (int j = 0; i < i; j++)
            a[j] = j;
        
        start_time = clock();
        selectionsort(a, a+i);
        end_time = clock();
        search_time = end_time - start_time;
        printf("Лучший случай: %d для %d\n", search_time/18, i);
        
        for (int j = i; j > 0; j--)
        {
            a[k] = j;
            k++;
        }
        start_time = clock();
        selectionsort(a, a+i);
        end_time = clock();
        search_time = end_time - start_time;
        printf("Худший случай: %d для %d\n", search_time/18, i);
    }
    printf("\n\n Shell\n");
    for (int i = 1000; i < 10000; i = i + 1000)
    {
        int a[i];
        int k = 0;
        for (int j = 0; i < i; j++)
            a[j] = j;
        
        start_time = clock();
        shellsort(a, a+i);
        end_time = clock();
        search_time = end_time - start_time;
        printf("Лучший случай: %d для %d\n", search_time/18, i);
        
        for (int j = i; j > 0; j--)
        {
            a[k] = j;
            k++;
        }
        start_time = clock();
        shellsort(a, a+i);
        end_time = clock();
        search_time = end_time - start_time;
        printf("Худший случай: %d для %d\n", search_time/18, i);
    }
    int a[10000];
    for (int i = 0; i < 10000; i++)
        a[i] = rand() % 5;
    
    printf("\n\n");
    start_time = clock();
    bubblesort(a, a+1000);
    end_time = clock();
    search_time = end_time - start_time;

    printf("%d", search_time/18);
    printf("\n");
    for (int i = 0; i < 1000; i++)
        a[i] = rand() % 5;
    start_time = clock();
    selectionsort(a, a+1000);
    end_time = clock();
    search_time = end_time - start_time;

    printf("%d", search_time/18);
    printf("\n");
    for (int i = 0; i < 1000; i++)
        a[i] = rand() % 5;
    start_time = clock();
    shellsort(a, a+1000);
    end_time = clock();
    search_time = end_time - start_time;

    printf("%d", search_time/18);
    printf("\n\n");

    int b[4000];
    for (int i = 0; i < 4000; i++)
        b[i] = rand() % 5;

    start_time = clock();
    bubblesort(b, b+4000);
    end_time = clock();
    search_time = end_time - start_time;

    printf("%d", search_time/18);
    printf("\n");
    for (int i = 0; i < 4000; i++)
        b[i] = rand() % 5;
    start_time = clock();
    selectionsort(b, b+4000);
    end_time = clock();
    search_time = end_time - start_time;

    printf("%d", search_time/18);
    printf("\n");
    for (int i = 0; i < 4000; i++)
        b[i] = rand() % 5;
    start_time = clock();
    shellsort(b, b+4000);
    end_time = clock();
    search_time = end_time - start_time;

    printf("%d", search_time/18);
    printf("\n\n");

    int c[8000];
    for (int i = 0; i < 8000; i++)
        c[i] = rand() % 5;

    start_time = clock();
    bubblesort(c, c+8000);
    end_time = clock();
    search_time = end_time - start_time;

    printf("%d", search_time/18);
    printf("\n");
    for (int i = 0; i < 8000; i++)
        c[i] = rand() % 5;
    start_time = clock();
    selectionsort(c, c+8000);
    end_time = clock();
    search_time = end_time - start_time;

    printf("%d", search_time/18);
    printf("\n");
    for (int i = 0; i < 8000; i++)
        c[i] = rand() % 5;
    start_time = clock();
    shellsort(c, c+8000);
    end_time = clock();
    search_time = end_time - start_time;

    printf("%d", search_time/18);
    printf("\n\n");

    int d[10000];
    for (int i = 0; i < 10000; i++)
        d[i] = rand() % 5;

    start_time = clock();
    bubblesort(d, d+10000);
    end_time = clock();
    search_time = end_time - start_time;

    printf("%d", search_time/18);
    printf("\n");
    for (int i = 0; i < 10000; i++)
        d[i] = rand() % 5;
    start_time = clock();
    selectionsort(d, d+10000);
    end_time = clock();
    search_time = end_time - start_time;

    printf("%d", search_time/18);
    printf("\n");
    for (int i = 0; i < 10000; i++)
        d[i] = rand() % 5;
    start_time = clock();
    shellsort(d, d+10000);
    end_time = clock();
    search_time = end_time - start_time;

    printf("%d", search_time/18);
    printf("\n\n");

    return 0;
}

