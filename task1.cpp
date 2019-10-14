#include <iostream>
#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 8


int main() {

    omp_set_dynamic(0);// runtime won't adjust the number of threads
    omp_set_num_threads(NUM_THREADS); // set number of threads in task

#pragma omp parallel
    {
        printf("Hello, World! %d of %d\n", omp_get_thread_num(), omp_get_num_threads() - 1);

    }

    return 0;
}