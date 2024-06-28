#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#define MAX 80
#define SA struct sockaddr
#define PORT 5051

//Function designed for chat between client and server
void chat(int connfd){

    char buffer[MAX];
    int n;
    //infinite loop for chat
    for(;;){
        bzero(buffer,MAX);

        //read the message from the client and copy it in buffer
        read(connfd,buffer,sizeof(buffer));
        //print client content
        printf("From client :%s \t To client :",buffer);
        bzero(buffer,MAX);
        n=0;
        //copy server message in the buffer

        while((buffer[n++]= getchar())!='\n');
        
        //send the buffer to client
        write(connfd,buffer,sizeof(buffer));
        
        //if msg contains "Exit" then server exit and chat ended
        if(strncmp("exit",buffer,4)==0){
            printf("Server Exit ..\n");
            break;
        }
    }
}

int main(){
    int sockfd,connfd;
    socklen_t len;
    struct sockaddr_in serveraddr,clientaddr;

    //socket create and verfication

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0){
        printf("socket creation failed   ..\n");
        exit(0);

    }
    else  printf("socket creation succesfull   ..\n");

    bzero(&serveraddr,sizeof(serveraddr));

    //assign IP,PORT
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(PORT);
    serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);

    //Binding the newly created socket

    if((bind(sockfd,(SA*)&serveraddr,sizeof(serveraddr)))!=0){
        printf("socket bind failed\n");
        exit(0);

    }
    else printf("socket bind succesful\n");

    //Checking whetehr the server is ready to listen

    if(listen(sockfd,5)!=0){
         printf("Listen failed\n");
         exit(0);
    }
    else  printf("Server listening");

    len =sizeof(clientaddr);

    //accept the data  packet from the client 
    connfd=accept(sockfd,(SA*)&clientaddr,&len);

    if(connfd < 0) {
        printf("server accept failed");
        exit(0);
    }
    else
        printf("server accept the client");

    //Function for chatting between the clinet and server
    chat(connfd);

    close(sockfd);



}

