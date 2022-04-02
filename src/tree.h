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
extern tree_t tree_append_sibling(tree_t tree, const tree_t node) __attribute__ ((warn_unused_result));
extern tree_t tree_append_children(tree_t tree, const tree_t children) __attribute__ ((warn_unused_result));
extern tree_t tree_remove_last_sibling(tree_t tree) __attribute__ ((warn_unused_result));
extern void tree_delete_siblings(tree_t tree);
extern void tree_delete_children(tree_t tree);
extern size_t tree_node_sibling_count(tree_t tree);
extern size_t tree_node_child_count(tree_t tree);
extern tree_t tree_node_sibling(tree_t tree, size_t index);
extern tree_t tree_node_child(tree_t tree, size_t index);

/*
 *  EXPLANATION
 *
 *  This function will perform a Depth-First Search on `tree`.
 *  It will call `fn` the first time it visits a node (preorder).
 *  It will call `fn2` the last time it visits a node (postorder).
 *  Both functions will get a pointer to the node as `node`.
 *  Both functions will get the index of the node amongst its siblings.
 *  Both functions will get the same `data` value that was passed to the function.
 *  Both functions will get a `common` pointing to a variable unique to each set of siblings.
 *  Both functions can return a positive or negative integer value.
 *  The search will advance as many siblings as the sum of the two values.
 *  For `fn`, zero is equivalent to one, but child nodes will be explored recursively.
 *
 *  e.g.    returning 0 and 0 means 'keep searching normally'.
 *          returning 1 and 0 means 'don't expand children, go to next sibling
 *          returning 0 and 1 means 'don't expand children, go to next sibling
 *          returning 1 and 1 means 'don't expand children, skip next node'
 *          returning 2 and -2 means 'don't expand children, repeat this node'
 *          returning 0 and INT_MAX means 'expand children, skip all siblings'
 */
extern int tree_walk(
    tree_t tree,
    int (*fn)(tree_t node, size_t index, void *data, void **common),
    int (*fn2)(tree_t node, size_t index, void *data, void **common),
    void *data
);

#endif // TREE_H
