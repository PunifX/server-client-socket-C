#include <netinet/in.h> //for struct
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // for socket functions
#include <pthread.h>    // for creathing threads
#include <unistd.h>       // close() for sockets, read(), write()
#include <arpa/inet.h>    // inet_addr, htons, ntohs

#define MAX_CLIENTS 100

typedef struct {
    int socket;
    char name[70];
} Client;

Client clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;


int socket_creating(){
    int server_socket=socket(AF_INET,SOCK_STREAM,0); // creating a socket
    printf("Socket created!\n");

    struct sockaddr_in server_address;
    memset(&server_address,0,sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port =htons(9999);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    int binding=bind(server_socket, (struct sockaddr *) &server_address,sizeof(server_address)); //assigning a name to a socket

    if (binding < 0){
        perror("Bind failed");
        close(server_socket);
        return -1;
    }
    int listening = listen(server_socket,5);

    if (listening < 0){
        perror("Listening failed");
        close(server_socket);
        return -1;
    }

    return server_socket;

}

int accepting(int server_socket){
    struct sockaddr_in client_address;
    memset(&client_address,0,sizeof(client_address));

    socklen_t len = sizeof(client_address); 
    int connection = accept(server_socket, (struct sockaddr *)&client_address,&len); 
        
    if (connection < 0){
        perror("connection failed\n");
        return-1 ;

    }
    accept(connection);
    return connection;
    
}

void *handle_client_name_and_sending_messages(void *arg) {
    int client_socket = *(int *)arg;

    free(arg);

    char name [70];
    int bytes=recv(client_socket,name,sizeof(name),0);
    if (bytes<=0) {
        close(client_socket);
        return NULL;
    }
    printf("%s has connected succefuly!\n",name);
    name[bytes] = '\0';

    pthread_mutex_lock(&clients_mutex);
    clients[client_count].socket = client_socket;
    strcpy(clients[client_count].name, name);
    client_count++;
    pthread_mutex_unlock(&clients_mutex);
    
    char message_sent [1024]

    

    while(1){

    int message_sent=recv(client_socket,name,sizeof(name),0);
    if (message_sent<=0) {
        close(client_socket);
        return NULL;
    }
    printf("%s:%s\n",name,message_sent);
    
    }
}


int handle_broadcasting(void *arg) {
    int client_socket = *(int *)arg;
    free(arg);

    char message_sending [1024];
    send(client_socket,message_sending,sizeof(message_sending),0);
    
    return message_sending;
}
int handle_client_recieve(void *arg,chat name[]) {
    int client_socket = *(int *)arg;
    free(arg);
    
    char message_recieved [1024];
    recv(client_socket,message_recieved,sizeof(message_recieved),0);
    printf("%s : %s",name,message_recieved);
    return message_recieved;
}
int main(){
    int server_socket = socket_creating();

    
    while(1){
      

    }
    close(connection);
    close(server_socket);
    return 0;
}