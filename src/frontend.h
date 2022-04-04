#include "gui.h"

#ifdef HAVE_GUI

extern void frontend_new_maximized_window(const char *name);
extern void frontend_run_at_startup(void (*callback)(void));
extern void frontend_main(void);

#endif // HAVE_GUI
