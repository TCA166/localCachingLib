#include <stdlib.h>
#include <stdio.h>
#include "localCachingLib.h"

int main(){
    struct cache intArr = createCache(sizeof(int), "cache.bin");

    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[5] = {6, 7, 8, 9, 10};

    writeToCache(arr1, &intArr, 5);
    writeToCache(arr2, &intArr, 5);

    //Tu możemy zwolnić pamięć arr1, arr2

    int* arr3 = (int*)(readFromCache(&intArr, 10, 0));

    printf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", arr3[0], arr3[1], arr3[2], arr3[3], arr3[4], arr3[5], arr3[6], arr3[7], arr3[8], arr3[9]);

    free(arr3);

    wipeCache(&intArr);
    freeCache(&intArr);

    struct typelessCache typeless = createTypelessCache("typeless.bin");

    writeTypeless(&typeless, arr1, sizeof(int));

    writeTypeless(&typeless, arr1 + 1, sizeof(int));

    int* res1 = (int*)readTypeless(&typeless, 0);

    int* res2 = (int*)readTypeless(&typeless, 1);

    printf("%d, %d", (int)*res1, (int)*res2); //the data conversion will need to be done manually by you

    free(res1);
    free(res2);

    //wipeTypeless(&typeless);
    //freeTypeless(&typeless);

    return 0;
}