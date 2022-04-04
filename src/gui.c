#include "gui.h"

#ifdef HAVE_GUI
#include "config.h"
#include "frontend.h"

void gui_startup_callback() {
    frontend_new_maximized_window(PACKAGE_STRING);
}

void gui_main() {
    frontend_run_at_startup(gui_startup_callback);
    frontend_main();
}

#endif // HAVE_GUI
