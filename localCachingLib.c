#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "localCachingLib.h"

//Type based cache

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

//Typeless cache

//Returns a ready to use typeless cache
struct typelessCache createTypelessCache(char* filename){
    struct typelessCache result;
    result.filename = filename;
    result.len = 0;
    return result;
}

//Writes the given element at the end of the cache.
int writeTypeless(struct typelessCache* cache, void* val, size_t size){
    FILE* cacheP = fopen(cache->filename, "ab");
    if(cacheP != NULL){
        fwrite(val, size, 1, cacheP); //write the actual value
        fwrite(typelessDelimiter, delimiterSize, delimiterLen, cacheP);
        fclose(cacheP);
        cache->len += 1;
        return 0;
    }
    else{
        return -1;
    }
}

//Reads a single element from the typeless cache at offset with offset being the number of elements in cache preceding the one we want read
void* readTypeless(struct typelessCache* cache, int offset){
    if(offset > cache->len - 1){
        return NULL;
    }
    FILE* cacheP = fopen(cache->filename, "rb");
    if(cacheP != NULL){
        fseek(cacheP, 0, SEEK_END);
        long fsize = ftell(cacheP); //get the file size
        fseek(cacheP, 0, SEEK_SET);
        //The unsigned is there to differentiate from the normal char
        unsigned char *contents = malloc(fsize + 1); //a char holds exactly 1 byte. 
        fread(contents, fsize, 1, cacheP);
        fclose(cacheP);
        int n = 0;
        while(offset > 0){
            if(contents[n] == EOF){
                return NULL;
            }
            if(isDelimit((contents + n))){
                offset--;
            }
            n++;
        }
        char* results = malloc(0); //initiate the pointer for reallo
        int i = n;
        while(!isDelimit((contents + i))){
            results = realloc(results, i + 1);
            results[i] = contents[i];
            //fprintf(stderr, "%d", contents[i]);
            i++;
        }
        free(contents);
        return (void*)results;
    }
    else{
        return NULL;
    }
}

//Removes all data in typeless cache
int wipeTypeless(struct typelessCache* cache){
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

//Deletes the typeless cache
int freeTypeless(struct typelessCache* cache){
    return remove(cache->filename);
}
