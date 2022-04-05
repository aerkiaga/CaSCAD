#include "gui.h"

#ifdef HAVE_GUI
#include "frontend.h"
#include <gdk/x11/gdkx.h>
#include <gtk/gtk.h>
#include <EGL/egl.h>

GtkApplication *application = NULL;
GtkWidget *window;
GtkWidget *code_editor;
GtkTextBuffer *code_buffer;
GtkWidget *viewer;
GtkWidget *console;
static void (*run_at_startup)(void) = NULL;
static void (*run_at_viewer_realize)(int, int, int, void *, void *, void *) = NULL;
static void (*run_at_viewer_render)(void) = NULL;
static void (*run_at_preview)(void) = NULL;

void frontend_run_at_gl_realize(void (*callback)(int, int, int, void *, void *, void *)) {
    run_at_viewer_realize = callback;
}

static void viewer_realize_callback(GtkWidget *self, gpointer user_data) {
    gtk_gl_area_make_current(GTK_GL_AREA(self));
    int width = gtk_widget_get_width(self);
    int height = gtk_widget_get_height(self);
    int scale_factor = gtk_widget_get_scale_factor(self);
    
    gtk_gl_area_set_has_depth_buffer(GTK_GL_AREA(self), 1);
    gtk_gl_area_set_has_stencil_buffer(GTK_GL_AREA(self), 1);
    gtk_gl_area_attach_buffers(GTK_GL_AREA(self));
    //gtk_gl_area_set_auto_render(GTK_GL_AREA(self), 0);
    
    EGLContext egl_context = eglGetCurrentContext();
    
    if(egl_context != EGL_NO_CONTEXT) {
        EGLContext egl_display = eglGetCurrentDisplay();
        EGLContext egl_surface = eglGetCurrentSurface(EGL_DRAW);
        EGLint egl_config_id = 0;
        EGLint num_configs = 0;
        eglQuerySurface(egl_display, egl_surface, EGL_CONFIG_ID, &egl_config_id);
        const EGLint config_attributes[] = {EGL_CONFIG_ID, egl_config_id, EGL_NONE};
        void* egl_config = NULL;
        eglChooseConfig(egl_display, config_attributes, &egl_config, 1, &num_configs);
        
        run_at_viewer_realize(
            width, height, scale_factor,
            (void *) egl_context, (void *) egl_display, (void *) egl_config
        );
    } else {
        //GdkGLContext* gdk_gl_context = gdk_gl_context_get_current();
        GdkGLContext *gdk_gl_context = gtk_gl_area_get_context(GTK_GL_AREA(self));
        GdkDisplay *display = gdk_gl_context_get_display(gdk_gl_context);
        GdkSurface *surface = gdk_gl_context_get_surface(gdk_gl_context);
        Display *xdisplay = gdk_x11_display_get_xdisplay(display);
        Window gl_window = gdk_x11_surface_get_xid(surface);
        
        run_at_viewer_realize(
            width, height, scale_factor,
            (void *) NULL, (void *) xdisplay, (void *) gl_window
        );
    }
}

void frontend_run_at_gl_render(void (*callback)(void)) {
    run_at_viewer_render = callback;
}

static void viewer_render_callback(GtkGLArea *self, GdkGLContext *context, gpointer user_data) {
    run_at_viewer_render();
}

void frontend_run_at_preview(void (*callback)(void)) {
    run_at_preview = callback;
}

static void button_preview_callback(GtkGLArea *self, gpointer user_data) {
    run_at_preview();
    GdkGLContext* gdk_gl_context = gdk_gl_context_get_current();
    GdkDisplay* display = gdk_gl_context_get_display(gdk_gl_context);
    gdk_display_flush(display);
}

void add_style(GtkWidget *widget, const char *css) {
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css_provider, css, -1);
    GtkStyleContext *style_context =
        gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(
        style_context,
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}

void frontend_create(const char *name) {
    window = gtk_application_window_new(application);
    gtk_window_set_title(GTK_WINDOW(window), name);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_maximize(GTK_WINDOW(window));
    
    GtkWidget *h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gtk_widget_set_hexpand(h_box, 1);
    gtk_widget_set_vexpand(h_box, 1);
    gtk_window_set_child(GTK_WINDOW(window), h_box);
    
        GtkWidget *v_box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
        gtk_widget_set_hexpand(v_box1, 1);
        gtk_widget_set_vexpand(v_box1, 1);
        gtk_box_append(GTK_BOX(h_box), v_box1);
        
            GtkWidget *button_bar1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
            gtk_widget_set_hexpand(v_box1, 1);
            gtk_box_append(GTK_BOX(v_box1), button_bar1);
                
                GtkWidget *button_view1 = gtk_button_new_from_icon_name("arrow-right-double");
                g_signal_connect(button_view1, "clicked", G_CALLBACK(button_preview_callback), NULL);
                gtk_widget_set_sensitive(button_view1, 1);
                gtk_box_append(GTK_BOX(button_bar1), button_view1);
    
            code_editor = gtk_text_view_new();
            gtk_widget_set_hexpand(code_editor, 1);
            gtk_widget_set_vexpand(code_editor, 1);
            GtkCssProvider *editor_css_provider = gtk_css_provider_new();
            add_style(
                code_editor,
                "textview {"
                "   font: 16px mono;"
                "   color: @theme_fg_color;"
                "}"
                "textview text {"
                "   background-color: @theme_bg_color;"
                "}"
            );
            gtk_text_view_set_left_margin(GTK_TEXT_VIEW(code_editor), 20);
            gtk_text_view_set_right_margin(GTK_TEXT_VIEW(code_editor), 20);
            gtk_text_view_set_top_margin(GTK_TEXT_VIEW(code_editor), 15);
            gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(code_editor), 15);
            gtk_box_append(GTK_BOX(v_box1), code_editor);
        
        GtkWidget *v_box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
        gtk_widget_set_hexpand(v_box2, 1);
        gtk_widget_set_vexpand(v_box2, 1);
        gtk_box_append(GTK_BOX(h_box), v_box2);
        
            viewer = gtk_gl_area_new();
            gtk_widget_set_hexpand(viewer, 1);
            gtk_widget_set_vexpand(viewer, 1);
            g_signal_connect(viewer, "realize", G_CALLBACK(viewer_realize_callback), NULL);
            g_signal_connect(viewer, "render", G_CALLBACK(viewer_render_callback), NULL);
            gtk_box_append(GTK_BOX(v_box2), viewer);
        
            GtkWidget *button_bar2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
            gtk_box_append(GTK_BOX(v_box2), button_bar2);
            
                GtkWidget *button_view2 = gtk_button_new_from_icon_name("arrow-right-double");
                g_signal_connect(button_view2, "clicked", G_CALLBACK(button_preview_callback), NULL);
                gtk_box_append(GTK_BOX(button_bar2), button_view2);
        
            console = gtk_text_view_new();
            gtk_widget_set_hexpand(console, 1);
            gtk_widget_set_vexpand(console, 1);
            GtkCssProvider *console_css_provider = gtk_css_provider_new();
            add_style(
                console,
                "textview {"
                "   font: 16px mono;"
                "   color: white;"
                "}"
                "textview text {"
                "   background-color: #404040;"
                "}"
            );
            gtk_text_view_set_editable(GTK_TEXT_VIEW(console), 0);
            gtk_box_append(GTK_BOX(v_box2), console);
    
    gtk_widget_show(window);
}

void frontend_run_at_startup(void (*callback)(void)) {
    run_at_startup = callback;
}

static void activate_callback(GtkApplication* app, gpointer user_data) {
    if(run_at_startup) run_at_startup();
}

const char *frontend_get_editor_text(void) {
    code_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(code_editor));
    GtkTextIter start;
    gtk_text_buffer_get_start_iter(code_buffer, &start);
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(code_buffer, &end);
    return gtk_text_buffer_get_text(code_buffer, &start, &end, 0);
}

void frontend_main(int argc, char *argv[]) {
    application = gtk_application_new(
        "io.github.aerkiaga.cascad", G_APPLICATION_FLAGS_NONE
    );
    g_signal_connect(application, "activate", G_CALLBACK(activate_callback), NULL);
    g_application_run(G_APPLICATION(application), argc, argv);
    g_object_unref(application);
}

#endif // HAVE_GUI
