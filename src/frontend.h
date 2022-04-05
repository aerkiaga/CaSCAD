#include "gui.h"

#ifdef HAVE_GUI

extern void frontend_create(const char *name);
extern void frontend_run_at_startup(void (*callback)(void));
extern void frontend_run_at_gl_realize(void (*callback)(int, int, int, void *, void *, void *));
extern void frontend_run_at_gl_unrealize(void (*callback)(void));
extern void frontend_run_at_gl_render(void (*callback)(void));
extern void frontend_run_at_preview(void (*callback)(void));
extern void frontend_console_print(const char *msg);
extern void frontend_main(int argc, char *argv[]);

extern const char *frontend_get_editor_text(void);

#endif // HAVE_GUI
