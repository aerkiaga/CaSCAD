#include "gui.h"

#ifdef HAVE_GUI
#include "backend.h"
#include "cascad.h"
#include "config.h"
#include "frontend.h"

void gui_startup_callback(void) {
    frontend_create(PACKAGE_STRING);
}

void gui_gl_realize_callback(
    int width, int height, int scale_factor,
    void *context, void *display, void *config
) {
    backend_realize_graphics(width, height, scale_factor, context, display, config);
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
    frontend_run_at_startup(gui_startup_callback);
    frontend_run_at_gl_realize(gui_gl_realize_callback);
    frontend_run_at_gl_render(gui_gl_render_callback);
    frontend_run_at_preview(gui_preview_callback);
    backend_init_graphics();
    frontend_main(argc, argv);
}

#endif // HAVE_GUI
