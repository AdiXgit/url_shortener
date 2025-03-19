#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")  // Link Winsock library
#else
    #include <unistd.h>
    #include <arpa/inet.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080
#define BUFFER_SIZE 2048

#ifdef _WIN32
    typedef SOCKET socket_t;
    #define close_socket closesocket
#else
    typedef int socket_t;
    #define close_socket close
#endif

int main() {
    #ifdef _WIN32
        WSADATA wsa;
        WSAStartup(MAKEWORD(2,2), &wsa);
    #endif

    socket_t sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    char request[BUFFER_SIZE], response[BUFFER_SIZE];

    printf("Enter command (SHORTEN <url> / EXPAND <short_url>): ");
    fgets(request, BUFFER_SIZE, stdin);
    request[strcspn(request, "\n")] = 0;  // Remove newline

    send(sock, request, strlen(request), 0);
    recv(sock, response, BUFFER_SIZE, 0);

    printf("%s\n", response);

    close_socket(sock);

    #ifdef _WIN32
        WSACleanup();
    #endif

    return 0;
}
