#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hash_table.h"
#define TABLE_SIZE 1000

//this code mainly handles the storage of shortened urls.

typedef struct url_node{
    char short_url[7];
    char long_url[2048];
    struct url_node* next;  // Added the missing next pointer
} url_node;

url_node* hash_table[TABLE_SIZE] = {NULL};  

unsigned int hash_function(const char* str){
    unsigned int hash  = 5381;
    while(*str)
        hash = ((hash << 5) + hash) + *str++;
    return hash % TABLE_SIZE;
}

void insert_url(const char* short_url,const char*long_url){
    unsigned int index = hash_function(short_url);
    url_node* new_node = (url_node*)malloc(sizeof(url_node));
    strcpy(new_node->short_url,short_url);
    strcpy(new_node->long_url,long_url);
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
}

char* get_url(const char* short_url){
    unsigned int index = hash_function(short_url);
    url_node* current = hash_table[index];
    while(current){
        if(strcmp(current->short_url,short_url) == 0)
            return current->long_url;
        current = current->next;
    }
    return NULL;
}
