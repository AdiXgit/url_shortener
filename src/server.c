#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "url_shortener.h"

#define PORT 8080
#define BUFFER_SIZE 2048
void* handle_client(void* socket_desc){
    int sock  = *(int*)socket_dec;
    char buffer[BUFFER_SIZE] = {0};

    read(sock,buffer,BUFFER_SIZE);
    sscanf(buffer,"%s %s",command,argument);

    if(strcmp(command,"SHORTEN") == 0){
        char*short_url = shorten_url(argument);
        sprintf(response,"SHORTENDED %s\n",short_url);
        free(short_url);
    } else if(strcmp(command,"EXPAND") == 0){
        char* long_url = expand_url(argument);
        sprintf(response,"EXPANDED %s\n",long_url);
        free(long_url);
    } else {
        sprintf(response,"ERROR\n");
    }
    write(sock,response,strlen(response));
    close(sock);
    free(socket_desc);
    return NULL;
}

int main(){
    int server_fd,client_sock;
    struct sockaddr_in server_addr,client_addr;
    socket_t client_len = sizeof(client_addr);

    server_fd = socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    listen(server_fd,5);
    printf("Server listening on port %d\n",PORT);

    while(1){
        client_sock = accept(server_fd,(struct sockaddr*)&client_addr,&client_len);
        pthread_t thread;
        int* socket_desc = (int*)malloc(sizeof(int));
        *socket_desc = client_sock;
        pthread_create(&thread,NULL,handle_client,(void*)socket_desc);
        pthread_detach(thread);
    }
    return 0;
    
}