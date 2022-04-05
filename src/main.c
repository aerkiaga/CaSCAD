#include "config.h"
#include "cascad.h"
#include "gui.h"
#include "strutils.h"
#include <getopt.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Noreturn void error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(1);
}

void warning(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

int main(int argc, char *argv[]) {
    const char *output_filename = NULL;
    const char *output_extension = "";
    int print_bytecode = 0;

    //const char *const short_options = "o:D:p:P:hvd:m:qs:x:";
    const char *const short_options = "o:hv";
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
        {"print-bytecode",  no_argument,        NULL,   0},
        {NULL,              0,                  NULL,   0}
    };
    int c;
    int old_optind = optind;
    int longind = 0;
    while ((c = getopt_long(
        argc, argv, short_options, long_options, &longind
    )) != -1) {
        switch(c) {
            case 0: {
                const char *name = long_options[longind].name;
                if(!strcmp("print-bytecode", name)) print_bytecode = 1;
            }
            case 'o':
                output_filename = argv[optind - 1];
                output_extension = path_extension(output_filename);
                break;
            case 'h':
                puts(
                    "Usage: cascad [options] file...\n"
                    "Generic options:\n"
                    "  -o <file>            write output to <file>\n"
                    "  -h, --help           display this help and exit\n"
                    "  -v, --help           output version information and exit\n"
                    "\n"
                    "CaSCAD-specific options:\n"
                    "  --print-bytecode     print compiled bytecode to stderr\n"
                    "\n"
                    "Report bugs to: (TODO)"
                );
                exit(0);
                break;
            case 'v':
                puts(
                    PACKAGE_STRING "\n"
                    "Copyright (C) 2022 Aritz Erkiaga Fernández\n"
                    "License GPLv3: GNU GPL version 3 <https://gnu.org/licenses/gpl-3.0.html>\n"
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
    
    if(!output_filename) {
        #ifdef HAVE_GUI
        gui_main(argc, argv);
        #else
        error("cascad: no GUI built, an output file needs to be specified.\n");
        #endif
    } else {
        const char *filename = argv[optind];
        if(!filename) error("cascad: no input file\n");
        FILE *file = fopen(filename, "rt");
        if(!file) error("cascad: file '%s' could not be opened\n", filename);
        cascad_ast_t ast = cascad_load_file(file);
        if(!ast) error("cascad: file '%s' could not be parsed\n", filename);
        cascad_context_t ctx = cascad_gen_context(ast, filename);
        if(!ctx) error("cascad: file '%s' could not be compiled\n", filename);
        if(print_bytecode) cascad_print_bytecode(ctx);
        cascad_shape_t output = cascad_execute(ctx);
        
        enum cascad_shape_type_t shape_type = cascad_get_shape_type(output);
        if(shape_type == CASCAD_INVALID) {
            error(
                "cascad: script execution produced invalid shape or non-shape; possible data corruption.\n"
            );
        }
        if(shape_type == CASCAD_EMPTY) {
            warning("cascad: script execution produced empty shape.\n");
        }
        
        if(output_filename) {
            if(!strcmp("stl", output_extension) || !strcmp("STL", output_extension)) {
                if(cascad_export_stl(output, output_filename, 1)) {
                    error(
                        "cascad: STL file export failed.\n"
                    );
                }
            }
        }
        fclose(file);
    }
    return 0;
}
