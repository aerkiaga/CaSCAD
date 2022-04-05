#include <stdio.h>

#define CASCAD_NOTICE \
PACKAGE_STRING "\n" \
"Copyright (C) 2022 Aritz Erkiaga Fernández\n" \
"License GPLv3: GNU GPL version 3 <https://gnu.org/licenses/gpl-3.0.html>\n" \
"This is free software: you are free to change and redistribute it.\n" \
"There is NO WARRANTY, to the extent permitted by law.\n"

/* Set a custom function to display error, warning and info messages. */
/* Variable `type` will be 'e', 'w' and 'i', respectively. */
void set_message_handler(void (*handler)(char type, const char *msg));

/* An Abstract Syntax Tree, created from parsing SCAD code. */
typedef struct t_cascad_ast_t *cascad_ast_t;

/*
 *  EXAMPLE CODE
 *
 *  cascad_ast_t example_open_file(const char *filename) {
 *      FILE *input = fopen(filename, "rt");
 *      cascad_ast_t ast = cascad_load_file(input);
 *      fclose(input);
 *      return ast;
 *  }
 *  
 */

/* Parse file and output an Abstract Syntax Tree. */
extern cascad_ast_t cascad_load_file(FILE *file);

/* Parse string and output an Abstract Syntax Tree. */
extern cascad_ast_t cascad_load_string(const char* buffer);

/* Print a representation of the Abstract Syntax Tree to stderr. */
void cascad_print_ast(cascad_ast_t ast);

/* A list of dependencies for one or more scripts. */
/* Includes their canonical paths and Abstract Syntax Trees. */
typedef struct t_cascad_deps_t *cascad_deps_t;

/* Load and parse all dependencies of `ast`. */
/* Dependencies are searched relative to `script_path` or in library paths. */
/* Passing `NULL` as `script_path` will only search in library paths. */
extern cascad_deps_t cascad_load_deps(const cascad_ast_t ast, const char *script_path);

/* An interpreter context, containing all data necessary to run a script. */
typedef struct t_cascad_context_t *cascad_context_t;

/* Compile Abstract Syntax Tree into an interpreter context. */
/* Equivalent to `cascad_gen_context_using_deps(ast, script_path, cascad_load_deps(ast, script_path))`. */
extern cascad_context_t cascad_gen_context(cascad_ast_t ast, const char *script_path);

/* Compile Abstract Syntax Tree into an interpreter context. */
/* The provided `deps` must contain at least all dependencies for the loaded script. */
/* This allows sharing loaded dependencies across many contexts. */
extern cascad_context_t cascad_gen_context_with_deps(
    cascad_ast_t ast, const char *script_path, cascad_deps_t deps
);

/*
 *  EXAMPLE CODE
 *
 *  void example_get_contexts(cascad_ast_t ast, const char *script_path) {
 *      cascad_context_t ctx1 = cascad_gen_context(ast, script_path);
 *      cascad_context_t ctx2 = cascad_gen_context(ast, script_path);
 *      ...
 *  }
 *  
 */

/* Print a representation of the compiled bytecode to stderr. */
void cascad_print_bytecode(cascad_context_t context);

/* An empty or solid shape. */
// TODO: add other types
typedef struct t_cascad_shape_t *cascad_shape_t;

/* Run an interpreter context. */
extern cascad_shape_t cascad_execute(cascad_context_t context);

/* Export a shape as STL file, either ascii or binary. */
int cascad_export_stl(cascad_shape_t shape, const char *path, int ascii);

/* A value indicating what type a shape is. */
enum cascad_shape_type_t {
    CASCAD_INVALID,
    CASCAD_EMPTY,
    CASCAD_SOLID
};

/* Query the shape type of a shape. */
extern enum cascad_shape_type_t cascad_get_shape_type(cascad_shape_t shape);

/* Call cascad_load_string, cascad_gen_context and cascad_execute in another thread. */
/* The function `later` is called with the eventual resulting shape. */
extern void cascad_run_string_async(
    const char* buffer, const char *filename, void (*later)(cascad_shape_t)
);

