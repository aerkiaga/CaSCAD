#include "config.h"

#ifdef HAVE_LIBGTK4
#define HAVE_GUI
#endif

#ifdef HAVE_GUI

#ifdef __cplusplus
extern "C" {
#endif

extern void gui_main(int argc, char *argv[]);
extern void gui_run_at_startup(void);
extern void gui_run_at_gl_realize(int scale_factor);
extern void gui_run_at_gl_resize(int width, int height);
extern void gui_run_at_gl_unrealize(void);
extern void gui_run_at_gl_render(void);
extern void gui_run_at_preview(void);
extern void gui_run_at_export_stl(void);
extern void gui_redraw_viewer(void);
extern void gui_perform_pan(double dx, double dy);
extern void gui_perform_zoom(double dy);

extern const char *gui_lookup_word(const char *word);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HAVE_GUI
