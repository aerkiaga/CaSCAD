#include "config.h"
#include "cascad.h"
#include <getopt.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

_Noreturn void error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(1);
}

int main(int argc, char *argv[]) {
    //const char *const short_options = "o:D:p:P:hvd:m:qs:x:";
    const char *const short_options = "hv";
    const struct option long_options[] = {
        //{"export-format",   required_argument,  NULL,   0},
        //{"enable",          required_argument,  NULL,   0},
        {"help",            no_argument,        NULL,   'h'},
        {"version",         no_argument,        NULL,   'v'},
        //{"info",            no_argument,        NULL,   0},
        //{"camera",          required_argument,  NULL,   0},
        //{"autocenter",      no_argument,        NULL,   0},
        //{"viewall",         no_argument,        NULL,   0},
        //{"imgsize",         required_argument,  NULL,   0},
        //{"render",          required_argument,  NULL,   0},
        //{"preview",         required_argument,  NULL,   0},
        //{"animate",         required_argument,  NULL,   0},
        //{"view",            required_argument,  NULL,   0},
        //{"projection",      required_argument,  NULL,   0},
        //{"summary",         required_argument,  NULL,   0},
        //{"summary-file",    required_argument,  NULL,   0},
        //{"colorscheme",     required_argument,  NULL,   0},
        //{"quiet",           no_argument,        NULL,   'q'},
        //{"hardwarnings",    no_argument,        NULL,   0},
        //{"check-parameters", required_argument,  NULL,   0},
        //{"check-parameter-ranges", required_argument,  NULL,   0},
        //{"debug",           required_argument,  NULL,   0},
        {NULL,              0,                  NULL,   0}
    };
    int c;
    int old_optind = optind;
    while ((c = getopt_long(
        argc, argv, short_options, long_options, NULL
    )) != -1) {
        switch(c) {
            case 'h':
                puts(
                    "Usage: cascad [options] file...\n"
                    "Options:\n"
                    "  -h, --help    display this help and exit\n"
                    "  -v, --help    output version information and exit\n"
                    "\n"
                    "Report bugs to: (TODO)"
                );
                exit(0);
                break;
            case 'v':
                puts(
                    PACKAGE_STRING "\n"
                    "Copyright (C) 2022 Aritz Erkiaga Fernández\n"
                    "License LGPLv3: GNU LGPL version 3 <https://gnu.org/licenses/lgpl-3.0.html>\n"
                    "This is free software: you are free to change and redistribute it.\n"
                    "There is NO WARRANTY, to the extent permitted by law."
                );
                exit(0);
                break;
            default:
                error("cascad: unrecognized option '%s'\n", argv[optind]);
        }
        old_optind = optind;
    }
    
    const char *filename = argv[optind];
    if(!filename) error("cascad: no input file\n");
    FILE *file = fopen(filename, "rt");
    if(!file) error("cascad: file '%s' could not be opened\n", filename);
    
    cascad_ast_t ast = cascad_load_file(file);
    if(!ast) error("cascad: file '%s' could not be parsed\n", filename);
    
    cascad_context_t ctx = cascad_gen_context(ast, filename);
    if(!ctx) error("cascad: file '%s' could not be compiled\n", filename);
    
    cascad_execute(ctx);
    
    fclose(file);
    return 0;
}
