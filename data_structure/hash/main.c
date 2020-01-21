//
//  main.c
//  day11_hash
//
//  Created by 户有福 on 2020/1/12.
//  Copyright © 2020 户有福. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "hash.h"
#include <time.h>

/// @brief A wrapper for getting the current time.
/// @returns The current time.
struct timespec snap_time()
{
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return t;
}

/// @brief Calculates the time difference between two struct timespecs
/// @param t1 The first time.
/// @param t2 The second time.
/// @returns The difference between the two times.
double get_elapsed(struct timespec t1, struct timespec t2)
{
    double ft1 = t1.tv_sec + ((double)t1.tv_nsec / 1000000000.0);
    double ft2 = t2.tv_sec + ((double)t2.tv_nsec / 1000000000.0);
    return ft2 - ft1;
}
void test(){
    int key_count = 1000000;
    int i;
    char **keys=malloc(sizeof(char *)*key_count);
    char **values=malloc(sizeof(char *)*key_count);


    for(i = 0; i < key_count; i++)
    {
        char *key=malloc(sizeof(char)*15);
        char *value=malloc(sizeof(char)*15);
        sprintf(key, "name-%d",i);
        sprintf(value, "value-%d",i);
        keys[i] = key;
        values[i]=value;
    }
    struct timespec t1;
    struct timespec t2;
    hashTable *ht=malloc(sizeof(hashTable));
    hash_init(ht);

    t1 = snap_time();
    for(int i=0;i<key_count;i++){
        hash_insert(ht, keys[i], values[i]);
    }
    t2 = snap_time();
    fprintf(stderr, "Inserting %d keys took %.2f seconds\n", key_count, get_elapsed(t1, t2));
    
    //hash_display(ht);
    hash_destroy(ht);
    
    free(keys);
    free(values);
}

int main() {
    //printf("%ld",sizeof(bucket*));
    for(int i=0;i<100;i++){
        printf("开始测试........%d\n",i);
        test();
        //sleep(1);
    }
    
    sleep(100);
    return 0;
}
