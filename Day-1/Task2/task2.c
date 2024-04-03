/*2Write a program that demonstrates file system permissions by creating a file with specific permissions 
(e.g., read-only for owner) and changing its permissions using system calls like chmod.*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *filename = "testfile.txt";
    int fd;
    
    // Create a file with read-only permissions for the owner
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR);
    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    
    printf("File created successfully with read-only permission for the owner.\n");
    
    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
   
    // Change file permissions to allow read and write for the owner
    if (chmod(filename, S_IRUSR | S_IWUSR) == -1) {
        perror("Error changing file permissions");
        exit(EXIT_FAILURE);
    }
    
    printf("File permissions changed to allow read and write for the owner.\n");
    
    return 0;
}

