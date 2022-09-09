#include "gui.h"

#ifdef HAVE_GUI

extern void frontend_create(const char *name);
extern void frontend_console_print(const char *msg);
extern void frontend_redraw_viewer(void);
extern void frontend_main(int argc, char *argv[]);

extern const char *frontend_get_editor_text(void);
extern void frontend_ask_save_filename(void (*callback)(const char *));


void frontend_init_graphics(void);
void frontend_realize_graphics(int scale_factor);
void frontend_resize_graphics(int width, int height);
void frontend_unrealize_graphics(void);
void frontend_render_graphics(void);
void frontend_send_triangles(
    const float *coords, unsigned int ncoords,
    const unsigned int *indices, unsigned int nindices
);
void frontend_set_matrix(float *matrix);

#endif // HAVE_GUI
