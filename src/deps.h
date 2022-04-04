#ifndef DEPS_H
#define DEPS_H

#include "ast.h"
#include "tree.h"

/* Format: (realpath  ast)... */
typedef tree_t deps_t;

/* By default, /usr/share/cascad/libraries */
/* Separate different paths with colons */
extern char *libraries_path_list;

extern deps_t create_empty_deps();
extern deps_t add_deps_from_ast(deps_t old_deps, const ast_t ast, const char *script_path);
extern deps_t get_deps_from_ast(const ast_t ast, const char *script_path);
extern tree_t find_path_in_dependencies(const char *path, deps_t deps, const char *script_path);

#endif // DEPS_H
