#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_VALUES 5

int values[NUM_VALUES];
int sum = 0;
pthread_mutex_t mutex;

void *generate_numbers(void *arg) {
    // Generate numbers 1 to 5 sequentially
    int counter = 1;
    for (int i = 0; i < NUM_VALUES; i++) {
        values[i] = counter;
        counter = counter + 1; // Wrap around to 1 after 5
    }
    return NULL;
}

void *calculate_sum(void *arg) {
    int local_sum = 0;
    for (int i = 0; i < NUM_VALUES; i++) {
        local_sum += values[i];
    }

    // Acquire mutex before updating global sum
    pthread_mutex_lock(&mutex);
    sum += local_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t generator_thread, calculator_thread;

    // Initialize mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Mutex initialization failed");
        exit(EXIT_FAILURE);
    }

    // Create generator thread
    if (pthread_create(&generator_thread, NULL, generate_numbers, NULL) != 0) {
        perror("Generator thread creation failed");
        exit(EXIT_FAILURE);
    }

    // Wait for generator thread to finish
    if (pthread_join(generator_thread, NULL) != 0) {
        perror("Generator thread join failed");
        exit(EXIT_FAILURE);
    }

    // Print the generated values
    printf("Generated values:\n");
    for (int i = 0; i < NUM_VALUES; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");

    // Create calculator thread
    if (pthread_create(&calculator_thread, NULL, calculate_sum, NULL) != 0) {
        perror("Calculator thread creation failed");
        exit(EXIT_FAILURE);
    }

    // Wait for calculator thread to finish
    if (pthread_join(calculator_thread, NULL) != 0) {
        perror("Calculator thread join failed");
        exit(EXIT_FAILURE);
    }

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    // Print the sum
    printf("Sum of the generated numbers: %d\n", sum);

    return 0;
}

