/*6.Create a multi-threaded program where multiple threads increment a shared counter concurrently. Use synchronization primitives like mutexes or atomic operations to prevent data race conditions.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define ITERATIONS 1000000

// Shared counter
int counter = 0;

// Mutex for synchronization
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Thread function
void *thread_function(void *arg) {
    int i;
    for (i = 0; i < ITERATIONS; ++i) {
        // Acquire the mutex lock
        pthread_mutex_lock(&mutex);
        
        // Critical section: Increment the counter
        counter++;
        
        // Release the mutex lock
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int i, result;
    
    // Create multiple threads
    for (i = 0; i < NUM_THREADS; ++i) {
        result = pthread_create(&threads[i], NULL, thread_function, NULL);
        if (result != 0) {
            fprintf(stderr, "Error creating thread %d: %d\n", i, result);
            exit(EXIT_FAILURE);
        }
    }
    
    // Wait for all threads to finish
    for (i = 0; i < NUM_THREADS; ++i) {
        result = pthread_join(threads[i], NULL);
        if (result != 0) {
            fprintf(stderr, "Error joining thread %d: %d\n", i, result);
            exit(EXIT_FAILURE);
        }
    }
    
    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);
    
    return 0;
}

