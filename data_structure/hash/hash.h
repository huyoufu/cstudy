//
//  hash.h
//  day11_hash
//
//  Created by 户有福 on 2020/1/13.
//  Copyright © 2020 户有福. All rights reserved.
//

#ifndef hash_h
#define hash_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_DEFAULT_INIT_SIZE 16 //8192*128
//#define DEFAULT_LOAD_FACTOR1 = 0.75f
static float DEFAULT_LOAD_FACTOR=0.75f;
#define BUCKET_INIT_SIZE 8;
//桶
typedef struct _bucket
{
    char *key;
    void *value;
    struct _bucket *next;
} bucket;
 //hash表
typedef struct _hashTable
{
    int used;
    int cap;
    int elem_num;
    bucket** buckets;
} hashTable;
int hash_init(hashTable *ht);                               // 初始化哈希表
int _hash_init(hashTable *ht,int cap);
void * hash_lookup(hashTable *ht, char *key);   // 根据key查找内容
int hash_insert(hashTable *ht, char *key, void *value);     // 将内容插入到哈希表中
int hash_remove(hashTable *ht, char *key);                  // 删除key所指向的内容
int hash_display(hashTable *ht);                            //hash打印
int hash_destroy(hashTable *ht); 
#endif /* hash_h */
