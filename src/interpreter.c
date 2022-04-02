#include "context.h"
#include "tree.h"
#include <stdint.h>
#include <stdio.h>

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

void interpreter_main_loop(context_t context) {
}

void interpreter_execute(context_t context) {
    debug_bytecode(context);
    interpreter_main_loop(context);
}
