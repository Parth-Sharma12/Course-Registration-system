#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
//#include "Structures.c"
#include "ADMIN.c"
int id = 0;
int ext = 0;
int main() {
    int server_socket, client_socket; // Fd's for server socket & client socket
    struct sockaddr_in server_addr, client_addr; //used to store address information for the server and client
    socklen_t client_addr_len;//This variable will hold the length of the client's address structure.

    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0); // IPV4 or any other,TCP or UDP,0 default
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Configure the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); //Any port No.
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) { // Server address to server socket
        perror("Binding failed");
        exit(1);
    }

    //maximum 5 pending connections server can handle
    if (listen(server_socket, 5) == -1) {
        perror("Listening failed");
        exit(1);
    }

    printf("Server listening on port 8080...\n");

    // Accept incoming connections
    client_addr_len = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);//returns new socket descriptor associated with the specific client
    if (client_socket == -1) {
        perror("Accepting failed");
        exit(1);
    }

    printf("Client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    client_count++;

    printf("Client connected.\n");
    send(client_socket,"************************* Welcome to academia ************************\n Choose an option to continue\n 1)User\n 2)Professor\n 3)Admin\n ",1000,0);
    while(1){

    char choice_buffer[2];
    recv(client_socket, choice_buffer, sizeof(choice_buffer), 0);
    int option = atoi(choice_buffer);
    if(option==1){ //ADMIN
    	int answer;
        printf("Sending\n");
        const char *options = "Choose from the following options\n 1) Add Student \n 2) View Student Details \n 3) Add Faculty\n 4) View Faculty Details\n 5) Activate Student\n 6) Block Student\n 7) Modify Student Details\n 8) Modify Faculty Details\n, 9) Logout and Exit\n ";
    	write(client_socket,options,strlen(options));
        read(client_socket,&answer,sizeof(int));
        performAdmin_Task(answer,client_socket,id);	
    }
    if(ext==1){
        break;
    }
}
    // Close the sockets when done
    close(client_socket);
    close(server_socket);

    return 0;
}
