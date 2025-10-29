#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int client_socket;
int connection;

//creating a new request function
void request(){
    struct sockaddr_in client_address;  //calling the sockaddr_in struct so i could store client-ip addresses into the the sockaddr_in

    memset(&client_address,0,sizeof(client_address)); //clearing the addresses before setting new values

    client_address.sin_family = AF_INET;  
    client_address.sin_port = htons(8080); 
    client_address.sin_addr.s_addr =htonl(INADDR_ANY); //this can be changed into the server ip address

    connection = connect(client_socket,(const struct sockaddr *) &client_address,sizeof(client_address)); //using the connect fuction so to connect into the server
    
}



//creating chat function
void chat(){
    char message[1024];
    char reply[1024];
    memset(&message,0,sizeof(message));
    
    printf("Enter your message : ");
    fgets(message, sizeof(message), stdin);     
    send(client_socket,message,strlen(message),0);
    
    memset(&reply,0,sizeof(reply));

    int recieve_byte=recv(client_socket,reply,sizeof(reply),0);
    if(recieve_byte <= 0)return;

    printf("server: %s",reply);
}


int main(int argc,const char *argv[]) {
    client_socket=socket(AF_INET,SOCK_STREAM,0); 
    if(client_socket<=0){
        printf("Failed to create socket\n");
        return 1;
    }
    printf("client socket created successfully\n");
    printf("trying to connect...");
    request();
    
    
    printf("connected!\n");
    
    while(1){
        chat();
    }
}
   