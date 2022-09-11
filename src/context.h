#ifndef CONTEXT_H
#define CONTEXT_H

#include "deps.h"
#include "tree.h"
#include <stdlib.h>

enum {
    BIND_TYPE_NONE, // not fully compiled yet, address is NULL
    BIND_TYPE_VARIABLE,
    BIND_TYPE_FUNCTION,
    BIND_TYPE_MODULE
};

enum {
    VALUE_TYPE_RETURN,
    VALUE_TYPE_UNDEF,
    VALUE_TYPE_NUMBER,
    VALUE_TYPE_BOOLEAN,
    VALUE_TYPE_STRING,
    VALUE_TYPE_VECTOR,
    VALUE_TYPE_FUNCTION,
    VALUE_TYPE_MODULE,
    VALUE_TYPE_EMPTY,
    VALUE_TYPE_SOLID,
    VALUE_TYPE_COMPOUND,
    VALUE_TYPE_CHILDREN
};

/* Each instruction consists of an opcode followed by zero or more parameters. */
/* Here, all parameters are mentioned for each opcode, as $1, $2, etc. */
/* Note that all addresses are indices, not pointers. */
/* Unless otherwise stated, all 'push', 'pop' or 'stack' refer to tmp_stack */
enum {
    OP_FINISH,  // end execution and present result, no parameters
    OP_NOP,     // no operation, has no parameters
    OP_JUMP,    // jump to address $1, execute it next
    OP_CALL,    // push current address and jump to address $1
    OP_RETURN,  // pop return value, pop address and set it as current, push return value
    OP_SAVE,    // push $2 values to call_stack from data storage starting at address $1
    OP_RESTORE, // pop $2 values from call_stack into data storage starting at address $1
    OP_STORE,   // pop stack, store value at address $1
    OP_VSTORE,  // pop and save return value at temporary variable, then ...
                // ... pop $2 values from the stack, store them starting at address $1, ...
                // ... the top of the stack becomes the last element; push return value
    OP_LOAD,    // push value at address $1 onto the stack
    OP_UNDEF,   // push literal undef, no parameters
    OP_NUMBER,  // push literal number $1
    OP_TRUE,    // push literal true, no parameters
    OP_FALSE,   // push literal false, no parameters
    OP_STRING,  // push literal string $1
    OP_VECTOR,  // push empty vector
    OP_DIVIDE,  // pop divisor, pop dividend, push quotient
    OP_APPEND,  // pop value, pop vector, push new vector
    OP_EMPTY,   // push empty geometry, no parameters
    OP_SPHERE,  // pop 'r' and '@children', push sphere
    OP_CYLINDER,// pop 'center', 'r2', 'r1', 'h' and '@children', push cylinder
    OP_GROUP,   // pop $1 values from the stack and push a list of geometry
    OP_UNION    // pop chikd or list of children from the stack and push their union
};

/* Format: (value_type  value)... */
typedef tree_t value_t;

typedef struct context_value_t {
    tree_t code; // bytecode instructions
    /* Format: (value_type  value)... */
    value_t data; // variable storage for all scopes
    value_t call_stack; // stack for values saved during call
    size_t call_stack_pushed; // number of elements pushed (<= capacity)
    value_t tmp_stack; // stack for temporary values
    size_t tmp_stack_pushed; // number of elements pushed (<= capacity)
    
    /* only used during compilation */
    const char *script_path; // path of currently running script, or NULL
    deps_t deps; // loaded dependencies of current script
    uintptr_t parent_type; // AST type of current node's parent
    /* Format: (ptr -> (name  bind_type  address  ast)...)... */
    tree_t scope_stack; // stack of scopes, with all current identifiers
    size_t data_variables; // number of variables currently in scope
} *context_t;

#endif // CONTEXT_H
