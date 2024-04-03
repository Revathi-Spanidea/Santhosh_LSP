/*3.Create a program that accesses and modifies environment variables using system calls like getenv and setenv.
 Demonstrate how to retrieve the value of a specific environment variable and how to set a new environment variable.*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Retrieve the value of a specific environment variable
    const char *home_dir = getenv("HOME");
    if (home_dir == NULL) {
        printf("HOME environment variable is not set.\n");
    } else {
        printf("Value of HOME environment variable: %s\n", home_dir);
    }
    
    // Set a new environment variable
    const char *new_var_name = "MY_VARIABLE";
    const char *new_var_value = "Hello, World!";
    
    if (setenv(new_var_name, new_var_value, 1) != 0) {
        perror("Error setting new environment variable");
        exit(EXIT_FAILURE);
    }
    
    printf("New environment variable '%s' set with value '%s'\n", new_var_name, new_var_value);
    
    // Retrieve the value of the newly set environment variable
    const char *new_var = getenv(new_var_name);
    if (new_var == NULL) {
        printf("New environment variable '%s' is not set.\n", new_var_name);
    } else {
        printf("Value of new environment variable '%s': %s\n", new_var_name, new_var);
    }
    
    return 0;
}

