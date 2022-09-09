#include "gui.h"

#ifdef HAVE_GUI
#include "frontend.h"
#include "resources.h"
#include <ctype.h>
#include <gdk/x11/gdkx.h>
#include <gtk/gtk.h>
#include <string.h>

GtkApplication *application = NULL;
GtkWidget *window;
GtkWidget *code_editor;
GtkTextBuffer *code_buffer;
GtkWidget *viewer;
GtkWidget *console;
GtkTextBuffer *console_buffer;

static void viewer_realize_callback(GtkWidget *self, gpointer user_data) {
    gtk_gl_area_make_current(GTK_GL_AREA(self));
    int scale_factor = gtk_widget_get_scale_factor(self);
    
    //gtk_gl_area_set_has_depth_buffer(GTK_GL_AREA(self), 1);
    //gtk_gl_area_set_has_stencil_buffer(GTK_GL_AREA(self), 1);
    //gtk_gl_area_attach_buffers(GTK_GL_AREA(self));
    //gtk_gl_area_set_auto_render(GTK_GL_AREA(self), 0);
    
    GdkGLContext *context = gtk_gl_area_get_context(GTK_GL_AREA(self));
    int major_version, minor_version;
    gdk_gl_context_get_version(context, &major_version, &minor_version);
    printf(
        "Using OpenGL%s %d.%d %s profile\n",
        gdk_gl_context_get_use_es(context) ? " ES" : "",
        major_version,
        minor_version,
        gdk_gl_context_is_legacy(context) ? "compatibility" : "core"
    );
    
    gui_run_at_gl_realize(scale_factor);
}

void viewer_resize_callback(GtkGLArea* self, gint width, gint height, gpointer user_data) {
    gui_run_at_gl_resize(width, height);
}

static void viewer_unrealize_callback(GtkWidget *self, gpointer user_data) {
    gtk_gl_area_make_current(GTK_GL_AREA(self));
    gui_run_at_gl_unrealize();
}

static void viewer_render_callback(GtkGLArea *self, GdkGLContext *context, gpointer user_data) {
    gui_run_at_gl_render();
}

static void button_preview_callback(GtkGLArea *self, gpointer user_data) {
    gui_run_at_preview();
    GdkGLContext* gdk_gl_context = gdk_gl_context_get_current();
    GdkDisplay* display = gdk_gl_context_get_display(gdk_gl_context);
    gdk_display_flush(display);
}

static void button_stl_callback(GtkGLArea *self, gpointer user_data) {
    gui_run_at_export_stl();
}

const char *frontend_get_editor_text(void) {
    GtkTextIter start;
    gtk_text_buffer_get_start_iter(code_buffer, &start);
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(code_buffer, &end);
    return gtk_text_buffer_get_text(code_buffer, &start, &end, 0);
}

static void editor_changed_callback(GtkTextBuffer* self, gpointer user_data) {
    GtkTextIter start;
    gtk_text_buffer_get_start_iter(code_buffer, &start);
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(code_buffer, &end);
    /* For now, this is a good enough solution. */
    gtk_text_buffer_remove_all_tags(self, &start, &end);
    gtk_text_buffer_get_start_iter(code_buffer, &start);
    GtkTextIter first, current;
    char first_ch = '\0';
    for(current = start; ; ) {
        char ch = gtk_text_iter_get_char(&current);
        if(first_ch == '\0') {
            first_ch = ch;
            first = current;
            if(isalpha(ch) || ch == '_' || ch == '$') ; // Identifier
            else if(isdigit(ch) || ch == '+' || ch == '-' || ch == '.') ; // Number
            else if(ch == '"') ; // String
            else if(ch == '/') ; // Comment
            else {
                first_ch = '\0';
            }
        } else if(isalpha(first_ch) || first_ch == '_' || first_ch == '$') {
            if(isalpha(ch) || ch == '_') first_ch = ch;
            else if(isdigit(ch)) ;
            else {
                if(first_ch != '$') {
                    const char *identifier = gtk_text_buffer_get_text(self, &first, &current, 0);
                    const char *tag_type = gui_lookup_word(identifier);
                    if(tag_type) {
                        gtk_text_buffer_apply_tag_by_name(self, tag_type, &first, &current);
                    }
                }
                first_ch = '\0';
                continue;
            }
        } else if(isdigit(first_ch) || first_ch == '+' || first_ch == '-' || first_ch == '.') {
            if(isdigit(ch)) first_ch = ch;
            else if(ch == 'e' || ch == 'E') gtk_text_iter_forward_char(&current);
            else if(ch == '.') ;
            else {
                if(first_ch != '+' && first_ch != '-' && first_ch != '.') {
                    gtk_text_buffer_apply_tag_by_name(self, "value", &first, &current);
                }
                first_ch = '\0';
                continue;
            }
        } else if(first_ch == '"') {
            if(ch == '\\') gtk_text_iter_forward_char(&current);
            else if(ch == '"') {
                gtk_text_iter_forward_char(&current);
                gtk_text_buffer_apply_tag_by_name(self, "string", &first, &current);
                first_ch = '\0';
                continue;
            }
        } else if(first_ch == '/') {
            if(ch == '*') first_ch = ch;
            else if(ch == '/') {
                gtk_text_iter_forward_line(&current);
                gtk_text_buffer_apply_tag_by_name(self, "comment", &first, &current);
                first_ch = '\0';
                continue;
            }
            else {
                first_ch = '\0';
                continue;
            }
        } else if(first_ch == '*') {
            if(ch == '*') {
                gtk_text_iter_forward_char(&current);
                ch = gtk_text_iter_get_char(&current);
                if(ch != '/') continue;
                else {
                    gtk_text_iter_forward_char(&current);
                    gtk_text_buffer_apply_tag_by_name(self, "comment", &first, &current);
                    first_ch = '\0';
                    continue;
                }
            }
            else ;
        }
        if(!gtk_text_iter_compare(&current, &end)) break;
        gtk_text_iter_forward_char(&current);
    }
}

double last_x, last_y;

static void drag_begin_callback(
    GtkGestureDrag *gesture,
    double x,
    double y,
    GtkWidget *area
) {
    last_x = 0;//x;
    last_y = 0;//y;
}

static void drag_update_callback(
    GtkGestureDrag *gesture,
    double x,
    double y,
    GtkWidget *area
) {
    double rel_x, rel_y;
    rel_x = x - last_x;
    rel_y = y - last_y;

    last_x += rel_x;
    last_y += rel_y;
    
    gui_perform_pan(rel_x, rel_y);
}

static void drag_end_callback(
    GtkGestureDrag *gesture,
    double x,
    double y,
    GtkWidget *area
) {
    double rel_x, rel_y;
    rel_x = x - last_x;
    rel_y = y - last_y;

    last_x += rel_x;
    last_y += rel_y;
    
    gui_perform_pan(rel_x, rel_y);
}

static void scroll_begin_callback(
    GtkEventControllerScroll *event,
    gpointer user_data
) {
}

static void scroll_callback(
    GtkEventControllerScroll *event,
    double dx,
    double dy,
    gpointer user_data
) {
    gui_perform_zoom(dy);
}

static void scroll_end_callback(
    GtkEventControllerScroll *event,
    gpointer user_data
) {
}

static void add_style(GtkWidget *widget, const char *css) {
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

static GtkWidget *frontend_new_icon_button(const void *data) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data(
        data, GDK_COLORSPACE_RGB, 1, 8, 24, 24, 4 * 24, NULL, NULL
    );
    GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);
    GtkWidget *button = gtk_button_new();
    gtk_button_set_child(GTK_BUTTON(button), image);
    return button;
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
            add_style(button_bar1, "box {background-color: #d8d8d8;}");
            gtk_box_append(GTK_BOX(v_box1), button_bar1);
                
                GtkWidget *button_view1 = frontend_new_icon_button(&ICON_RENDER_pixel_data);
                g_signal_connect(button_view1, "clicked", G_CALLBACK(button_preview_callback), NULL);
                gtk_box_append(GTK_BOX(button_bar1), button_view1);
                
                GtkWidget *button_stl = frontend_new_icon_button(&ICON_STL_pixel_data);
                g_signal_connect(button_stl, "clicked", G_CALLBACK(button_stl_callback), NULL);
                gtk_box_append(GTK_BOX(button_bar1), button_stl);
    
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
            gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(code_editor), 5);
            code_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(code_editor));
            /* Reasonably nice palette, works well in light and dark, and with color blindness. */
            gtk_text_buffer_create_tag(code_buffer, "comment", "foreground", "#9B9288", NULL);
            gtk_text_buffer_create_tag(code_buffer, "undef", "foreground", "#9B9288", NULL);
            //gtk_text_buffer_create_tag(code_buffer, "value", "foreground", "#C41F1F", NULL);
            gtk_text_buffer_create_tag(code_buffer, "value", "foreground", "#FFA51F", NULL);
            gtk_text_buffer_create_tag(code_buffer, "string", "foreground", "#B3CB2A", NULL);
            //gtk_text_buffer_create_tag(code_buffer, "string", "foreground", "#FFA51F", NULL);
            gtk_text_buffer_create_tag(code_buffer, "keyword", "foreground", "#66D24B", NULL);
            gtk_text_buffer_create_tag(code_buffer, "function", "foreground", "#66D24B", NULL);
            gtk_text_buffer_create_tag(code_buffer, "operator", "foreground", "#4BAFBE", NULL);
            gtk_text_buffer_create_tag(code_buffer, "module", "foreground", "#3358FF", NULL);
            g_signal_connect(code_buffer, "changed", G_CALLBACK(editor_changed_callback), NULL);
            GtkWidget *editor_container = gtk_scrolled_window_new();
            gtk_widget_set_hexpand(editor_container, 1);
            gtk_widget_set_vexpand(editor_container, 1);
            gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(editor_container), code_editor);
            gtk_box_append(GTK_BOX(v_box1), editor_container);
        
        GtkWidget *v_box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_hexpand(v_box2, 1);
        gtk_widget_set_vexpand(v_box2, 1);
        gtk_box_append(GTK_BOX(h_box), v_box2);

            GtkGesture *viewer_drag_gesture = gtk_gesture_drag_new();
            gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(viewer_drag_gesture), GDK_BUTTON_PRIMARY);
            g_signal_connect(viewer_drag_gesture, "drag-begin", G_CALLBACK(drag_begin_callback), NULL);
            g_signal_connect(viewer_drag_gesture, "drag-update", G_CALLBACK(drag_update_callback), NULL);
            g_signal_connect(viewer_drag_gesture, "drag-end", G_CALLBACK(drag_end_callback), NULL);
            
            GtkEventController *viewer_scroll_event = gtk_event_controller_scroll_new(GTK_EVENT_CONTROLLER_SCROLL_VERTICAL);
            g_signal_connect(viewer_scroll_event, "scroll-begin", G_CALLBACK(scroll_begin_callback), NULL);
            g_signal_connect(viewer_scroll_event, "scroll", G_CALLBACK(scroll_callback), NULL);
            g_signal_connect(viewer_scroll_event, "scroll-end", G_CALLBACK(scroll_end_callback), NULL);
  
            viewer = gtk_gl_area_new();
            gtk_widget_set_hexpand(viewer, 1);
            gtk_widget_set_vexpand(viewer, 1);
            gtk_widget_set_size_request(viewer, 1, 350);
            g_signal_connect(viewer, "realize", G_CALLBACK(viewer_realize_callback), NULL);
            g_signal_connect(viewer, "render", G_CALLBACK(viewer_render_callback), NULL);
            g_signal_connect(viewer, "resize", G_CALLBACK(viewer_resize_callback), NULL);
            gtk_widget_add_controller(viewer, GTK_EVENT_CONTROLLER(viewer_drag_gesture));
            gtk_widget_add_controller(viewer, GTK_EVENT_CONTROLLER(viewer_scroll_event));
            gtk_box_append(GTK_BOX(v_box2), viewer);
        
            GtkWidget *button_bar2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
            add_style(button_bar2, "box {background-color: #d8d8d8;}");
            gtk_box_append(GTK_BOX(v_box2), button_bar2);
            
                GtkWidget *button_view2 = frontend_new_icon_button(&ICON_RENDER_pixel_data);
                g_signal_connect(button_view2, "clicked", G_CALLBACK(button_preview_callback), NULL);
                gtk_box_append(GTK_BOX(button_bar2), button_view2);
            
            console = gtk_text_view_new();
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
            gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(console), GTK_WRAP_WORD_CHAR);
            gtk_text_view_set_left_margin(GTK_TEXT_VIEW(console), 5);
            gtk_text_view_set_right_margin(GTK_TEXT_VIEW(console), 5);
            gtk_text_view_set_top_margin(GTK_TEXT_VIEW(console), 5);
            gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(console), 5);
            GtkWidget *console_container = gtk_scrolled_window_new();
            gtk_widget_set_hexpand(console_container, 1);
            //gtk_widget_set_vexpand(console_container, 1);
            gtk_widget_set_size_request(console_container, 1, 300);
            gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(console_container), console);
            gtk_box_append(GTK_BOX(v_box2), console_container);
    
    gtk_widget_show(window);
}

static void activate_callback(GtkApplication* app, gpointer user_data) {
    gui_run_at_startup();
}

static gboolean frontend_console_print_main_thread(gpointer user_data) {
    const char *msg = (const char *) user_data;
    console_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(console));
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(console_buffer, &end);
    gtk_text_buffer_insert(
        console_buffer, &end, msg, strlen(msg)
    );
    gtk_text_buffer_get_end_iter(console_buffer, &end);
    gtk_text_view_scroll_to_iter(
        GTK_TEXT_VIEW(console), &end, 0.0, TRUE, 0.5, 1.0
    );
}

void frontend_console_print(const char *msg) {
    g_idle_add(frontend_console_print_main_thread, (gpointer) strdup(msg));
}

void (*current_save_response_callback)(const char *) = NULL;

static void save_response_callback(GtkDialog *dialog, int response)
{
  if (response == GTK_RESPONSE_ACCEPT) {
      GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
      GFile *file = gtk_file_chooser_get_file(chooser);
      const char *path = g_file_get_path(file);
      current_save_response_callback(path);
  }

  gtk_window_destroy (GTK_WINDOW (dialog));
}

void frontend_ask_save_filename(void (*callback)(const char *)) {
    current_save_response_callback = callback;
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Export as STL", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_SAVE,
        "Cancel", GTK_RESPONSE_CANCEL,
        "Export", GTK_RESPONSE_ACCEPT, NULL
    );
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
    gtk_file_chooser_set_current_name(chooser, "Untitled.stl");
    gtk_widget_show(dialog);
    g_signal_connect(
        dialog, "response", G_CALLBACK(save_response_callback), NULL
    );
}

extern void frontend_redraw_viewer(void) {
    gtk_gl_area_queue_render(GTK_GL_AREA(viewer));
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
