#ifndef _localCachingLib_H_
#define _localCachingLib_H_
    //A cache object that stores the associated filename, the size of one element in cache and the amount of elements in cache
    struct cache{
        char* filename; //Associated filename
        size_t size; //The size of one element in cache
        int len; //The number of elements in cache
    };

    //Returns a ready to use cache
    extern struct cache createCache(size_t size, char filename[]);

    //Writes the provided value into cache
    extern int writeToCache(void* val, struct cache* cache, int len);

    //Reads len elements of cache.size from cache at offset
    extern void* readFromCache(struct cache* cache, int len, int offset);

    //Removes all data in cache
    extern int wipeCache(struct cache* cache);

    //Deletes the cache
    extern int freeCache(struct cache* cache);

    //Reads all data in cache
    extern void* readAllFromCache(struct cache* cache);

#endif