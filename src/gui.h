#include "config.h"

#ifdef HAVE_LIBGTK4
#define HAVE_GUI
#endif

#ifdef HAVE_GUI

extern void gui_main();

#endif // HAVE_GUI
