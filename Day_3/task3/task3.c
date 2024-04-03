/*3.Write a C program that simulates a simple file copying utility using Linux system calls. Your program should take two command-line arguments: the source file path and the destination file path. It should then read the contents of the source file and write them to the destination file. Implement error handling for file opening, reading, and writing operations.*/




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    int source_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];
    
    // Check if correct number of command-line arguments are provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // Open source file for reading
    source_fd = open(argv[1], O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }
    
    // Open destination file for writing, create it if it doesn't exist, truncate it if it does
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(source_fd);
        exit(EXIT_FAILURE);
    }
    
    // Copy contents from source file to destination file
    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }
    
    if (bytes_read == -1) {
        perror("Error reading from source file");
        close(source_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }
    
    // Close files
    if (close(source_fd) == -1) {
        perror("Error closing source file");
        exit(EXIT_FAILURE);
    }
    if (close(dest_fd) == -1) {
        perror("Error closing destination file");
        exit(EXIT_FAILURE);
    }
    
    printf("File copied successfully.\n");
    return 0;
}

