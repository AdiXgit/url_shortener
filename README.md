# URL Shortener in C

A simple URL shortener implemented in C using a hash table for storing mappings between short and long URLs. The project includes a TCP server and client for interaction.

## Features

- **In-memory storage** using a hash table.
- **Base62 encoding** for generating short URLs.
- **Client-server communication** using TCP sockets.
- **Multi-threaded server** to handle multiple client requests.

## Compilation and Running

### Prerequisites

- GCC Compiler (MinGW for Windows)
- Windows: Link with `-lws2_32` for Winsock support

### Compilation

```sh
gcc -o server.exe src/server.c src/hash_table.c src/url_shortener.c -Iinclude -lws2_32
gcc -o client.exe src/client.c -Iinclude -lws2_32
```
 -then run ./server.exe in one terminal and ./clinet.exe in another terminal 
 
