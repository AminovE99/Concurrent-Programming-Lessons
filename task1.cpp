#include <iostream>
#include <stdio.h>
#include <omp.h>
#include "task4.h"

#define NUM_THREADS 8


void task1();

void task2();

void task3();

void task4();

int main() {
    //task1();
    //task2();
    //task3();
    task4();
}

void task4() {

}

void task3() {
    int a, b;
    printf("Print a: ");
    scanf("%d", &a);
    printf("\nPrint b: ");
    scanf("%d", &b);

    omp_set_num_threads(4);
#pragma omp parallel private(a) firstprivate(b)
    {
        int thread_num = omp_get_thread_num();
        a += omp_get_thread_num();
        b += omp_get_thread_num();
        printf("Number of thread inside: %d \n, a = %d; b = %d", thread_num, a, b);
    }
    printf(" Outside of block: a = %d; b = %d\n", a, b);
    omp_set_num_threads(2);
#pragma omp parallel shared(a) private(b)
    {
        int thread_num = omp_get_thread_num();
        a -= omp_get_thread_num();
        b -= omp_get_thread_num();
        printf("Inside second block %d Thread: a = %d, b = %d\n",thread_num,a,b);
    }
    printf("After second block: a= %d, b = %d", a,b);
}


void task2() {
    omp_set_dynamic(0);
    int NUMBER_OF_THREADS = 3; // you can
    printf("Print Number Of Threads: ");
    scanf("%d", &NUMBER_OF_THREADS);
    omp_set_num_threads(NUMBER_OF_THREADS);
#pragma omp parallel if (NUMBER_OF_THREADS > 1)
    if (NUMBER_OF_THREADS > 1) {
        printf("Thread number: %d of %d \n", omp_get_thread_num(), omp_get_num_threads() - 1);
    }
}

void task1() {
    omp_set_dynamic(0);// runtime won't adjust the number of threads
    omp_set_num_threads(NUM_THREADS); // set number of threads in task

#pragma omp parallel
    {
        printf("Hello, World! %d of %d\n", omp_get_thread_num(), omp_get_num_threads() - 1);

    }
}
