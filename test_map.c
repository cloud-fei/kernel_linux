#include "rbtree.h"
#include "map.h"
#include <stdio.h>
#include <unistd.h>

rb_root_t user_quota = RB_ROOT;
rb_root_t group_quota = RB_ROOT;

int main() {
    int key1 = 200000;
    int word1 = 1048576;
    put(&user_quota, &key1, &word1);

    int key2 = 199999;
    int word2 = 1073741824;
    put(&group_quota, &key2, &word2);


    int key3 = 199998;
    int word3 = 1024;
    put(&group_quota, &key3, &word3);

    int key4 = 199997;
    unsigned int key4_key;
    unsigned int key4_val;

    map_t *data1 = get(&user_quota, &key1);
    if (data1 != NULL){
        printf("user_quota data1->key:  %d\n", *(data1->key));
        printf("user_quota data1->val:  %d\n\n", *(data1->val));
    }else{
        printf("group_quota data1: not exit\n\n");
    }

    map_t *data2 = get(&group_quota, &key2);
    if (data2 != NULL){
        printf("user_quota data2->key:  %d\n", *(data2->key));
        printf("group_quota data2->val:  %d\n\n", *(data2->val));
    }
        
    
    map_t *data3 = get(&group_quota, &key3);
    if (data3 != NULL){
        printf("group_quota data3->key:  %d\n", *(data3->key));
        printf("group_quota data3->val:  %d\n\n", *(data3->val));
    }
        

    map_t *data4 = get(&group_quota, &key4);
    if (data4 != NULL){
        key4_key = *(data4->key);
        key4_val = *(data4->val);
        printf("group_quota data4->key:  %d\n", key4_key);
        printf("group_quota data4->val:  %d\n", key4_val);
    }else{
        printf("group_quota data4: not exit\n\n");
    }
        
    
    //遍历
    map_t *node1;
    for (node1 = map_first(&group_quota); node1; node1=map_next(&(node1->node))) {
        printf("group_quota: %d\n", *(node1->key));
    }
 
    // free map if you don't need
    // map_t *nodeFree = NULL;
    // for (nodeFree = map_first(&group_quota); nodeFree; nodeFree = map_first(&group_quota)) {
    //     if (nodeFree) {
    //         rb_erase(&nodeFree->node, &group_quota);
    //         map_free(nodeFree);
    //     }
    // }
    return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
