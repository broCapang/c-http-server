#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){
	struct sockaddr_in inbound_socket;
	// Create a socket
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd > 0){
			puts("[*]Socket Created!");
	}else{
			puts("[!]Failed! Cannot create Socket!");

	}
	// Zeroed out the inbound_socket variable
	memset(&inbound_socket, 0, sizeof(struct sockaddr_in));
	
	// Initialize the value for sockaddr_in structure
	inbound_socket.sin_family = AF_INET;
	inbound_socket.sin_port = htons(PORT);
	inet_aton("127.0.0.1",(struct in_addr*) &inbound_socket.sin_addr.s_addr);
	
	// binds the socket 
	if (bind(sockfd, (struct sockaddr*) &inbound_socket, sizeof(inbound_socket)) >= 0){
		puts("[*]IP Address and Socket Binded Successfully!");
	}else{
		puts("[!]Failed! IP Address and Socket did not Bind!");
		exit(EXIT_FAILURE);		
	}
	
	//listen to the socket
	if (listen(sockfd,3)>=0) {
		puts("[*]Socket is currently Listening!");
	}else{
		puts("[!]Failed! Cannot listen to the Socket!");
		exit(EXIT_FAILURE);
	}

	while(1){
		puts("[*]Server Started....");
		puts("[*]Waiting for client to connect.....");
		

		struct sockaddr_in client_addr;

		socklen_t client_addr_len = sizeof(client_addr);
		int clientfd = accept(sockfd, (struct sockaddr_in*) &client_addr, &client_addr_len);
		if (clientfd > 0 ){
			puts("[*]Client Connected!");
			if(!fork()){
			// Handle Connection 
			// handleConnection(clientfd);
				handleConnection(clientfd);


			}
			//char* respond = "HTTP/1.1 200 OK\r\n\r\n";
			//if (send(clientfd, respond, strlen(respond), 0) < 0){
			//	puts("[!]Failed! Cannot send respond!");
			//}
		}else{
			puts("[!]Failed! Cannot accept client request");
			exit(EXIT_FAILURE);
		}
	}	
	exit(0);

}


void handleConnection(int clientfd){
		puts("[*]Handling a Connection!");
		char *buffer;
		buffer = malloc(1024*(sizeof(char)));
		int bytes_recv = recv(clientfd, buffer, malloc_usable_size(buffer),0);
		
		if (bytes_recv < 0 ){
				puts("[!]Failed! No Bytes Received!");
				exit(EXIT_FAILURE);
		}

		printf("Input: %s\n\n",buffer);

		return;

}
