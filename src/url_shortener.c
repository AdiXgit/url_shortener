//converts long urls to short ones using base62 encoding.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hash_table.h"
#include "url_shortener.h"

const char BASE62[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

void generate_short_url(char* short_url,unsigned int id){
    for(int i = 0;i<6;i++){
        short_url[i] = BASE62[id % 62];
        id /= 62;
    }
    short_url[6] = '\0';
}

char* shorten_url(const char* long_url){
    unsigned int id = 0;
    char* shorten_url = (char*)malloc(7);
    generate_short_url(shorten_url,id);
    insert_url(shorten_url,long_url);
    return shorten_url;
}

