#include <stdio.h>

typedef struct t_cascad_ast_t *cascad_ast_t;

/* Parse file and output an Abstract Syntax Tree */
extern cascad_ast_t cascad_load_file(FILE *file);

/* Parse string and output an Abstract Syntax Tree */
extern cascad_ast_t cascad_load_string(const char* buffer);
