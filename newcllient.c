#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ADMIN.c"
#define PORT 4444

int main(){

	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");

	while(1){
		char buff[1000];
    	recv(client_socket,buff,sizeof(buff),0);
    	printf("Menu %s",buff);

    	//Selecting Login as
    	char choice_buffer[2];
    	fgets(choice_buffer, sizeof(choice_buffer), stdin);
    	send(client_socket, choice_buffer, sizeof(choice_buffer), 0);
    	int c;
    	while ((c = getchar()) != '\n' && c != EOF);
    	//Displaying options
    	char buff1[1000];
    	read(client_socket,buff1,sizeof(buff1));
    	printf("%s\n",buff1);

    	int choice;
    	fflush(stdout);
    	printf("\nEnter your choice:\n");
    	scanf("%d",&choice);
    	write(client_socket, &choice, sizeof(choice));
   		Admin(choice,client_socket);
	}	
	close(client_socket);
}