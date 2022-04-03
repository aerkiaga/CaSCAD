#include "context.h"
#include "tree.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern _Noreturn void error(const char *fmt, ...);

void debug_bytecode(context_t context);

void push_value(context_t context, value_t value) {
    if(2*context->tmp_stack_pushed == context->tmp_stack[0].u) {
        union tree_child_t dummy;
        context->tmp_stack = tree_resize(context->tmp_stack, context->tmp_stack[0].u + 2);
    }
    context->tmp_stack[2*context->tmp_stack_pushed + 1] = value[1];
    context->tmp_stack_pushed++;
    context->tmp_stack[2*context->tmp_stack_pushed] = value[2];
}

void push_value_typed_u(context_t context, uintptr_t type, uintptr_t data) {
    union tree_child_t new_value[3];
    new_value[1].u = type;
    new_value[2].u = data;
    push_value(context, new_value);
}

void push_value_typed_d(context_t context, uintptr_t type, double data) {
    union tree_child_t new_value[3];
    new_value[1].u = type;
    new_value[2].d = data;
    push_value(context, new_value);
}

void push_value_typed_s(context_t context, uintptr_t type, const char *data) {
    union tree_child_t new_value[3];
    new_value[1].u = type;
    new_value[2].s = strdup(data);
    push_value(context, new_value);
}

void push_value_typed_a(context_t context, uintptr_t type, tree_t data) {
    union tree_child_t new_value[3];
    new_value[1].u = type;
    new_value[2].a = data;
    push_value(context, new_value);
}

uintptr_t get_top_value_type(context_t context) {
    return context->tmp_stack[2*context->tmp_stack_pushed + 1].u;
}

uintptr_t pop_value_data_u(context_t context) {
    context->tmp_stack_pushed--;
    return context->tmp_stack[2*context->tmp_stack_pushed + 1].u;
}

tree_t pop_value_data_a(context_t context) {
    context->tmp_stack_pushed--;
    return context->tmp_stack[2*context->tmp_stack_pushed + 1].a;
}

union tree_child_t pop_value_data_raw(context_t context) {
    context->tmp_stack_pushed--;
    return context->tmp_stack[2*context->tmp_stack_pushed + 1];
}

void copy_to_call_stack(context_t context, const tree_t src, size_t count) {
    size_t new_size = context->call_stack_pushed + count;
    if(2*new_size > context->call_stack[0].u) {
        context->call_stack = tree_resize(context->call_stack, 2*new_size);
    }
    memcpy(
        &context->call_stack[2*context->call_stack_pushed] + 1,
        src,
        2*count*sizeof(union tree_child_t)
    );
    context->call_stack_pushed += count;
}

void copy_from_call_stack(tree_t dst, context_t context, size_t count) {
    memcpy(
        dst,
        &context->call_stack[2*(context->call_stack_pushed - count)] + 1,
        2*count*sizeof(union tree_child_t)
    );
    context->call_stack_pushed -= count;
}

void pop_and_copy(tree_t dst, context_t context, size_t count) {
    memcpy(
        dst,
        &context->tmp_stack[2*(context->tmp_stack_pushed - count)] + 1,
        2*count*sizeof(union tree_child_t)
    );
    context->tmp_stack_pushed -= count;
}

void interpreter_main_loop(context_t context) {
    tree_t ip = context->code + 1;
    while(ip <= context->code + context->code[0].u) {
        uintptr_t opcode = ip->u;
        switch(opcode) {
            case OP_FINISH:
                return;
            case OP_NOP:
                break;
            case OP_JUMP:
                ip = context->code + ip[1].u - 1;
                break;
            case OP_CALL:
                push_value_typed_u(context, VALUE_TYPE_RETURN, ip - context->code);
                ip = context->code + ip[1].u - 1;
                break;
            case OP_RETURN: {
                uintptr_t return_type = get_top_value_type(context);
                value_t return_value = pop_value_data_a(context);
                if(get_top_value_type(context) != VALUE_TYPE_RETURN) {
                    error("runtime error: function/module return address corrupted.");
                }
                ip = context->code + pop_value_data_u(context);
                push_value_typed_a(context, VALUE_TYPE_RETURN, return_value);
                break;
            }
            case OP_SAVE:
                copy_to_call_stack(context, context->data + ip[1].u, ip[2].u);
                ip += 2;
                break;
            case OP_RESTORE:
                copy_from_call_stack(context->data + ip[1].u, context, ip[2].u);
                ip += 2;
                break;
            case OP_STORE: {
                uintptr_t data_type = get_top_value_type(context);
                union tree_child_t value = pop_value_data_raw(context);
                context->data[ip[1].u].u = data_type;
                context->data[ip[2].u] = value;
                ip++;
                break;
            }
            case OP_VSTORE: {
                union tree_child_t return_value = pop_value_data_raw(context);
                pop_and_copy(context->data + ip[1].u, context, ip[2].u);
                push_value(context, &return_value);
                ip += 2;
                break;
            }
            case OP_UNDEF:
                push_value_typed_u(context, VALUE_TYPE_UNDEF, 0);
                break;
            case OP_NUMBER:
                push_value_typed_d(context, VALUE_TYPE_NUMBER, ip[1].d);
                ip++;
                break;
            case OP_TRUE:
                push_value_typed_u(context, VALUE_TYPE_BOOLEAN, 1);
                break;
            case OP_FALSE:
                push_value_typed_u(context, VALUE_TYPE_BOOLEAN, 0);
                break;
            case OP_STRING:
                push_value_typed_s(context, VALUE_TYPE_STRING, ip[1].s);
                ip++;
                break;
            case OP_EMPTY:
                push_value_typed_d(context, VALUE_TYPE_EMPTY, 0);
                break;
            case OP_UNION:
                // TODO
                context->tmp_stack_pushed -= ip[1].u;
                ip++;
                break;
            default:
                error("runtime error: unknown opcode."); //D
                return;
        }
        ip++;
    }
}

void interpreter_execute(context_t context) {
    debug_bytecode(context);
    interpreter_main_loop(context);
}

void debug_bytecode(context_t context) {
    fputs(
        "Bytecode\n"
        "========\n",
        stderr
    );
    tree_t ip;
    for(ip = context->code + 1; ip <= context->code + context->code[0].u; ip++) {
        uintptr_t opcode = ip->u;
        switch(opcode) {
            case OP_FINISH:
                fprintf(stderr, "OP_FINISH\n");
                break;
            case OP_NOP:
                fprintf(stderr, "OP_NOP\n");
                break;
            case OP_JUMP:
                fprintf(stderr, "OP_JUMP %ld\n", ip[1].u);
                ip++;
                break;
            case OP_CALL:
                fprintf(stderr, "OP_CALL %ld\n", ip[1].u);
                ip++;
                break;
            case OP_RETURN:
                fprintf(stderr, "OP_RETURN\n");
                break;
            case OP_SAVE:
                fprintf(stderr, "OP_SAVE %ld, %ld\n", ip[1].u, ip[2].u);
                ip += 2;
                break;
            case OP_RESTORE:
                fprintf(stderr, "OP_RESTORE %ld, %ld\n", ip[1].u, ip[2].u);
                ip += 2;
                break;
            case OP_STORE:
                fprintf(stderr, "OP_STORE %ld\n", ip[1].u);
                ip++;
                break;
            case OP_VSTORE:
                fprintf(stderr, "OP_VSTORE %ld, %ld\n", ip[1].u, ip[2].u);
                ip += 2;
                break;
            case OP_UNDEF:
                fprintf(stderr, "OP_UNDEF\n");
                break;
            case OP_NUMBER:
                fprintf(stderr, "OP_NUMBER %g\n", ip[1].d);
                ip++;
                break;
            case OP_TRUE:
                fprintf(stderr, "OP_TRUE\n");
                break;
            case OP_FALSE:
                fprintf(stderr, "OP_FALSE\n");
                break;
            case OP_STRING:
                fprintf(stderr, "OP_STRING \"%s\"\n", ip[1].s);
                ip++;
                break;
            case OP_EMPTY:
                fprintf(stderr, "OP_EMPTY\n");
                break;
            case OP_UNION:
                fprintf(stderr, "OP_UNION %ld\n", ip[1].u);
                ip++;
                break;
            default:
                fprintf(stderr, "Unknown opcode: %ld\n", opcode);
                return;
        }
    }
    fputs(
        "========\n"
        "\n",
        stderr
    );
}
