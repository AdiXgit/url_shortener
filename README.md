URL Shortener

Overview

A simple URL shortener implemented in C with an in-memory hash-based store. It provides a TCP-based API for shortening and retrieving URLs.

Features

Shortens long URLs using Base62 encoding.

Stores shortened URLs in an in-memory hash table.

Supports retrieving original URLs from shortened ones.

Multi-threaded TCP server to handle client requests.

Project Structure

url_shortener/
├── src/
│   ├── server.c          # TCP server implementation
│   ├── client.c          # Client for testing API
│   ├── url_shortener.c   # URL shortening and expansion logic
│   ├── hash_table.c      # In-memory hash table for storage
├── include/
│   ├── url_shortener.h   # Header for URL shortener functions
│   ├── hash_table.h      # Header for hash table functions
├── Makefile              # Compilation rules
├── README.md             # Project documentation

Compilation & Running

Windows

Open a terminal in the project directory.

Compile the server:

gcc -o server.exe src/server.c src/hash_table.c src/url_shortener.c -Iinclude -lws2_32

Compile the client:

gcc -o client.exe src/client.c -Iinclude -lws2_32

Run the server:

./server.exe

Run the client and interact with the server:

./client.exe

Linux

Compile the server:

gcc -o server src/server.c src/hash_table.c src/url_shortener.c -Iinclude -lpthread

Compile the client:

gcc -o client src/client.c -Iinclude

Run the server:

./server

Run the client:

./client

Usage

Shorten a URL

Enter command (SHORTEN <url>): SHORTEN https://www.google.com
SHORTENED daaaaa

Expand a Shortened URL

Enter command (EXPAND <short_url>): EXPAND daaaaa
EXPANDED https://www.google.com

Future Enhancements

Persistent storage (e.g., saving URLs in a file or database).

Web-based interface.

Custom short URLs.

License

MIT License

