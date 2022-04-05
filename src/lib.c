#include "ast.h"
#include "backend.h"
#include "cascad.h"
#include "compiler.h"
#include "context.h"
#include "deps.h"
#include "interpreter.h"
#include "lexer.h"
#include "parser_interface.h"
#include "strutils.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

void (*message_override)(char type, const char *msg) = NULL;

void error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    if(message_override) {
        char *buffer = vformatted_string(fmt, args);
        message_override('e', buffer);
        free(buffer);
    } else {
        vfprintf(stderr, fmt, args);
        exit(1);
    }
    va_end(args);
}

void warning(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    if(message_override) {
        char *buffer = vformatted_string(fmt, args);
        message_override('w', buffer);
        free(buffer);
    } else {
        vfprintf(stderr, fmt, args);
    }
    va_end(args);
}

void info(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    if(message_override) {
        char *buffer = vformatted_string(fmt, args);
        message_override('i', buffer);
        free(buffer);
    } else {
        vfprintf(stderr, fmt, args);
    }
    va_end(args);
}

void set_message_handler(void (*handler)(char type, const char *msg)) {
    message_override = handler;
}

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

void cascad_print_ast(cascad_ast_t ast) {
    debug_ast((ast_t) ast);
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

void cascad_print_bytecode(cascad_context_t context) {
    debug_bytecode((context_t) context);
}

cascad_shape_t cascad_execute(cascad_context_t context) {
    return (cascad_shape_t) interpreter_execute((context_t) context);
}

int cascad_export_stl(cascad_shape_t shape, const char *path, int ascii) {
    return !backend_export_stl((value_t) shape + 1, path, ascii);
}

enum cascad_shape_type_t cascad_get_shape_type(cascad_shape_t shape) {
    switch(((value_t) shape)[1].u) {
        case VALUE_TYPE_EMPTY:
            return CASCAD_EMPTY;
        case VALUE_TYPE_SOLID:
            return CASCAD_SOLID;
        default:
            return CASCAD_INVALID;
    }
}

struct exchanged_data_t {
    const char* buffer;
    const char* filename;
    void (*later)(cascad_shape_t);
};

static int worker_entry_point(void *param) {
    struct exchanged_data_t *data = (struct exchanged_data_t *)param;
    
    info("\nCompiling...\n");
    cascad_ast_t ast = cascad_load_string(data->buffer);
    if(!ast) {
        if(!ast) error("file '%s' could not be parsed\n", data->filename);
        data->later(NULL);
        return 1;
    }
    cascad_context_t ctx = cascad_gen_context(ast, data->filename);
    if(!ctx) {
        if(!ast) error("file '%s' could not be compiled\n", data->filename);
        data->later(NULL);
        return 2;
    }
    info("Rendering...\n");
    cascad_shape_t output = cascad_execute(ctx);
    info("Done.\n");
    
    enum cascad_shape_type_t shape_type = cascad_get_shape_type(output);
    if(shape_type == CASCAD_INVALID) {
        error(
            "error: script produced invalid shape or non-shape; possible data corruption.\n"
        );
        data->later(NULL);
        return 3;
    }
    if(shape_type == CASCAD_EMPTY) {
        warning("warning: script execution produced empty shape.\n");
    }
    data->later(output);
    return 0;
}

void cascad_run_string_async(
    const char* buffer, const char *filename, void (*later)(cascad_shape_t)
) {
    thrd_t thread_id;
    struct exchanged_data_t *data =
        (struct exchanged_data_t *) malloc(sizeof(struct exchanged_data_t));
    data->buffer = buffer;
    data->filename = filename;
    data->later = later;
    thrd_create(&thread_id, worker_entry_point, data);
}


