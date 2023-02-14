#ifndef _localCachingLib_H_
#define _localCachingLib_H_

    //Type based cache

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

    //Typeless cache

    //the actual value of the delimiter
    #define typelessDelimiter "\0;"
    //size in bytes of the delimiter
    #define delimiterSize 3 * sizeof(char)
    //A macro for checking if the provided pointer points to a delimiter 
    #define isDelimit(a) (a[0] == typelessDelimiter[0] && a[1] == typelessDelimiter[1] && a[2] == typelessDelimiter[2])

    //A cache without a predetermined size of one element. Due to the nature of how data is stored it's best to use the normal cache when possible.
    struct typelessCache{
        char* filename;
        int len;
    };

    //Returns a ready to use typeless cache
    extern struct typelessCache createTypelessCache(char* filename);

    //Writes the given one element from val to cache
    int writeTypeless(struct typelessCache* cache, void* val, size_t size);

    //Reads a single element from the typeless cache at offset with offset being the number of elements in cache preceding the one we want read
    extern void* readTypeless(struct typelessCache* cache, int offset);

    //Removes all data in typeless cache
    int wipeTypeless(struct typelessCache* cache);

    //Deletes the typeless cache
    int freeTypeless(struct typelessCache* cache);
#endif