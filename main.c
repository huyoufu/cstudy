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

int main() {
    
    for(int x=0;x<100;x++){
        hashTable *ht=malloc(sizeof(hashTable));
        hash_init(ht);
        for(int i=1;i<1000;i+=1){

            char *key=malloc(sizeof(char)*100);
            char *value=malloc(sizeof(char)*100);
            sprintf(key, "name-%d",i);
            sprintf(value, "value-%d",i);
            hash_insert(ht, key, value);
            free(key);
            free(value);
        }

        //char *s1=hash_lookup(ht, "name-1");
        printf("第%d次\n",x);
    }
    sleep(100);
    return 0;
}
