#include "ast.h"
#include "cascad.h"
#include "deps.h"
#include "strutils.h"
#include "tree.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void error(const char *fmt, ...);

/* By default, /usr/share/cascad/libraries */
/* Separate different paths with colons */
char *libraries_path_list = PATH_DATADIR "/cascad/libraries";

static int dependencies_walk_fn(ast_t node, size_t index, void *data, void **common) {
    tree_t *list = (tree_t *) data;
    if(index == 0) {
        switch(node->u) {
            case AST_TYPE_STATEMENT_LIST:
                return 1;
            case AST_TYPE_MODULE_OPERATOR:
            case AST_TYPE_PRE_OPERATOR:
            case AST_TYPE_IF_STATEMENT:
            case AST_TYPE_FOR_STATEMENT:
            case AST_TYPE_INTERSECTION_FOR_STATEMENT:
            case AST_TYPE_LET_STATEMENT:
            case AST_TYPE_MODULE_LITERAL:
                return 2;
            case AST_TYPE_BIND_STATEMENT:
                if(node[2].a[1].u == AST_TYPE_MODULE_LITERAL) return 2;
                else return INT_MAX;
            case AST_TYPE_INCLUDE_STATEMENT:
            case AST_TYPE_USE_STATEMENT:
                *list = tree_append_children(*list, NULL);
                (*list)[(*list)[0].u].s = strdup(node[1].s);
                return INT_MAX;
            default:
                return INT_MAX;
        }
    }
    return 0;
}

tree_t get_raw_dependency_list(const ast_t ast) {
    tree_t r = tree_new_siblings(0);
    ast_walk(ast, dependencies_walk_fn, NULL, (void *) &r);
    return r;
}

char *try_expand_dependency_path(const char *relative, const char *script_path) {
    if(script_path) {
        char *script_dir = append_string(path_dirname(script_path), "/");
        char *local_path = append_string(script_dir, relative);
        char *real_local_path = path_realpath(local_path);
        free(local_path);
        if(real_local_path) {
            return real_local_path;
        }
        free(real_local_path);
    }
    const char *libraries_path_list_ptr = libraries_path_list;
    for(;;) {
        size_t span = strcspn(libraries_path_list_ptr, ":");
        char *library_dir = append_string(strndup(libraries_path_list_ptr, span), "/");
        char *lib_path = append_string(library_dir, relative);
        char *real_lib_path = path_realpath(lib_path);
        free(lib_path);
        if(real_lib_path) {
            return real_lib_path;
        }
        free(real_lib_path);
        libraries_path_list_ptr += span;
        if(*libraries_path_list_ptr == '\0') break;
        libraries_path_list_ptr++;
    }
    error("error: couldn't find file '%s', included/used from %s\n", relative, script_path);
    return NULL;
}

int convert_raw_to_realpath(tree_t deps, const char *script_path) {
    size_t index;
    for(index = 1; index <= deps[0].u; index++) {
        char *raw_path = deps[index].s;
        char *real_path = try_expand_dependency_path(raw_path, script_path);
        if(!real_path) return 1;
        free(deps[index].s);
        deps[index].s = real_path;
    }
    return 0;
}

deps_t create_empty_deps() {
    return tree_new_siblings(0);
}

deps_t add_deps_from_ast(deps_t old_deps, const ast_t ast, const char *script_path) {
    tree_t file_deps = get_raw_dependency_list(ast);
    if(convert_raw_to_realpath(file_deps, script_path)) {
        return NULL;
    }
    size_t new_index;
    for(new_index = 1; new_index <= file_deps[0].u; new_index++) {
        char *new_dep_ptr = file_deps[new_index].s;
        /* Make sure there are no duplicates. */
        size_t old_index;
        int exists = 0;
        for(old_index = 1; !exists && old_index < old_deps[0].u; old_index += 2) {
            const char *old_dep_ptr = old_deps[old_index].s;
            if(!strcmp(new_dep_ptr, old_dep_ptr)) exists = 1;
        }
        if(!exists) {
            FILE *file = fopen(new_dep_ptr, "rt");
            if(!file) {
                return NULL;
            }
            ast_t new_ast = (ast_t) cascad_load_file(file);
            fclose(file);
            if(!new_ast) {
                return NULL;
            }
            union tree_child_t new_node;
            new_node.s = new_dep_ptr;
            old_deps = tree_append_sibling(old_deps, &new_node);
            new_node.a = new_ast;
            old_deps = tree_append_sibling(old_deps, &new_node);
            add_deps_from_ast(old_deps, new_ast, new_dep_ptr);
        }
    }
    return old_deps;
}

deps_t get_deps_from_ast(const ast_t ast, const char *script_path) {
    deps_t r = create_empty_deps();
    r = add_deps_from_ast(r, ast, script_path);
    if(!r) {
        return NULL;
    }
    return r;
}

tree_t find_path_in_dependencies(const char *path, deps_t deps, const char *script_path) {
    /* We can assume the dependency exists. */
    /* So it's only a matter of returning the right value. */
    tree_t r = NULL;
    /* First, try without looking at the filesystem. */
    size_t i;
    const char *base = path_basename(path);
    for(i = 1; i <= deps[0].u; i += 2) {
        if(!strcmp(base, path_basename(deps[i].s))) {
            if(!r) r = deps + i;
            else {
                r = NULL;
                break;
            }
        }
    }
    if(r) return r;
    /* Secondly, do it by working with the filesystem. */
    char *full_path = try_expand_dependency_path(path, script_path);
    if(!full_path) return NULL;
    for(i = 1; i <= deps[0].u; i += 2) if(!strcmp(full_path, deps[i].s)) return deps + i;
    return NULL;
}

