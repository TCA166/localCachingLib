# localCachingLib

A library for storing variables in local binary files as opposed to RAM.

## How to use it

1. Create a cache struct
    Each cache struct has a filename associated with it (it's your responsibility to ensure that caches do not share names), and a size of one element.
    This effectively means that each cache has an associated type like int. Ideally you name them to make it clear what type each cache is.
    ```C
    struct cache intArr = createCache(sizeof(int), "cache.bin");
    ```
2. Write something to the cache.
    Variables can be written to the cache almost as if it is an array
    ```C
    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[5] = {6, 7, 8, 9, 10};

    writeToCache(arr1, &intArr, 5);
    writeToCache(arr2, &intArr, 5);
    ```
    In this example the intArr cache holds now an array of 10 ints
3. Read something from the cache
    Reading things from the cache is also rather easy.
    ```C
    printf("%d", arr1[1]) //prints 2
    printf("%d", (int)(readFromCache(&intArr, 1, 1))) //prints 2
    ```
4. Delete the cache
    When your program stops execution the struct will be of course automaticly lost. Hovewer the file will remain. So the same way it's good practice to free everything at the end of the program, it's also good practice to freeCache each cache you have created

