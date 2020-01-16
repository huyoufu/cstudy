//
//  hash.c
//  day11_hash
//
//  Created by 户有福 on 2020/1/13.
//  Copyright © 2020 户有福. All rights reserved.
//

#include "hash.h"
//hash算法
unsigned int hash(char *key)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
    while (*key)
    {
        hash = hash *seed +(*key );
        key ++;
    }
    return (hash & 0x7FFFFFFF);
}
//确保数组的容量是2的指数被 最大不超过64
int table_size_for(int cap) {
    if (cap<=0) {
        return 2;
    }
    int n = cap - 1;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return (n < 0) ? 1 : (n >= 64) ? 64: n + 1;
}
//这里必须保证 n是2的指数 才可以算出正确的索引值
int get_tb_index(int n,char *key){
    return (n-1)&hash(key);
}

int hash_init(hashTable *ht)
{
    return _hash_init(ht, HASH_TABLE_DEFAULT_INIT_SIZE);
}
int _hash_init(hashTable *ht,int cap)
{
    cap=table_size_for(cap);
    ht->size        = cap;
    ht->elem_num    = 0;
    //将桶的指针指向一个初始化好指针
    //目的是分配好一堆指针 实际上就是指针数组
    ht->buckets  = (bucket **)calloc(ht->size, sizeof(bucket *));
    
    if(ht->buckets == NULL) return 0;
    return 1;
}
void resize_hash_table_if_needed(hashTable *ht){
    
    if(ht->elem_num>=ht->size*DEFAULT_LOAD_FACTOR){
        
        
    }
    
}
int hash_insert(hashTable *ht, char *key, void *value)
{
    // check if we need to resize the hashtable
    resize_hash_table_if_needed(ht);
    //获取元素在数组的位置索引
    int index = get_tb_index(ht->size, key);
    //printf("\n当前key:%s----的索引为:%d",key,index);
    bucket *org_bucket=ht->buckets[index];
    bucket *tmp_bucket=org_bucket;
    
    //printf("当前桶的首指针:%p--",org_bucket);

    // check if the key exits already
    while(tmp_bucket!=NULL)
    {
        if(strcmp(key, tmp_bucket->key) == 0)
        {
            tmp_bucket->value = value;
            return 1;
        }
        
        tmp_bucket = tmp_bucket->next;
    }
    
    bucket *bucket = malloc(sizeof(bucket));
    //printf("插入元素的指针为:%p",bucket);
    //char * keyi=malloc(sizeof(char)*strlen(key));
    char * keyi=malloc(sizeof(char)*20);
    strcpy(keyi, key);
    printf("%s\n",keyi);
    //char * valuei=malloc(sizeof(char)*strlen(value));
    char * valuei=malloc(sizeof(char)*20);
    strcpy(valuei, value);
    //printf("%s\n",keyi);
    bucket->key   = keyi;
    bucket->value = valuei;
    bucket->next  = NULL;
    ht->elem_num += 1;
    if(org_bucket != NULL)
    {
        bucket->next = org_bucket;
    }
    ht->buckets[index]= bucket;
    return 1;
}
void * hash_lookup(hashTable *ht, char *key)
{
    int index = get_tb_index(ht->size, key);
    bucket *bucket = ht->buckets[index];
    //    if(bucket == NULL)
    //        return 0;
    while(bucket)
    {
        if(strcmp(bucket->key, key) == 0)
        {
            return bucket->value;
            
        }
        bucket = bucket->next;
    }
    return NULL;
}
int hash_display(hashTable *ht){
    int i;
    for (i=0; i<ht->size; i++) {
        bucket *p_bucket=ht->buckets[i];
        //遍历数组 删除
        if (p_bucket!=NULL) {
            printf("\nkey的值:%s--",p_bucket->key);
            
            printf("value的值:%s\n",p_bucket->value);
        }
        
    }
    
    
    
    
    return 1;
}


