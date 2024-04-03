/*5.Write a program that performs basic file system operations such as creating directories, listing directory contents, and deleting files.
 Utilize system calls like mkdir, opendir, readdir, and unlink.*/
 
 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    // Create a directory
    if (mkdir("example_dir", 0777) == -1) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }
    
    printf("Directory 'example_dir' created successfully.\n");
    
    // Open the directory
    DIR *dir = opendir("example_dir");
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    
    // List directory contents
    printf("Contents of directory 'example_dir':\n");
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    
    // Close the directory
    closedir(dir);
    
    // Delete the directory
    if (rmdir("example_dir") == -1) {
        perror("rmdir");
        exit(EXIT_FAILURE);
    }
    
    printf("Directory 'example_dir' deleted successfully.\n");
    
    return 0;
}

