#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
int connection;
int server_socket;


void Accept() {
        
    listen(server_socket,5);
    printf("listening...\n");
    struct sockaddr_in client_address;
    socklen_t len = sizeof(client_address); //
    connection = accept(server_socket, (struct sockaddr *)&client_address,&len); //
        
    if (connection <=0){
        printf("connection failed\n");
        return ;
    }
        
    printf("connected!\n");
    
    
}


void chat(){

    char message[1024];
    char reply[1024];

    memset(&message,0,sizeof(message));

    int bytes_Rec=recv(connection,message,sizeof(message),0);
    if(bytes_Rec <= 0) return;

    printf("client : %s",message);

    printf("type something : ");
    
    
    fgets(reply,sizeof(reply),stdin);
    send(connection,reply,strlen(reply),0);
}


int main(int argc,const char *argv[]){

    server_socket=socket(AF_INET,SOCK_STREAM,0); //creating a socket in ipv4 using tcp stream

    if(server_socket<0){

        printf("Failed to create socket\n");
        return 1;
    }


    printf("Server socket created successfully\n");
    
    struct sockaddr_in server_address;  //creating a structure that stores server's ip adresses

    memset(&server_address,0,sizeof(server_address)); //clearing the memory of that structure 

    server_address.sin_family = AF_INET;  //specifying that it is ipv4
    server_address.sin_port = htons(8080);; // specifiying the port of 8080 using htons that conver unsigned short inter to bytes
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); //specfying the adress ip
    

    int status = bind(server_socket,(struct sockaddr *) &server_address ,sizeof(server_address));// here comes the binding,we bind the socket,

    if (status<0){
        printf("the bind didnt work\n");
        return 1;
    }
    printf("bind is succefully working\n");
    while(1){
        Accept();
        while(1){
            chat();
            }
        }

        close(server_socket);
    }
