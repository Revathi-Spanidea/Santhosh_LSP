#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081 //defines constants for the server's port number (PORT) 
#define SERVER_IP "127.0.0.1" // the server's IP address (SERVER_IP).

int main() 
{
    int sock = 0; // initializes variables for the client socket file descriptor (sock)
    struct sockaddr_in serv_addr; //server address structure (serv_addr)
    char message[1024] = {0}; //uffer to store the message to be sent.

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) //creates a socket using the socket system call
    {
        printf("socket creation failed");
        exit(EXIT_FAILURE);
    }
    else
    {
	    printf("Socket creation successfull\n");
    }

    // Initialize server address structure
    serv_addr.sin_family = AF_INET; //Sets up the address structure for the server,
    serv_addr.sin_port = htons(PORT); //specifying IPv4 and the port number.

    // Convert IPv4 and IPv6 addresses from text to binary form, stores it in the address structure
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0)
    {
        printf("invalid address");
        exit(EXIT_FAILURE);
    }
    else
    {
	    printf("Valid address\n");
    }

    // Connects to the server using the socket and the server address structure.
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("connection failed");
        exit(EXIT_FAILURE);
    }
    else
    {
	    printf("Connection to Socket is successfull\n");
    }

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin); //reads the input from the standard input (stdin),
    message[strcspn(message, "\n")] = '\0'; // Remove newline character from the end of the message.

    // Send message to server through the socket.
    int send_bytes = send(sock, message, strlen(message), 0);
    if(send_bytes <= 0)
    {
	    printf("failed to send data from clinet\n");
    }
    else
    {
    	printf("Message sent to server\n");
    }

    // Receive reversed message from server from the socket into the buffer
    char buffer[1024] = {0};
    int read_bytes = read(sock, buffer, 1024);
    if(read_bytes <= 0)
    {
	    printf("Failed to read from server\n");
    }
    else
    {
	    printf("Reversed message from server: %s\n", buffer);
    }

    close(sock); //Closes the socket connection.

    return 0;
}

