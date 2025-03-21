#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

#define TABLE_SIZE 1000

typedef struct Entry {
    char short_url[7];
    char long_url[2048];
    struct Entry* next;
} Entry;

Entry* hash_table[TABLE_SIZE];

unsigned int hash(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key++;
    }
    return hash % TABLE_SIZE;
}

void insert_url(const char* short_url, const char* long_url) {
    unsigned int index = hash(short_url);
    Entry* new_entry = (Entry*)malloc(sizeof(Entry));
    strcpy(new_entry->short_url, short_url);
    strcpy(new_entry->long_url, long_url);
    new_entry->next = hash_table[index];
    hash_table[index] = new_entry;
}

char* lookup_url(const char* short_url) {  // Function remains as lookup_url
    unsigned int index = hash(short_url);
    Entry* entry = hash_table[index];
    while (entry) {
        if (strcmp(entry->short_url, short_url) == 0) {
            return entry->long_url;  // Return the long URL
        }
        entry = entry->next;
    }
    return "Not Found";  // URL not found
}
