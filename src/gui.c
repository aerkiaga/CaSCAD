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

void gui_startup_callback(void) {
    frontend_create(PACKAGE_STRING);
    frontend_console_print(CASCAD_NOTICE);
}

void gui_gl_realize_callback(
    int width, int height, int scale_factor,
    void *context, void *display, void *config
) {
    backend_realize_graphics(width, height, scale_factor, context, display, config);
}

void gui_gl_unrealize_callback(void) {
    backend_unrealize_graphics();
}

void gui_gl_render_callback(void) {
    backend_render_graphics();
}

static void gui_finalize_work(cascad_shape_t output) {
    if(!output) return;
    
    if(cascad_get_shape_type(output) == CASCAD_SOLID) {
        backend_render_shape(output);
    }
}

void gui_preview_callback(void) {
    cascad_run_string_async(frontend_get_editor_text(), NULL, gui_finalize_work);
}

void gui_main(int argc, char *argv[]) {
    set_message_handler(gui_message_handler);
    frontend_run_at_startup(gui_startup_callback);
    frontend_run_at_gl_realize(gui_gl_realize_callback);
    frontend_run_at_gl_unrealize(gui_gl_unrealize_callback);
    frontend_run_at_gl_render(gui_gl_render_callback);
    frontend_run_at_preview(gui_preview_callback);
    backend_init_graphics(NULL);
    frontend_main(argc, argv);
}

#endif // HAVE_GUI
