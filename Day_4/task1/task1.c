/*10.Write a program that demonstrates memory mapping by mapping a file into memory,
 modifying its contents, and then writing the changes back to the file. Use memory mapping system calls like mmap and munmap.*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILENAME "mapped_file.txt"
#define FILESIZE 1000

int main() {
    int fd;
    char *mapped_mem;
    struct stat file_stat;

    // Open the file for reading and writing
    fd = open(FILENAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Truncate the file to the desired size
    if (ftruncate(fd, FILESIZE) == -1) {
        perror("Error truncating file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Map the file into memory
    mapped_mem = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_mem == MAP_FAILED) {
        perror("Error mapping file into memory");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Write some data to the memory region
    strcpy(mapped_mem, "Hello, Memory Mapping!");

    // Sync the mapped region to the file
    if (msync(mapped_mem, FILESIZE, MS_SYNC) == -1) {
        perror("Error syncing memory to file");
        munmap(mapped_mem, FILESIZE);
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Unmap the memory region
    if (munmap(mapped_mem, FILESIZE) == -1) {
        perror("Error unmapping memory");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    printf("File mapped, modified, and written back successfully.\n");

    return 0;
}
