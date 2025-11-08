#include <netinet/in.h> //for struct
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // for socket functions
#include <pthread.h>    // for creathing threads
#include <unistd.h>       // close() for sockets, read(), write()
#include <arpa/inet.h>    // inet_addr, htons, ntohs

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

int *handle_client_name(void *arg) {
    int client_socket = *(int *)arg;
    free(arg);
    char name [70];
    recv(client_socket,name,sizeof(name),0);
    printf("%s has connected succefuly!\n",name);
    return name;
}


int handle_client_sending(void *arg) {
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
       int connection =  accepting(server_socket);

       int *socket_name = malloc(sizeof(int));
       int *socket_recieve = malloc(sizeof(int));
       int *socket_sending = malloc(sizeof(int));

       *socket_name=*socket_sending=*socket_recieve=connection;

       pthread_t thread_name;
       pthread_t thread_recieve;
       pthread_t thread_sending;

       pthread_create(&thread_name,NULL,handle_client_name,socket_name);

       pthread_create(&thread_recieve,NULL,handle_client_recieve,socket_sending);

       pthread_create(&thread_name,NULL,handle_client_sending,socket_recieve);


       pthread_detach(thread_name);
       pthread_detach(thread_recieve);
       pthread_detach(thread_sending);

    }
    close(connection);
    close(server_socket);
    return 0;
}