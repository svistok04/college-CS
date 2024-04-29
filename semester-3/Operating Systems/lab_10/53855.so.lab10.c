// SO IS1 223A LAB10
// Vladyslav Zosimchuk
// zv53855@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t mutex;
double global_sum = 3.0;

void* calculate_pi(void* data) {
    int* thread_data = (int*)data;
    int start_index = thread_data[0];
    int count_rate = thread_data[1];

    double local_sum = 0.0;
    for (int i = start_index; i < start_index + count_rate; ++i) {
        if (i % 2 == 0) {
            local_sum += 4.0 / ((2.0 * i + 2.0) * (2.0 * i + 3.0) * (2.0 * i + 4.0));
        } else {
            local_sum -= 4.0 / ((2.0 * i + 2.0) * (2.0 * i + 3.0) * (2.0 * i + 4.0));
        }
    }

    if (pthread_mutex_lock(&mutex)) {
        fprintf(stderr, "Unable to lock mutex!\n");
    }
    global_sum += local_sum;
    if (pthread_mutex_unlock(&mutex)) {
        fprintf(stderr, "Unable to unlock mutex!\n");
    }

    free(thread_data);
    double* result = malloc(sizeof(double));
    *result = local_sum;
    return (void*)result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Error: Invalid arguments. %s <number of expressions> <number of threads>\n", argv[0]);
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); ++i) {
        if (argv[1][i] < '0' || argv[1][i] > '9') {
            fprintf(stderr, "Error: Invalid arguments. %s <number of expressions> <number of threads>\n", argv[0]);
            return 2;
        }
    }

    for (int i = 0; i < strlen(argv[2]); ++i) {
        if (argv[2][i] < '0' || argv[2][i] > '9') {
            fprintf(stderr, "Error: Invalid arguments. %s <number of expressions> <number of threads>\n", argv[0]);
            return 2;
        }
    }

    int n = atoi(argv[1]);
    int w = atoi(argv[2]);

    if (n <= 1 || n >= 100000000 || w <= 1 || w >= n || w > 100000) {
        fprintf(stderr, "Error: Invalid arguments. 1 < n < 100000000, 1 < w < min(100000, n)\n");
        return 3;
    }

    pthread_t threads[w];
    if (pthread_mutex_init(&mutex, NULL)) {
        fprintf(stderr, "Couldn't initialize mutex!\n");
        return 4;
    }

    int count_rate_per_thread = n / w;
    int extra = n % w;
    int starting_index = 0;

    struct timespec start1, finish1;
    clock_gettime(CLOCK_MONOTONIC, &start1);

    for (int i = 0; i < w; ++i) {
        if (i == (w-1)) {
            count_rate_per_thread += extra;
        }
        int *thread_data = (int *)malloc(2 * sizeof(int));
        thread_data[0] = starting_index;
        thread_data[1] = count_rate_per_thread;
        if (pthread_create(&threads[i], NULL, calculate_pi, (void*)thread_data)) {
            fprintf(stderr, "Error creating a thread!\n");
            return 5;
        }
        printf("Thread %lx size=%d first==%d\n", threads[i], thread_data[1], starting_index);
        starting_index += count_rate_per_thread;
    }

    for (int i = 0; i < w; ++i) {
        double* local_sum;
        if (pthread_join(threads[i], (void**)&local_sum)) {
            fprintf(stderr, "Error waiting for thread %lx! \n", threads[i]);
            return 6;
        }

        printf("Thread %lx sum=%.20f\n", threads[i], *local_sum);
        free(local_sum);
    }

    if (pthread_mutex_destroy(&mutex)) {
        fprintf(stderr, "Error destroying mutex!\n");
        return 7;
    }

    clock_gettime(CLOCK_MONOTONIC, &finish1);
    double time_with_threads = (finish1.tv_sec - start1.tv_sec) + (finish1.tv_nsec - start1.tv_nsec) / 1000000000.0;

    printf("w/Threads PI=%.20f time=%.6f\n", global_sum, time_with_threads);

    struct timespec start2, finish2;
    clock_gettime(CLOCK_MONOTONIC, &start2);

    double pi = 3.0;
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            pi += 4.0 / ((2.0 * i + 2.0) * (2.0 * i + 3.0) * (2.0 * i + 4.0));
        } else {
            pi -= 4.0 / ((2.0 * i + 2.0) * (2.0 * i + 3.0) * (2.0  * i + 4.0));
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &finish2);
    double time_without_threads = (finish2.tv_sec - start2.tv_sec) + (finish2.tv_nsec - start2.tv_nsec) / 1000000000.0;

    printf("wo/Threads PI=%.20f time=%.6f\n", pi, time_without_threads);

    return 0;
}
