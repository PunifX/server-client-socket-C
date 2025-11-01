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
const char *host_ip;
const char *host_port;
char name[70];



//creating a new request function
void request(){
    struct sockaddr_in client_address;  //calling the sockaddr_in struct so i could store client-ip addresses into the the sockaddr_in

    memset(&client_address,0,sizeof(client_address)); //clearing the addresses before setting new values

    client_address.sin_family = AF_INET;  
    client_address.sin_port = htons(atoi(host_port)); 
    if (inet_pton(AF_INET, host_ip, &client_address.sin_addr) <= 0) {
        perror("Invalid IP address");
    return;
    }
    connection = connect(client_socket,(const struct sockaddr *) &client_address,sizeof(client_address)); //using the connect fuction so to connect into the server
   
    
}

void args(int argc,const char *argv[]){
    if (argc<3){
        printf("please provide two arguemnts\n./client <ip> <port>\n");
        exit(1) ;
    }else{

       host_ip = argv[1];
       host_port = argv[2]; 

    }
}

//creating chat function
void chat(){
    char message[1024];
    char reply[1024];

    memset(&message,0,sizeof(message));
    
         
    printf("%s: ",name);
    fgets(message, sizeof(message), stdin);
    
    send(client_socket,message,strlen(message),0);
    
    memset(&reply,0,sizeof(reply));

    int recieve_byte=recv(client_socket,reply,sizeof(reply),0);
    if(recieve_byte <= 0)return;

    printf("server: %s",name,reply);
}

//need to fix client's side of chat to recive first name and send their name 


int main(int argc,const char *argv[]) {
    args(argc,argv);

    client_socket=socket(AF_INET,SOCK_STREAM,0); 
    if(client_socket<=0){
        printf("Failed to create socket\n");
        return 1;
    }
    printf("client socket created successfully\n");
    printf("trying to connect...\n");
    request(argc,argv);


    if (connection <0){
        printf("invalid ip or port\n");
        return 1;
    }
    
    printf("connected!\n");
    printf("Enter your name : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name,"\n")] ='\0';
    send(client_socket,name,strlen(name),0);
    while(1){
        chat();
    }
}
   