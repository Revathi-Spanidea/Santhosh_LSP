#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081  //defines constants for the server's port number
#define MAX_MSG_SIZE 1024  //the maximum size of the message

int main() {
	int server_fd, new_socket;  //the client socket file descriptor (new_socket), socket file descriptor (server_fd),
	struct sockaddr_in address; //socket address structure (address),
	int addrlen = sizeof(address); //the size of the address structure (addrlen)
	char buffer[MAX_MSG_SIZE] = {0}; //It also declares a buffer to store received messages.

	// Create socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) //creates a socket using the socket system call
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Socket creation is successfull\n");
	}

	// Initialize address structure Sets up the address structure for the serve
	address.sin_family = AF_INET;  //specifying IPv4
	address.sin_addr.s_addr = INADDR_ANY; // any available IP address of the machine (INADDR_ANY),
	address.sin_port = htons(PORT); //the port number

	// Bind the socket to localhost and port
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("bind failed\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Bind is successfull\n");
	}

	// Listen for connections
	if (listen(server_fd, 3) < 0) //Sets the socket to listen for incoming connections,It specifies the maximum length of the queue for pending connections (3 in this case).
	{
		printf("listen Failed\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Listen Successfull\n");
		printf("Server listening on port %d\n", PORT);
	}

	//printf("Server listening on port %d\n", PORT);

	// Accept incoming connection from clients,  creates a new socket (new_socket) for communication with the client.
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) 
	{
		printf("accept is failed\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Accept Successfull\n");
	}

	// Read message from client 
	int bytes_read = read(new_socket, buffer, MAX_MSG_SIZE); //Reads the message sent by the client from the socket into the buffer.
	if(bytes_read < 0)
	{
		printf("Failed to read message from the client\n");
		printf("Values of the bytes_read %d\n",bytes_read);
	}
	else
	{
		printf("Client sent: %s\n", buffer);
		printf("Values of the bytes_read %d\n",bytes_read);
	}

	// Reverse the message stored in the buffer.
	int len = strlen(buffer);
	for (int i = 0; i < len / 2; i++)
	{
		char temp = buffer[i];
		buffer[i] = buffer[len - i - 1];
		buffer[len - i - 1] = temp;
	}

	// Send reversed message back to client through the socket.
	int bytes_write = send(new_socket, buffer, strlen(buffer), 0);
	if(bytes_read < 0)
	{
		printf("Failed to write message from the socket\n");
		printf("Values of the bytes_read %d\n",bytes_write);
	}
	else
	{
		printf("Reversed message sent to client\n");
		printf("Socket Sent message: %s\n", buffer);
		printf("Values of the bytes_read %d\n",bytes_write);
	}



	close(new_socket);//Closes the socket connections.
	close(server_fd);

	return 0;
}

