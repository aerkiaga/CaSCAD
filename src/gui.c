#include "gui.h"

#ifdef HAVE_GUI
#include "backend.h"
#include "builtin.h"
#include "cascad.h"
#include "config.h"
#include "context.h"
#include "frontend.h"
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <threads.h>

static void gui_update_matrix();

void gui_message_handler(char type, const char *msg) {
    frontend_console_print(msg);
    if(type == 'e') thrd_exit(1);
}

void gui_run_at_startup(void) {
    frontend_create(PACKAGE_STRING);
    frontend_console_print(CASCAD_NOTICE);
}

float viewer_aspect_ratio = 1.0;

void gui_run_at_gl_realize(int scale_factor) {
    frontend_realize_graphics(scale_factor);
}

void gui_run_at_gl_resize(int width, int height) {
    viewer_aspect_ratio = width / (float) height;
    gui_update_matrix();
    frontend_resize_graphics(width, height);
}

void gui_run_at_gl_unrealize(void) {
    frontend_unrealize_graphics();
}

void gui_run_at_gl_render(void) {
    frontend_render_graphics();
}

static cascad_shape_t current_shape = NULL;

static void gui_finalize_work(cascad_shape_t output) {
    if(!output) return;
    
    if(cascad_get_shape_type(output) == CASCAD_SOLID) {
        float *coords;
        unsigned int ncoords;
        unsigned int *indices;
        unsigned int nindices;
        backend_export_triangles((value_t) output + 1, &coords, &ncoords, &indices, &nindices);
        frontend_send_triangles(coords, ncoords, indices, nindices);
        gui_redraw_viewer();
    }
    
    current_shape = output;
}

void gui_run_at_preview(void) {
    cascad_run_string_async(frontend_get_editor_text(), NULL, gui_finalize_work);
}

static void gui_export_stl_filename_callback(const char *filename) {
    cascad_export_stl_async(current_shape, filename, 1, NULL);
}

void gui_run_at_export_stl(void) {
    if(!current_shape) return;
    if(cascad_get_shape_type(current_shape) != CASCAD_SOLID) return;
    frontend_ask_save_filename(gui_export_stl_filename_callback);
}

void gui_redraw_viewer(void) {
    frontend_redraw_viewer();
}

const char *gui_lookup_word(const char *word) {
    if(
        !strcmp(word, "undef")
    ) return "undef";
    else if(
        !strcmp(word, "PI")
    ) return "value";
    else if(
        !strcmp(word, "each") ||
        !strcmp(word, "else") ||
        !strcmp(word, "false") ||
        !strcmp(word, "for") ||
        !strcmp(word, "function") ||
        !strcmp(word, "if") ||
        !strcmp(word, "include") ||
        !strcmp(word, "intersection_for") ||
        !strcmp(word, "let") ||
        !strcmp(word, "module") ||
        !strcmp(word, "true") ||
        !strcmp(word, "use")
    ) return "keyword";
    else {
        builtin_t builtin = search_in_builtins(word);
        if(builtin) {
            uintptr_t builtin_type = builtin[1].u;
            if(builtin_type == BIND_TYPE_FUNCTION) return "function";
            else if(builtin_type == BIND_TYPE_MODULE) return "module";
        }
    }
    return NULL;
}

static void multiply_matrix(float *c, const float *a, const float *b) {
    c[0] = a[0]*b[0] + a[1]*b[4] + a[2]*b[8] + a[3]*b[12];
    c[1] = a[0]*b[1] + a[1]*b[5] + a[2]*b[9] + a[3]*b[13];
    c[2] = a[0]*b[2] + a[1]*b[6] + a[2]*b[10] + a[3]*b[14];
    c[3] = a[0]*b[3] + a[1]*b[7] + a[2]*b[11] + a[3]*b[15];
    c[4] = a[4]*b[0] + a[5]*b[4] + a[6]*b[8] + a[7]*b[12];
    c[5] = a[4]*b[1] + a[5]*b[5] + a[6]*b[9] + a[7]*b[13];
    c[6] = a[4]*b[2] + a[5]*b[6] + a[6]*b[10] + a[7]*b[14];
    c[7] = a[4]*b[3] + a[5]*b[7] + a[6]*b[11] + a[7]*b[15];
    c[8] = a[8]*b[0] + a[9]*b[4] + a[10]*b[8] + a[11]*b[12];
    c[9] = a[8]*b[1] + a[9]*b[5] + a[10]*b[9] + a[11]*b[13];
    c[10] = a[8]*b[2] + a[9]*b[6] + a[10]*b[10] + a[11]*b[14];
    c[11] = a[8]*b[3] + a[9]*b[7] + a[10]*b[11] + a[11]*b[15];
    c[12] = a[12]*b[0] + a[13]*b[4] + a[14]*b[8] + a[15]*b[12];
    c[13] = a[12]*b[1] + a[13]*b[5] + a[14]*b[9] + a[15]*b[13];
    c[14] = a[12]*b[2] + a[13]*b[6] + a[14]*b[10] + a[15]*b[14];
    c[15] = a[12]*b[3] + a[13]*b[7] + a[14]*b[11] + a[15]*b[15];
}

float current_scale = 1.0f;
float current_angle_x = 0.0f;
float current_angle_y = 0.0f;

static void gui_update_matrix() {
    float tmp_matrix[16];
    
    float xrot_matrix[16] = {
        1.0f, 0.0f,                     0.0f,                   0.0f,
        0.0f, cosf(current_angle_x),    -sinf(current_angle_x), 0.0f,
        0.0f, sinf(current_angle_x),    cosf(current_angle_x),  0.0f,
        0.0f,                   0.0f,   0.0f,                   1.0f
    };
    
    float yrot_matrix[16] = {
        cosf(current_angle_y),  0.0f, sinf(current_angle_y),    0.0f,
        0.0f,                   1.0f, 0.0f,                     0.0f,
        -sinf(current_angle_y), 0.0f, cosf(current_angle_y),    0.0f,
        0.0f,                   0.0f, 0.0f,                     1.0f
    };
    
    multiply_matrix(tmp_matrix, yrot_matrix, xrot_matrix);
    
    float tmp2_matrix[16];

    float scale_matrix[16] = {
        current_scale,  0.0f,           0.0f,           0.0f,
        0.0f,           current_scale,  0.0f,           0.0f,
        0.0f,           0.0f,           current_scale,  0.0f,
        0.0f,           0.0f,           0.0f,           1.0f
    };

    multiply_matrix(tmp2_matrix, tmp_matrix, scale_matrix);

    float near = 0.1f;
    float far = 10.0f;
    
    float proj_matrix[16] = {
        1.0f, 0.0f,                 0.0f,                   0.0f,
        0.0f, viewer_aspect_ratio,  0.0f,                   0.0f,
        0.0f, 0.0f,                 2/(far-near),           -(far+near)/(far-near),
        0.0f, 0.0f,                 0.0f,                   1.0f
    };
    
    float out_matrix[16];
    
    multiply_matrix(out_matrix, tmp2_matrix, proj_matrix);
    
    frontend_set_matrix(out_matrix);
    gui_redraw_viewer();
}

void gui_perform_pan(double dx, double dy) {    
    float angle_y = 0.025 * dx;
    current_angle_y -= angle_y;
    
    float angle_x = 0.025 * dy;
    current_angle_x -= angle_x;
    if(current_angle_x > M_PI/2.0f) current_angle_x = M_PI/2.0f;
    if(current_angle_x < -M_PI/2.0f) current_angle_x = -M_PI/2.0f;
    
    gui_update_matrix();
}

void gui_perform_zoom(double dy) {
    double ratio = pow(2.0, -dy / 10.0);
    current_scale *= ratio;

    gui_update_matrix();
}

void gui_main(int argc, char *argv[]) {
    set_message_handler(gui_message_handler);
    frontend_init_graphics();
    frontend_main(argc, argv);
}

#endif // HAVE_GUI
