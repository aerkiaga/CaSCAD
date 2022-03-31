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

tree_t tree_append_sibling(tree_t tree, tree_t node) {
    if(!tree) return NULL;
    if(!node) return NULL;
    tree[0].u++;
    tree = (tree_t) realloc(tree, (tree[0].u + 1) * sizeof(union tree_child_t));
    tree[tree[0].u] = *node;
    return tree;
}

tree_t tree_append_children(tree_t tree, tree_t children) {
    if(!tree) return NULL;
    if(!children) return NULL;
    tree_t node;
    node->a = children;
    tree = tree_append_sibling(tree, node);
    return tree;
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
