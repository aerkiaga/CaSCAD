#include "gui.h"

#ifdef HAVE_GUI
#include "backend.h"
#include "cascad.h"
#include "config.h"
#include "frontend.h"
#include <threads.h>

void gui_message_handler(char type, const char *msg) {
    frontend_console_print(msg);
    if(type == 'e') thrd_exit(1);
}

void gui_run_at_startup(void) {
    frontend_create(PACKAGE_STRING);
    frontend_console_print(CASCAD_NOTICE);
}

void gui_run_at_gl_realize(
    int width, int height, int scale_factor,
    void *context, void *display, void *config
) {
    backend_realize_graphics(width, height, scale_factor, context, display, config);
}

void gui_run_at_gl_unrealize(void) {
    backend_unrealize_graphics();
}

void gui_run_at_gl_render(void) {
    backend_render_graphics();
}

static cascad_shape_t current_shape = NULL;

static void gui_finalize_work(cascad_shape_t output) {
    if(!output) return;
    
    if(cascad_get_shape_type(output) == CASCAD_SOLID) {
        backend_render_shape(output);
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

void gui_main(int argc, char *argv[]) {
    set_message_handler(gui_message_handler);
    backend_init_graphics(NULL);
    frontend_main(argc, argv);
}

#endif // HAVE_GUI
