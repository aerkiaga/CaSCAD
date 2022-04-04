#include "gui.h"

#ifdef HAVE_GUI
#include "frontend.h"
#include <gtk/gtk.h>

GtkApplication *application = NULL;
GtkWidget *window;
static void (*run_at_startup)(void) = NULL;

void frontend_new_maximized_window(const char *name) {
    window = gtk_application_window_new(application);
    gtk_window_set_title(GTK_WINDOW(window), name);
    gtk_window_maximize(GTK_WINDOW(window));
    gtk_widget_show (window);
}

void frontend_run_at_startup(void (*callback)(void)) {
    run_at_startup = callback;
}

static void activate_callback(GtkApplication* app, gpointer user_data) {
    if(run_at_startup) run_at_startup();
}

extern void frontend_main(void) {
    application = gtk_application_new(
        "io.github.aerkiaga.cascad", G_APPLICATION_FLAGS_NONE
    );
    g_signal_connect(application, "activate", G_CALLBACK(activate_callback), NULL);
    g_application_run(G_APPLICATION(application), 0, NULL);
    g_object_unref(application);
}

#endif // HAVE_GUI
