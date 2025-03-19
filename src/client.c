#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define buffer_size 2048

int main(){
    int sock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    connect(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    char request[buffer_size],response[buffer_size];

    printf("Enter command(SHORTEN <url> / LOOKUP <url>): ");
    fgets(request,buffer_size,stdin);
    request[strcspn(request,"\n")] = 0;

    send(sock,request,strlen(request),0);
    read(sock,response,buffer_size);
    printf("%s\n",response);
    close(sock);
    return 0;
}


