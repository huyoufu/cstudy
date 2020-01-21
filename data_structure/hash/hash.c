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
int table_size_for(unsigned int cap) {
    if (cap<=0) {
        return 2;
    }
    int n = cap - 1;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return (n < 0) ? 1 : n + 1;
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
    ht->cap        = cap;
    ht->elem_num    = 0;
    ht->used=0;
    //将桶的指针指向一个初始化好指针
    //目的是分配好一堆指针 实际上就是指针数组
    ht->buckets  = (bucket **)calloc(ht->cap, sizeof(bucket *));
    
    if(ht->buckets == NULL) return 0;
    return 1;
}
int _hash_insert(hashTable *ht, bucket * ca_bucket)
{
    // get the key  in the tabs
    int index = get_tb_index(ht->cap, ca_bucket->key);
    bucket *org_bucket=ht->buckets[index];
    
    ht->elem_num += 1;
    if(org_bucket != NULL)
    {
        ca_bucket->next = org_bucket;
    }else{
        ht->used++;
    }
    ht->buckets[index]= ca_bucket;
    return 1;
}
hashTable * resize_hash_table_if_needed(hashTable *ht){
    
    if(ht->used>=ht->cap*DEFAULT_LOAD_FACTOR){
        //开始扩容
        //printf("当前容量:%d--已使用:%d--扩容到:%d\n",ht->cap,ht->used,ht->cap*2);
        //创建一个hashtab;
        hashTable *new_ht=malloc(sizeof(hashTable));
        _hash_init(new_ht, ht->cap*2);
        //遍历原来的元素
        //插入到新的hashtab中;
        for (int i=0; i<ht->cap; i++) {
            //遍历数组 删除
            bucket *bucket_head=ht->buckets[i];
            while(bucket_head!=NULL){
                bucket *tmp_bucket=bucket_head->next;
                bucket_head->next=NULL;
                _hash_insert(new_ht, bucket_head);
                bucket_head=tmp_bucket;
            }
        }
        free(ht->buckets);
        ht->cap=new_ht->cap;
        ht->elem_num=new_ht->elem_num;
        ht->used=new_ht->used;
        ht->buckets=new_ht->buckets;
        free(new_ht);
    }
    return ht;
}
bucket * create_bucket(char * key,void * value)
{
    bucket *bucketv = malloc(sizeof(bucket));
    bucketv->key   = key;
    bucketv->value = value;
    bucketv->next  = NULL;
    return bucketv;
}


int hash_insert(hashTable *ht, char *key, void *value)
{
    // get the key  in the tabs
    int index = get_tb_index(ht->cap, key);
    
    bucket *org_bucket=ht->buckets[index];
    bucket *tmp_bucket=org_bucket;
    //printf("当前桶的首指针:%p--",org_bucket);
    
    // check if the key exits already
    while(tmp_bucket!=NULL)
    {
        if(strcmp(key, tmp_bucket->key) == 0)
        {
            tmp_bucket->value = value;
            //先释放原来的key 和value的值 不然会导致内存泄漏
            free(tmp_bucket->key);
            free(tmp_bucket->value);
            tmp_bucket->key=key;
            tmp_bucket->value=value;
            return 1;
        }
        tmp_bucket = tmp_bucket->next;
    }
    bucket *bucketv = create_bucket(key,value);
    ht->elem_num += 1;
    if(org_bucket != NULL)
    {
        bucketv->next = org_bucket;
    }else{
        ht->used++;
    }
    ht->buckets[index]= bucketv;
    // check if we need to resize the hashtable
    resize_hash_table_if_needed(ht);
    return 1;
}

void * hash_lookup(hashTable *ht, char *key)
{
    int index = get_tb_index(ht->cap, key);
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
    for (i=0; i<ht->cap; i++) {
        
        //遍历数组 删除
        bucket *bucket_head=ht->buckets[i];
        while(bucket_head!=NULL){
            
            printf("\nkey的值:%s--",bucket_head->key);
            
            printf("value的值:%s\n",bucket_head->value);
            bucket_head=bucket_head->next;
        }
    }
    return 1;
}

int hash_destroy(hashTable *ht){
    //销毁hashtab
    //遍历所有桶数组
    bucket **bucket_arr=ht->buckets;
    int xcnt=0;
    int len=ht->cap;
    for(int i=0;i<len;i++){
        bucket *bucket_head=bucket_arr[i];
        while(bucket_head!=NULL){
            bucket *tmp=bucket_head->next;
            xcnt++;
            free(bucket_head->key);
            free(bucket_head->value);
            free(bucket_head);
            bucket_head=tmp;
        }
    }
    //释放桶指针数组 防止内存泄漏
    free(bucket_arr);
    free(ht);
    //printf("共销毁了:%d个元素\n",xcnt);
    return 1;
}

