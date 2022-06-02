#include "gui.h"

#ifdef HAVE_GUI
#include "backend.h"
#include "builtin.h"
#include "cascad.h"
#include "config.h"
#include "context.h"
#include "frontend.h"
#include <stdint.h>
#include <string.h>
#include <threads.h>

void gui_message_handler(char type, const char *msg) {
    frontend_console_print(msg);
    if(type == 'e') thrd_exit(1);
}

void gui_run_at_startup(void) {
    frontend_create(PACKAGE_STRING);
    frontend_console_print(CASCAD_NOTICE);
}

void gui_run_at_gl_realize(int width, int height, int scale_factor) {
    frontend_realize_graphics(width, height, scale_factor);
}

void gui_run_at_gl_unrealize(void) {
    frontend_unrealize_graphics();
}

void gui_run_at_gl_render(void) {
    frontend_render_graphics();
}

static cascad_shape_t current_shape = NULL;

static void gui_finalize_work(cascad_shape_t output) {
    if(!output) return;
    
    if(cascad_get_shape_type(output) == CASCAD_SOLID) {
        float *coords;
        unsigned int ncoords;
        unsigned int *indices;
        unsigned int nindices;
        backend_export_triangles((value_t) output + 1, &coords, &ncoords, &indices, &nindices);
        frontend_send_triangles(coords, ncoords, indices, nindices);
        gui_redraw_viewer();
    }
    
    current_shape = output;
}

void gui_run_at_preview(void) {
    cascad_run_string_async(frontend_get_editor_text(), NULL, gui_finalize_work);
}

static void gui_export_stl_filename_callback(const char *filename) {
    cascad_export_stl_async(current_shape, filename, 1, NULL);
}

void gui_run_at_export_stl(void) {
    if(!current_shape) return;
    if(cascad_get_shape_type(current_shape) != CASCAD_SOLID) return;
    frontend_ask_save_filename(gui_export_stl_filename_callback);
}

void gui_redraw_viewer(void) {
    frontend_redraw_viewer();
}

const char *gui_lookup_word(const char *word) {
    if(
        !strcmp(word, "undef")
    ) return "undef";
    else if(
        !strcmp(word, "PI")
    ) return "value";
    else if(
        !strcmp(word, "each") ||
        !strcmp(word, "else") ||
        !strcmp(word, "false") ||
        !strcmp(word, "for") ||
        !strcmp(word, "function") ||
        !strcmp(word, "if") ||
        !strcmp(word, "include") ||
        !strcmp(word, "intersection_for") ||
        !strcmp(word, "let") ||
        !strcmp(word, "module") ||
        !strcmp(word, "true") ||
        !strcmp(word, "use")
    ) return "keyword";
    else {
        builtin_t builtin = search_in_builtins(word);
        if(builtin) {
            uintptr_t builtin_type = builtin[1].u;
            if(builtin_type == BIND_TYPE_FUNCTION) return "function";
            else if(builtin_type == BIND_TYPE_MODULE) return "module";
        }
    }
    return NULL;
}

void gui_main(int argc, char *argv[]) {
    set_message_handler(gui_message_handler);
    frontend_init_graphics();
    frontend_main(argc, argv);
}

#endif // HAVE_GUI
