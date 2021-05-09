#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define BUFSIZE 1024

int main(int argc , char *argv[]){
    int clnt_socket;
    char send_message[BUFSIZE];
    char receive_message[BUFSIZE];
    size_t send_len; // unsigned data type
    char name[BUFSIZE];
    struct sockaddr_in serv_address , clnt_address;
    int clnt_address_size;
    // argv[0] route , argv[1] protocol type , argv[2] server_ip_address ,  argv[3] port_num , argv[4] client_name
    if( argc != 5){
        printf("Parameter Error \n");
        return 0;
    }
    strcpy(name , argv[4]);
    printf("Client name : %s\n",name);
    if(strcmp(argv[1] , "TCP") == 0 || strcmp(argv[1] , "tcp")== 0){ //TCP
        printf("This Connection protocol is TCP\n");
        clnt_socket = socket(AF_INET , SOCK_STREAM , 0);
        if(clnt_socket == -1){
            printf("Socket Error\n");
            return 0;
        }
        memset(&serv_address , 0 , sizeof(serv_address));
        serv_address.sin_family = AF_INET;
        serv_address.sin_addr.s_addr = inet_addr(argv[2]);
        serv_address.sin_port = htons(atoi(argv[3]));
        // init server_address struct
        
        if(connect(clnt_socket , (struct sockaddr*)&serv_address , sizeof(serv_address)) == -1){
        printf("Connection error\n");
        return 0;
        }

        printf("chatting start , if you want to exit input 'q' or 'quit' \n");
        while(1){
            //init message
            printf("[%s]:",name);
            memset(send_message , 0 , BUFSIZE);
            fgets(send_message , BUFSIZE , stdin);
            if(strcmp(send_message , "quit") == 0 || strcmp(send_message , "q") == 0){
                printf("chatting is over\n");
                return 0;
            }
            send_len = strlen(send_message);
            ssize_t send_num = write(clnt_socket , send_message , BUFSIZE);
            if(send_num == -1){
                printf("Write Error!\n");
                return 0;
            }
			ssize_t read_num = read(clnt_socket , receive_message , BUFSIZE);
	
			if(read_num == -1){
				printf("Read Error\n");
				return 0;
			}
            if(strcmp(receive_message , "quit") == 0 || strcmp(receive_message , "q") == 0){
                printf("chatting is over\n");
                return 0;
            }
            printf("[server]%s: %s\n",inet_ntoa(serv_address.sin_addr) , receive_message);
            memset(receive_message , 0 , sizeof(receive_message));
        
        }
    }
    else if(strcmp(argv[1],"UDP") == 0 || strcmp(argv[1],"udp")==0){ // UDP
        printf("This Connection protocol is UDP\n");
        clnt_socket = socket(AF_INET,SOCK_DGRAM,0);
        if(clnt_socket == -1){
            printf("Socket Error\n");
            return 0;
        }
    }
   
    
}


