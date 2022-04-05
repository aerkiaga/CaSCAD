#include "config.h"

#ifdef HAVE_LIBGTK4
#define HAVE_GUI
#endif

#ifdef HAVE_GUI

extern void gui_main(int argc, char *argv[]);
extern void gui_run_at_startup(void);
extern void gui_run_at_gl_realize(
    int width, int height, int scale_factor,
    void *context, void *display, void *config
);
extern void gui_run_at_gl_unrealize(void);
extern void gui_run_at_gl_render(void);
extern void gui_run_at_preview(void);
extern void gui_run_at_export_stl(void);

#endif // HAVE_GUI
