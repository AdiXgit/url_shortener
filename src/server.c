#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <windows.h>
    #pragma comment(lib, "ws2_32.lib")  // Link Winsock library
#else
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <pthread.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "url_shortener.h"

#define PORT 8080
#define BUFFER_SIZE 2048

#ifdef _WIN32
    typedef SOCKET socket_t;
    #define close_socket closesocket
#else
    typedef int socket_t;
    #define close_socket close
#endif

void* handle_client(void* socket_desc) {
    socket_t sock = *(socket_t*)socket_desc;
    free(socket_desc);

    char buffer[BUFFER_SIZE] = {0};
    char command[16], argument[BUFFER_SIZE], response[BUFFER_SIZE];

    recv(sock, buffer, BUFFER_SIZE, 0);
    sscanf(buffer, "%s %s", command, argument);

    if (strcmp(command, "SHORTEN") == 0) {
        char* short_url = shorten_url(argument);
        sprintf(response, "SHORTENED %s\n", short_url);
        free(short_url);
    } else if (strcmp(command, "EXPAND") == 0) {
        char* long_url = expand_url(argument);
        sprintf(response, "EXPANDED %s\n", long_url);
        free(long_url);
    } else {
        strcpy(response, "ERROR\n");
    }

    send(sock, response, strlen(response), 0);
    close_socket(sock);
    return NULL;
}

int main() {
    #ifdef _WIN32
        WSADATA wsa;
        WSAStartup(MAKEWORD(2,2), &wsa);
    #endif

    socket_t server_fd, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    listen(server_fd, 5);
    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_sock = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_sock < 0) {
            perror("Accept failed");
            continue;
        }

        #ifdef _WIN32
            HANDLE thread;
            thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)handle_client, (void*)&client_sock, 0, NULL);
            CloseHandle(thread);
        #else
            pthread_t thread;
            socket_t* socket_desc = (socket_t*)malloc(sizeof(socket_t));
            *socket_desc = client_sock;
            pthread_create(&thread, NULL, handle_client, (void*)socket_desc);
            pthread_detach(thread);
        #endif
    }

    close_socket(server_fd);
    #ifdef _WIN32
        WSACleanup();
    #endif

    return 0;
}
