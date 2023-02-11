#include <stdio.h>
#include <stdlib.h>
#include "localCachingLib.h"

//Returns a ready to use cache
struct cache createCache(size_t size, char filename[]){
    struct cache newCache;
    newCache.size = size;
    newCache.filename = filename;
    newCache.len = 0;
    return newCache;
}

//Writes the provided value into cache
int writeToCache(void* val, struct cache* cache, int len){
    FILE* cacheP = fopen(cache->filename, "ab");
    if(cacheP != NULL){
        fwrite(val, cache->size, len, cacheP);
        fclose(cacheP);
        cache->len += len;
        return 0;
    }
    else{
        return -1;
    }
}

//Reads len elements of cache.size from cache at offset
void* readFromCache(struct cache* cache, int len, int offset){
    FILE* cacheP = fopen(cache->filename, "rb");
    int ret = fseek( cacheP, offset, SEEK_SET );
    if(ret != 0){
        return NULL;
    }
    void* result = calloc(cache->size, len);
    fread(result, cache->size, len, cacheP);
    fclose(cacheP);
    return result;
}

//Removes all data in cache
int wipeCache(struct cache* cache){
    FILE* cacheP = fopen(cache->filename, "wb");
    if(cacheP != NULL){
        fclose(cacheP);
        cache->len = 0;
        return 0;
    }
    else{
        return -1;
    }
}

//Deletes the cache
int freeCache(struct cache* cache){
    return remove(cache->filename);
}

//Reads all data in cache
void* readAllFromCache(struct cache* cache){
    FILE* cacheP = fopen(cache->filename, "rb");
    void* result = calloc(cache->size, cache->len);
    fread(result, cache->size, cache->len, cacheP);
    fclose(cacheP);
    return result;
}