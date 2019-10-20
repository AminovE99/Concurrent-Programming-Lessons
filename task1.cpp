#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <limits>

#define NUM_THREADS 8


void task1();

void task2();

void task3();

void task4();

void task5();


void task6();

void task7();

int main() {
    //task1();
    //task2();
    //task3();
    //task4();
    //task5();
    //task6();
    task7();
}

void task7() {
    int N = 12;
    int a[N];
    int b[N];
    int c[N];
    omp_set_dynamic(0);
    omp_set_num_threads(3);
    #pragma omp parallel for schedule(static, 4)
    for (int i = 0; i < N;i++){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        printf("part N 1, Thread N %d, thread_count %d", omp_get_thread_num(),omp_get_num_threads());
        printf("i,a[i],b[i] = %d, %d, %d \n", i, a[i],b[i]);
    }
    omp_set_num_threads(3);
    #pragma omp parallel for schedule(dynamic, 3)
    for (int i = 0; i < N; i++){
        c[i] = a[i] + b[i];
        printf("part N 2, Thread N %d, thread_count %d",omp_get_thread_num(),omp_get_num_threads());
        printf("i,c[i] = %d, %d",i,c[i]);
    }
}

void task6() {
    int COUNT_OF_THREADS = 6;
    int N = 10;
    omp_set_dynamic(0);
    omp_set_num_threads(COUNT_OF_THREADS);
    int a[N];
    int b[N];
    for (int i = 0; i < N; i++) {
        a[i] = rand();
        b[i] = rand();
    }
    int average_a = 0;
    int average_b = 0;
    #pragma omp parallel for reduction(+:average_a, average_b)
    for(int i = 0; i < N;i++){
        average_a = average_a+a[i];
        average_b = average_b+b[i];
    }
    printf("Average a: %d", average_a);
    printf("Average b: %d", average_b);
}

void task5() {
    int COUNT_OF_THREADS = 4;
    omp_set_dynamic(0);
    omp_set_num_threads(COUNT_OF_THREADS);
    int d[6][8];
    for (int i = 0; i < sizeof(d); i++) {
        for (int j = 0; j < sizeof(d[i]); j++) {
            d[i][j] = rand() % 100;
        }
    }
#pragma omp parallel sections
    {
#pragma omp section
        {
            int average = 0;
            for (int i = 0; i < sizeof(d); i++) {
                for (int j = 0; j < sizeof(d[i]); j++) {
                    average += d[i][j];
                }
            }
            average /= sizeof(d) * sizeof(d[0]);
            printf("Hello, I'm thread number %d. Average = %d\n", omp_get_thread_num(), average);


        }
#pragma omp section
        {
            int max = std::numeric_limits<int>::min();
            int min = std::numeric_limits<int>::max();
            for (int i = 0; i < sizeof(d); i++) {
                for (int j = 0; j < sizeof(d[i]); j++) {
                    if (d[i][j] > max) {
                        max = d[i][j];
                    }
                    if (d[i][j] < min) {
                        min = d[i][j];
                    }
                }
            }
            printf("Hello, I'm thread number %d; Min = %d; Max = %d\n", omp_get_thread_num(), min, max);

        }
#pragma omp section
        {
            int multiple_three_count = 0;
            for (int i = 0; i < sizeof(d); i++) {
                for (int j = 0; j < sizeof(d[i]); j++) {
                    if (d[i][j] % 3 == 0) {
                        multiple_three_count++;
                    }
                }
            }
            printf("Hello, I'm thread number %d;\n; Multiple three count = %d\n", omp_get_thread_num(),
                   multiple_three_count);

        }
    }
}


void task4() {
    int num = 0;
    printf("Insert count of numbers: ");
    scanf("%d", &num);
    int a[num], b[num];
    for (int i = 0; i < num; i++) {
        a[i] = rand() % (10 - 1) + 1;
        b[i] = rand() % (10 - 1) + 1;
    }
    int min_a = std::numeric_limits<int>::max();
    int max_b = std::numeric_limits<int>::min();
#pragma omp parallel
    {
        if (omp_get_thread_num() == 0) {
            for (int i = 0; i < num; i++) {
                if (a[i] < min_a) {
                    min_a = a[i];
                }
            }
        } else {
            for (int i = 0; i < num; i++) {
                if (b[i] > max_b) {
                    max_b = b[i];
                }
            }
        }
    }
    printf("Min a: %d\n", min_a);
    printf("Max b: %d\n", max_b);
}

void task3() {
    int a, b;
    printf("Print a: ");
    scanf("%d", &a);
    printf("\nPrint b: ");
    scanf("%d", &b);
    omp_set_dynamic(0);

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
        printf("Inside second block %d Thread: a = %d, b = %d\n", thread_num, a, b);
    }
    printf("After second block: a= %d, b = %d", a, b);
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
