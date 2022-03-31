#ifndef TREE_H
#define TREE_H

#include <stdint.h>
#include <stdlib.h>

typedef union tree_child_t{
    union tree_child_t *a;
    intptr_t i;
    uintptr_t u;
    double d;
    char* s;
    void* p;
} *tree_t;

extern tree_t tree_new_siblings(size_t initial_size);
extern tree_t tree_new_children(tree_t tree, size_t initial_size);
extern tree_t tree_append_sibling(tree_t tree, tree_t node);
extern tree_t tree_append_children(tree_t tree, tree_t children);
extern void tree_delete_siblings(tree_t tree);
extern void tree_delete_children(tree_t tree);
extern size_t tree_node_sibling_count(tree_t tree);
extern size_t tree_node_child_count(tree_t tree);
extern tree_t tree_node_sibling(tree_t tree, size_t index);
extern tree_t tree_node_child(tree_t tree, size_t index);

extern int tree_walk(tree_t tree, int (*fn)(tree_t node, size_t index, void *data), int (*fn2)(tree_t node, size_t index, void *data), void *data);

#endif // TREE_H
