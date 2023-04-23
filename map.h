
#ifndef _MAP_H
#define _MAP_H

#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <string.h>

struct map {
    struct rb_node node;
    int *key;
    int *val;
};

typedef struct map map_t;
typedef struct rb_root rb_root_t;
typedef struct rb_node rb_node_t;

map_t *get(rb_root_t *root, int *str) {
   rb_node_t *node = root->rb_node; 
   while (node) {
        map_t *data = container_of(node, map_t, node);

        //compare between the key with the keys in map
        int cmp = str - data->key;
        if (cmp < 0) {
            node = node->rb_left;
        }else if (cmp > 0) {
            node = node->rb_right;
        }else {
            return data;
        }
   }
   return NULL;
}

int put(rb_root_t *root, int* key, int* val) {
    map_t *data = (map_t*)malloc(sizeof(map_t));
    data->key = (int*)malloc(sizeof(int));
    data->key = key;
    data->val = (int*)malloc(sizeof(int));
    data->val = val;
    
    rb_node_t **new_node = &(root->rb_node), *parent = NULL;
    while (*new_node) {
        map_t *this_node = container_of(*new_node, map_t, node);
        int result = key - this_node->key;
        printf("key:%d ,this_node->key:%d, result:%d\n", *(key), *(this_node->key), result);
        parent = *new_node;

        if (result < 0) {
            new_node = &((*new_node)->rb_left);
        }else if (result > 0) {
            new_node = &((*new_node)->rb_right);
        }else {
            this_node->val = val;
            free(data);
            return 0;
        }
    }

    rb_link_node(&data->node, parent, new_node);
    rb_insert_color(&data->node, root);

    return 1;
}

map_t *map_first(rb_root_t *tree) {
    rb_node_t *node = rb_first(tree);
    return (rb_entry(node, map_t, node));
}

map_t *map_next(rb_node_t *node) {
    rb_node_t *next =  rb_next(node);
    return rb_entry(next, map_t, node);
}

void map_free(map_t *node){
    if (node != NULL) {
        if (node->key != NULL) {
            free(node->key);
            node->key = NULL;
            free(node->val);
            node->val = NULL;
    }
        free(node);
        node = NULL;
    }
}

#endif  //_MAP_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
