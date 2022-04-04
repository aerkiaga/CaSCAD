#include "ast.h"
#include "deps.h"
#include "context.h"
#include <stddef.h>

extern ptrdiff_t append_code_u(context_t context, uintptr_t value);

extern context_t compiler_produce_with_deps(ast_t ast, deps_t deps, const char *script_path);
extern context_t compiler_produce(ast_t ast, const char *script_path);
