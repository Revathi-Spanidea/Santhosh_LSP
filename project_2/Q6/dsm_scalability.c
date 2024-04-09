//Validate the performance and scalability of the DSM module through extensive testing and benchmarking under various workload scenarios, considering factors like access patterns, data size, and network latency.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define NUM_THREADS 5
#define DATA_SIZE 1000000 // Size of shared data array
#define NUM_ITERATIONS 10000 // Number of iterations per thread

int shared_data[DATA_SIZE]; // Shared data array
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Function to simulate processing
void process_data(int thread_id) {
    // Access shared data with read or write operations
    // Simulate processing time based on access pattern
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        int index = rand() % DATA_SIZE; // Random access pattern
        pthread_mutex_lock(&mutex);
        shared_data[index]++; // Modify shared data
        pthread_mutex_unlock(&mutex);
    }
}

// Function executed by each thread
void *thread_function(void *arg) {
    int thread_id = *((int *)arg);
    process_data(thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    struct timeval start_time, end_time;
    double total_time;

    // Initialize shared data
    for (int i = 0; i < DATA_SIZE; i++) {
        shared_data[i] = 0;
    }

    // Start time measurement
    gettimeofday(&start_time, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, (void *)&thread_ids[i]) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Error joining thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // End time measurement
    gettimeofday(&end_time, NULL);

    // Calculate total time taken
    total_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0; // Convert seconds to milliseconds
    total_time += (end_time.tv_usec - start_time.tv_usec) / 1000.0; // Convert microseconds to milliseconds

    printf("Total time taken: %.2f milliseconds\n", total_time);

    pthread_mutex_destroy(&mutex);

    return 0;
}

