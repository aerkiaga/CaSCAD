#include "ast.h"
#include "cascad.h"
#include "compiler.h"
#include "context.h"
#include "deps.h"
#include "interpreter.h"
#include "lexer.h"
#include "parser_interface.h"
#include <stdio.h>
#include <stdlib.h>

cascad_ast_t cascad_load_file(FILE* file) {
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    char *buffer = (char*) malloc(file_size + 1);
    rewind(file);
    size_t read_size = fread(buffer, 1, file_size, file);
    if(read_size != file_size) {
        free(buffer);
        return NULL;
    }
    buffer[file_size] = '\0';
    cascad_ast_t r = cascad_load_string(buffer);
    free(buffer);
    return r;
}

cascad_ast_t cascad_load_string(const char *buffer) {
    lexer_load(buffer);
    ast_t tree = parser_run();
    return (cascad_ast_t) tree;
}

cascad_deps_t cascad_load_deps(const cascad_ast_t ast, const char *script_path) {
    return (cascad_deps_t) get_deps_from_ast((ast_t) ast, script_path);
}

cascad_context_t cascad_gen_context(cascad_ast_t ast, const char *script_path) {
    return (cascad_context_t) compiler_produce((ast_t) ast, script_path);
}

cascad_context_t cascad_gen_context_with_deps(
    cascad_ast_t ast, const char *script_path, cascad_deps_t deps
) {
    return (cascad_context_t) compiler_produce_with_deps((ast_t) ast, (deps_t) deps, script_path);
}

void cascad_execute(cascad_context_t context) {
    interpreter_execute((context_t) context);
}


