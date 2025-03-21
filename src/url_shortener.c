#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "url_shortener.h"

const char BASE62[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

// Function to generate Base62 short URL
void generate_short_url(char* short_url, unsigned int id) {
    int i = 0;

    // Convert ID to Base62
    while (id > 0 && i < 6) {
        short_url[i++] = BASE62[id % 62];
        id /= 62;
    }

    // If ID was small, pad with 'a' at the end
    while (i < 6) short_url[i++] = BASE62[0];

    short_url[i] = '\0';  // Null terminate

    // Reverse the string to maintain correct Base62 order
    for (int j = 0; j < i / 2; j++) {
        char temp = short_url[j];
        short_url[j] = short_url[i - j - 1];
        short_url[i - j - 1] = temp;
    }
}

// Function to retrieve the next ID from a file
unsigned int get_next_id() {
    FILE* file = fopen("id_counter.txt", "r+");
    unsigned int id = 1;

    if (file) {
        fscanf(file, "%u", &id);
        fseek(file, 0, SEEK_SET);
    } else {
        file = fopen("id_counter.txt", "w");
    }

    fprintf(file, "%u", id + 1);
    fclose(file);
    return id;
}

// Function to shorten a URL
char* shorten_url(const char* long_url) {
    unsigned int id = get_next_id();  // Get unique ID
    char* short_url = (char*)malloc(7);
    
    generate_short_url(short_url, id);
    insert_url(short_url, long_url);
    
    return short_url;
}

// Function to expand a short URL
char* expand_url(const char* short_url) {
    return lookup_url(short_url);
}
