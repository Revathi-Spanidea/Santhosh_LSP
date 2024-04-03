#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define Buffer_Size 4096

int main(int argc, char *argv[])
{
    int source_file, dest_file;
    ssize_t bytes_read_src, bytes_read_dest;
    char buffer_src[Buffer_Size], buffer_dest[Buffer_Size];

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    source_file = open(argv[1], O_RDONLY);
    if (source_file < 0)
    {
        printf("Failed to open source file");
        exit(EXIT_FAILURE);
    }
    else
    {
            printf("Source file opned successfully\n");
    }

    dest_file = open(argv[2],  O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_file < 0)
    {
        printf("Failed to open destination file");
        close(source_file);
        exit(EXIT_FAILURE);
    }
    else
    {
            printf("Destination file open Successfully\n");
    }

    bytes_read_src = read(source_file, buffer_src, Buffer_Size);
    bytes_read_dest = read(dest_file, buffer_dest, Buffer_Size);
    if(bytes_read_dest != bytes_read_src || memcmp(buffer_src, buffer_dest, bytes_read_src) != 0)
    {
            printf(" buffer content doesn't match\n");
            if (write(dest_file, buffer_src, bytes_read_src) != bytes_read_src)
            {
                    printf("Failed to write to destination file");
                    close(source_file);
                    close(dest_file);
            }
            printf("Copied %zd bytes from source to destination\n", bytes_read_src);
    }
    else
    {
            printf("Content in source and destination files match\n");
    }

    close(source_file);
    close(dest_file);

    return 0;
}

