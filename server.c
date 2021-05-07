#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include <arpa/inet.h>

int main(int argc , char *argv[]){
// argc : number of parameters , argv : value of paramater , argv[0] : route
// if gcc -o server.c 1234 -> argc : 2 , argv[1] = '1234'          
	//argv[0] route  , argv[1] protocol type , argv[2] server_port_num
	int serv_socket;
    int client_socket;
	struct sockaddr_in serv_address;
	struct sockaddr_in clnt_address;
	char message[25];
	int str_len;
	int clnt_address_size;
   // printf("my address : %d",)
    
	if(argc != 3){
		printf("parameter is not allowed\n");
		return 0;
	}
    if(strcmp(argv[1] , "TCP") == 0 || strcmp(argv[1] , "tcp") == 0){
		printf("this protocol is TCP \n");
		serv_socket = socket(AF_INET , SOCK_STREAM , 0);
	
	}
	else if(strcmp(argv[1] , "UDP") == 0 || strcmp(argv[1] , "udp") == 0){
		printf("this protocol is UDP\n");
		serv_socket = socket(AF_INET , SOCK_DGRAM , 0);}
		
	 if(serv_socket == -1){
		 printf("Socket Error\n");
		 return 0;
	 }

	memset(&serv_address ,0 , sizeof(serv_address));
	serv_address.sin_family = AF_INET; // IPv4
	serv_address.sin_addr.s_addr = htonl(INADDR_ANY); // htonl,htons : convert little endian to big endian , INADDR_ANY :my ipAdress
	serv_address.sin_port = htons(atoi(argv[2]));
	
	if(bind(serv_socket , (struct sockaddr*)&serv_address , sizeof(serv_address)) == -1){
	printf("Binding error\n");
	return 0;
	}
	printf("create TCP socket(%d :%d) done\n" ,htonl( INADDR_ANY) , atoi(argv[2]));
	if(listen(serv_socket ,5) == -1)
	{
		printf("Listening error\n");
		return 0;
	}
	printf("Server lIstening~~~~\n");
	//server listening
	clnt_address_size = sizeof(clnt_address);
	client_socket = accept(serv_socket , (struct sockaddr*)&clnt_address , &clnt_address_size);
	//if accept is successed  ,func accept() returns clients socket, 
	if(client_socket == -1){
		printf("accept error\n");
		return 0;
	}
	printf("Enter Client\n");
	printf("Connected from %s:%d\n" ,inet_ntoa(clnt_address.sin_addr),ntohs(clnt_address.sin_port));
	
	


	
		
    //socket(int domain , int type , int protocol)
    //int domain-> AF_UNIX : between same process
    // AF_INET : IPv4 , AP_INET6 : IPv6
    // type -> SOCK_STREAM(TCP) , SOCK_DGRAM(UDP) , SOCK_RAW(RAW)
    // int protocol -> IPPROTO_TCP : TCP , IPPROTO_UDP : UDP
    // socket return -1 if socket error , and success -> value that is >=0 socket descriptor
        





    
    
	
}
