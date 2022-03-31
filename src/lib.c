#include "ast.h"
#include "lib.h"
#include "lexer.h"
#include "parser_interface.h"
#include <stdio.h>
#include <stdlib.h>

cascad_ast_t cascad_load_file(FILE* file) {
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    char* buffer = (char*) malloc(file_size + 1);
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

cascad_ast_t cascad_load_string(const char* buffer) {
    lexer_load(buffer);
    ast_t tree = parser_run();
    return (cascad_ast_t) tree;
}
