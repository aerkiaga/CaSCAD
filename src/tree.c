#include "tree.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

tree_t tree_new_siblings(size_t initial_size) {
    size_t size_bytes = (initial_size + 1) * sizeof(union tree_child_t);
    tree_t r = (tree_t) malloc(size_bytes);
    memset(r, 0, size_bytes);
    r[0].u = initial_size;
    return r;
}

tree_t tree_new_children(tree_t tree, size_t initial_size) {
    if(!tree) return NULL;
    tree_t r = tree_new_siblings(initial_size);
    tree->a = r;
    return r;
}

tree_t tree_append_sibling(tree_t tree, const tree_t node) {
    if(!tree) return NULL;
    if(!node) return NULL;
    tree[0].u++;
    tree = (tree_t) realloc(tree, (tree[0].u + 1) * sizeof(union tree_child_t));
    tree[tree[0].u] = *node;
    return tree;
}

tree_t tree_append_children(tree_t tree, const tree_t children) {
    if(!tree) return NULL;
    union tree_child_t node;
    node.a = children;
    tree = tree_append_sibling(tree, &node);
    return tree;
}

tree_t tree_remove_last_sibling(tree_t tree) {
    if(!tree) return NULL;
    tree[0].u--;
    // no realloc
    return tree;
}

tree_t tree_resize(tree_t tree, size_t size) {
    if(!tree) return NULL;
    tree[0].u = size;
    return (tree_t) realloc(tree, (size + 1) * sizeof(union tree_child_t));
}

void tree_delete_siblings(tree_t tree) {
    tree[0].u = 0;
    free(tree);
}

void tree_delete_children(tree_t tree) {
    if(!tree) return;
    tree_delete_siblings(tree->a);
    tree->a = NULL;
}

size_t tree_node_sibling_count(tree_t tree) {
    if(!tree) return 0;
    return tree[0].u;
}

size_t tree_node_child_count(tree_t tree) {
    if(!tree) return 0;
    tree = tree->a;
    return tree_node_sibling_count(tree);
}

tree_t tree_node_sibling(tree_t tree, size_t index) {
    if(!tree) return NULL;
    return &tree[index + 1];
}

tree_t tree_node_child(tree_t tree, size_t index) {
    if(!tree) return NULL;
    tree = tree->a;
    return tree_node_sibling(tree, index);
}

int tree_walk(
    tree_t tree,
    int (*fn)(tree_t node, size_t index, void *data, void **common),
    int (*fn2)(tree_t node, size_t index, void *data, void **common),
    void *data
) {
    size_t index;
    int retval = 0;
    void *common = NULL;
    while(index < tree[0].u) {
        retval = fn ? fn(&tree[index + 1], index, data, &common) : 0;
        if(!retval) {
            if(tree[index + 1].a) tree_walk(tree[index + 1].a, fn, fn2, data);
            retval++;
        }
        retval += fn2 ? fn2(&tree[index + 1], index, data, &common) : 0;
        index += retval;
    }
    return retval;
}

