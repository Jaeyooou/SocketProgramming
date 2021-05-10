#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include <arpa/inet.h>

#define BUFSIZE 1024
int main(int argc , char *argv[]){
// argc : number of parameters , argv : value of paramater , argv[0] : route
// if gcc -o server.c 1234 -> argc : 2 , argv[1] = '1234'
    //argv[0] route  , argv[1] protocol type , argv[2] server_port_num
    int serv_socket;
    int client_socket;
    struct sockaddr_in serv_address;
    struct sockaddr_in clnt_address;
    char receive_message[BUFSIZE] , send_message[BUFSIZE]; // chatting message re
    int str_len;
    int clnt_address_size;
    char client_name[50];
   // printf("my address : %d",)
    
    if(argc != 3){
        printf("parameter is not allowed\n");
        return 0;
    }
    if(strcmp(argv[1] , "TCP") == 0 || strcmp(argv[1] , "tcp") == 0){
        printf("this protocol is TCP \n");
        serv_socket = socket(AF_INET , SOCK_STREAM , 0);
        //socket(int domain , int type , int protocol)
        //int domain-> AF_UNIX : between same process
        // AF_INET : IPv4 , AP_INET6 : IPv6
        // type -> SOCK_STREAM(TCP) , SOCK_DGRAM(UDP) , SOCK_RAW(RAW)
        // int protocol -> IPPROTO_TCP : TCP , IPPROTO_UDP : UDP
        // socket return -1 if socket error , and success -> value that is >=0 socket descriptor
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
	memset(receive_message , 0 , sizeof(receive_message));
	if(read(client_socket , receive_message , BUFSIZE) == -1){
		printf("Read Error!\n");
		return 0;	
}
	strcpy(client_name , receive_message);
	
	
        printf("Connected [%s]from %s:%d\n" ,client_name , inet_ntoa(clnt_address.sin_addr),ntohs(clnt_address.sin_port));
        while(1){
            //read() from client
            memset(receive_message , 0 , sizeof(receive_message));
            ssize_t Received_num = read(client_socket , receive_message , BUFSIZE);
            if(Received_num == -1){
                printf("Read Error!\n");
				return 0;
            }
            if (strcmp(receive_message, "q\n") == 0 || strcmp(receive_message, "quit\n") == 0) {
                printf("Chatting quit!\n");
                return 0;
            }
            printf("from[%s] %s : %s\n",client_name , inet_ntoa(clnt_address.sin_addr) , receive_message);
            
            
            // init receive_message buffer , send_message buffer
            memset(receive_message , 0 , sizeof(receive_message));
            memset(send_message , 0 , sizeof(send_message));
            // input server message
            printf("[server]:");
            fgets(send_message , BUFSIZE , stdin);
			printf("\n");
            if(strcmp(send_message , "q") == 0 || strcmp(send_message , "quit") == 0){
                printf("Chatting quit!\n");
                return 0;
            }
            ssize_t send_num = write(client_socket , send_message , BUFSIZE);
            if(send_num == -1){
                printf("Send Error! \n");
                return 0;
            }
            
            
        }
      
        }
    
    
//--------------------TCP Protocol--------------------------------------------
    else if(strcmp(argv[1] , "UDP") == 0 || strcmp(argv[1] , "udp") == 0){
        printf("this protocol is UDP\n");
        serv_socket = socket(AF_INET , SOCK_DGRAM , 0);
        if(serv_socket == -1){
            printf("Socket Error\n");
            return 0;
        }
		
		memset(&serv_address ,0 , sizeof(serv_address)); 
		serv_address.sin_family = AF_INET; // IPv4
        serv_address.sin_addr.s_addr = htonl(INADDR_ANY); // htonl,htons :     convert little endian to big endian , INADDR_ANY :my ipAdress
        serv_address.sin_port = htons(atoi(argv[2]));
  
        if(bind(serv_socket , (struct sockaddr *)&serv_address,sizeof(serv_address)) == -1){
       		 printf("Binding error\n");
         	 return 0;
        }
         
		printf("create UDP socket(%d :%d) done\n" ,htonl( INADDR_ANY) ,atoi(argv[2]));
		while(1){
			int k = 0;
			memset(receive_message , 0 , sizeof(receive_message));
			int clnt_address_size = sizeof(clnt_address);
			ssize_t Received_num1 = recvfrom(serv_socket , receive_message , BUFSIZE , 0 , (struct sockaddr *)&clnt_address,&clnt_address_size);
			printf("[%s] from %s:",receive_message,inet_ntoa(clnt_address.sin_addr));
			memset(receive_message,0,sizeof(receive_message));
			ssize_t Received_num = recvfrom(serv_socket , receive_message , BUFSIZE , 0 , (struct sockaadr *)&clnt_address , &clnt_address_size);

			if(strcmp(receive_message , "q\n") == 0 || strcmp(receive_message , "quit\n") == 0){
			printf("Chat is over \n");
			return 0;
			}

			printf("%s\n" ,receive_message);

			memset(receive_message , 0 , sizeof(receive_message));
			memset(send_message , 0 , sizeof(send_message));
			//input message
			printf("[server] : ");
			fgets(send_message , BUFSIZE , stdin);
			printf("\n");
			ssize_t send_num = sendto(serv_socket , send_message , BUFSIZE , 0 , (struct sockaddr*)&clnt_address , sizeof(clnt_address));
			if(send_num == -1){
				printf("Send Error!\n");
				return 0;
			}
			
			if(strcmp(send_message , "q\n") == 0 || strcmp(send_message , "quit\n") == 0){
				printf("chat is over!\n");
				return 0;
				}
					
		}


    }
    close(client_socket);
    close(serv_socket);

    
}

