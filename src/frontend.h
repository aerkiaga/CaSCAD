#include "gui.h"

#ifdef HAVE_GUI

extern void frontend_create(const char *name);
extern void frontend_console_print(const char *msg);
extern void frontend_redraw_viewer(void);
extern void frontend_main(int argc, char *argv[]);

extern const char *frontend_get_editor_text(void);
extern void frontend_ask_save_filename(void (*callback)(const char *));

#endif // HAVE_GUI
