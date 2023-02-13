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


## Typeless vs Normal caches

This library has two very similar structs and associated functions. Normal caches and typeless caches. 
So far the examples have only shown how to use the normal caches. That is because typeless caches are less reliable and there is a lot more that can go wrong.
Normal caches are essentially files with a memory representation of an array. Since each element has a given size reading them is easy and painless.
Typeless caches hovewer while allowing for variable element size, are forced to seperate each element with a delimiter, making reading them a lot more problematic and prone to errors.
The delmiter is by default a string "\0\10" and since it's a string there's a third hidden null character. This is a rather distinct combination that shouldn't overlap with most data.

### Redefining the delimiter

In order to redefine the delimiter you have to redefine the following macros that are in the localCachingLib.h

```C
    #define typelessDelimiter "\0\10"
    #define delimiterSize 3 * sizeof(char)
    #define delimiterLen 3
    #define isDelimit(a) (a[0] == typelessDelimiter[0] && a[1] == typelessDelimiter[1] && a[2] == typelessDelimiter[2])
```

## How to use typeless Caches

They function very similarly to normal caches, except you can't write multiple elements at a time to limit the amount of things that can go wrong.  
Here's an example use case:

```C
    struct typelessCache typeless = createTypelessCache("typeless.bin");

    writeTypeless(&typeless, arr1, sizeof(int));

    int* res = (int*)readTypeless(&typeless, 0);

    printf("\n%d", *res);

    free(res);

    wipeTypeless(&typeless);
    freeTypeless(&typeless);
```
