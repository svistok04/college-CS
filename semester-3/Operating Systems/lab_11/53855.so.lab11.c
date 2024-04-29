// SO IS1 223A LAB11
// Vladyslav Zosimchuk
// zv53855@zut.edu.pl
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

HANDLE mutex;
float global_sum = 0.0;
float* t;

typedef struct {
    int index;
    int count_rate;
    float retval;
} DATA;

DWORD WINAPI routine(LPVOID arg) {
    DATA* data = (DATA*)arg;
    int start_index = data->index;
    int count_rate = data->count_rate;

    float local_sum = 0.0;
    for (int i = start_index; i < start_index + count_rate; ++i) {
        local_sum += t[i];
    }

    if (WaitForSingleObject(mutex, INFINITE)) {
        fprintf(stderr, "Unable to lock mutex!\n");
    }
    global_sum += local_sum;
    if (!ReleaseMutex(mutex)) {
        fprintf(stderr, "Unable to unlock mutex!\n");
    }

    data->retval = local_sum;
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <number of expressions> <number of threads>\n", argv[0]);
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); ++i) {
        if (argv[1][i] < '0' ||  argv[1][i] > '9') {
            fprintf(stderr, "Error: Invalid arguments. %s <number of expressions> <number of threads>\n", argv[0]);
            return 2;
        }
    }
    int n = atoi(argv[1]);
    int w = atoi(argv[2]);
    if (n <= 1 || n >= 10000000 || w <= 1 || w >= n || w >= 100000) {
        printf("Invalid arguments. Please ensure 1 < n < 10000000, 1 < w < min(100000, n)\n");
        return 3;
    }
    t = (float*)malloc(n*sizeof(float));
    srand(0);
    for(int i = 0; i < n; i++) {
        t[i] = 1000.0 * rand() / RAND_MAX;
    }
    HANDLE threads[w];
    DWORD threadids[w];
    DATA data[w];
    mutex = CreateMutex(NULL, FALSE, NULL);
    if (!mutex) {
        fprintf(stderr, "Couldn't initialize mutex!\n");
        return 4;
    }
    int count_rate_per_thread = n / w;
    int extra = n % w;
    int starting_index = 0;

    LARGE_INTEGER start, finish, frequency;
    QueryPerformanceFrequency(&frequency);
    double time_elapsed;

    QueryPerformanceCounter(&start);

    for (int i = 0; i < w; ++i) {
        if (i == (w - 1)) {
            count_rate_per_thread += extra;
        }
        data[i].index = starting_index;
        data[i].count_rate = count_rate_per_thread;

        threads[i] = CreateThread(NULL, 0, routine, &data[i], 0, &threadids[i]);
        if (!threads[i]) {
            fprintf(stderr, "Error creating a thread!\n");
            return 5;
        }
        printf("Thread #%lx size=%d\n", threadids[i], data[i].count_rate);
        starting_index += count_rate_per_thread;
    }

    for (int i = 0; i < w; ++i) {
        if (WaitForSingleObject(threads[i], INFINITE)) {
            fprintf(stderr, "Error waiting for thread %lx! \n", threads[i]);
            return 6;
        }
        printf("Thread #%lx sum=%.6f\n", threadids[i], data[i].retval);
        if (!CloseHandle(threads[i])) {
            fprintf(stderr, "Error closing a thread %lx! \n", threads[i]);
            return 7;
        }
    }
    QueryPerformanceCounter(&finish);
    time_elapsed = (double)(finish.QuadPart - start.QuadPart) / frequency.QuadPart;
    if (!CloseHandle(mutex)) {
        fprintf(stderr, "Error destryoing mutex! \n");
        return 8;
    }
    printf("w/Threads sum=%.6f, time=%.6fsec\n", global_sum, time_elapsed);

    QueryPerformanceCounter(&start);
    float sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += t[i];
    }
    QueryPerformanceCounter(&finish);
    time_elapsed = (double)(finish.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("wo/Threads sum=%.6f, time=%.6fsec\n", sum, time_elapsed);
    free(t);
    return 0;
}
