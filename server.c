#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>


int connection;
int server_socket;
// const char *host_ip;
// const char *host_port;
char name[50];

//creating a void function for accepting socket request from clients

void Accept() {
    printf("listening...\n");
    struct sockaddr_in client_address;
    socklen_t len = sizeof(client_address); 


    connection = accept(server_socket, (struct sockaddr *)&client_address,&len); 
        
    if (connection <=0){

        //creating an error message for the socket creation 

        perror("connection failed\n");
        return ;
    }
        
    printf("connected!\n");
    
    recv(connection,name,sizeof(name),0);
}


void chat(){

    char message[1024];
    char reply[1024];

    memset(&message,0,sizeof(message));

    int bytes_Rec=recv(connection,message,sizeof(message),0);
    if(bytes_Rec <= 0) return;

    printf("%s : %s",name,message);

    printf("you : ");
    
    
    fgets(reply,sizeof(reply),stdin);
    send(connection,reply,strlen(reply),0);
}
//fucntion for asking the argumants with at least of 3 counters ./server <Ip> <port>
// void arg(int argc,const char *argv[]){
//     if (argc<3){
//         printf("please provide two arguemnts\n./server <ip> <port>\n");
//         exit(1) ;
//     }else{

//        host_ip = argv[1];
//        host_port = argv[2]; 

//     }


//fucntion for asking the argumants with at least of 3 counters ./server <Ip> <port>




int main(int argc,const char *argv[]){
    //arg(argc,argv);

    
    //printf("%s:%s",host_ip,host_port); just to verify if the arguments are working


    server_socket=socket(AF_INET,SOCK_STREAM,0); //creating a socket in ipv4 using tcp stream

    if(server_socket<0){

        perror("Failed to create socket\n");
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
        perror("the bind didnt work\n");
        return 1;
    }
    printf("bind is succefully created \n");
    listen(server_socket,5); //listening for clients with max 5 connections in the queue
    while(1){
        Accept();

        while(1){
            chat();
            }
        }

        close(server_socket);
    }
