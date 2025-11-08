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
    listen(server_socket,5);

    return server_socket;

}

void accepting(){
    //
}

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    //interract
    close(client_socket);
    return NULL;

}
int main(){
    int server_socket = socket_creating();
    //code 
    close(server_socket);
    return 0;
}