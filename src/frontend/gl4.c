#include "glad.h"

void error(const char *fmt, ...);

void warning(const char *fmt, ...);

void info(const char *fmt, ...);

void frontend_init_graphics(void) {
}

const char* vertex_shader =
"#version 400\n"
"in vec4 vp;"
"uniform mat4 mvp;"
"void main() {"
"  gl_Position = mvp * vp;"
"  gl_Position.z -= 1.0;"
"}";

const char* fragment_shader =
"#version 400\n"
"out vec4 frag_color;"
"void main() {"
"  frag_color = vec4(0.5, 0.5, gl_FragCoord.z, 1.0);"
"}";

GLuint shader_program = 0;
GLuint vbo = 0;
GLuint vao = 0;
GLuint ebo = 0;

GLuint mvp = 0;

void frontend_realize_graphics(int scale_factor) {
    if(!gladLoadGL()) {
        error(
            "error: OpenGL extension loading failed.\n"
        );
    }
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    if(glGetError()) error("error: could not create and bind VAO.\n");
    
    vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW); //D
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    if(glGetError()) error("error: could not create and bind VBO.\n");
    
    ebo = 0;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW); //D
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    if(glGetError()) error("error: could not create and bind EBO.\n");
    
    int status;
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE || glGetError())
        error("error: could not compile vertex shader.\n");
    
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE || glGetError())
        error("error: could not compile fragment shader.\n");
    
    shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
    if(status == GL_FALSE || glGetError())
        error("error: could not attach and link shaders.\n");
    
    mvp = glGetUniformLocation(shader_program, "mvp");
}

void frontend_unrealize_graphics(void) {
}

const static unsigned int *elements = NULL;
static unsigned int element_count = 0;
const static float *coordinates = NULL;
static unsigned int coordinate_count = 0;
int update_pending = 0;

GLfloat modelview_matrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};
int matrix_dirty = 1;

void frontend_render_graphics(void) {
    int status = 0;
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_program);
    if(status = glGetError()) warning("warning: shader binding did not succeed (0x%x).\n", status);
    
    if(matrix_dirty) {
        glUniformMatrix4fv(mvp, 1, GL_FALSE, modelview_matrix);
        if(glGetError()) warning("warning: modelview matrix uploading did not succeed.\n");
        matrix_dirty = 0;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    if(status = glGetError()) warning("warning: VBO binding did not succeed (0x%x).\n", status);
    glEnableVertexAttribArray(0);
    if(glGetError()) warning("warning: VBO enabling did not succeed.\n");
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    if(status = glGetError()) warning("warning: VBO configuration did not succeed (0x%x).\n", status);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    if(status = glGetError()) warning("warning: EBO binding did not succeed (0x%x).\n", status);
    
    if(update_pending) {
        glBufferData(GL_ARRAY_BUFFER, coordinate_count * sizeof(float), NULL, GL_DYNAMIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, coordinate_count * sizeof(float), coordinates, GL_DYNAMIC_DRAW);
        if(glGetError()) warning("warning: triangle uploading did not succeed.\n");
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_count * sizeof(unsigned int), NULL, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_count * sizeof(unsigned int), elements, GL_STATIC_DRAW);
        if(glGetError()) warning("warning: index uploading did not succeed.\n");
        update_pending = 0;
    }
    
    if(elements != NULL) {
        //glDrawElements(GL_TRIANGLES, element_count, GL_UNSIGNED_INT, NULL);
        glDrawArrays(GL_LINE_STRIP, 0, element_count);
        if(status = glGetError()) warning("warning: visual rendering did not succeed (0x%x).\n", status);
    }
    
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void frontend_send_triangles(
    const float *coords, unsigned int ncoords,
    const unsigned int *indices, unsigned int nindices
) {
    coordinates = coords;
    coordinate_count = ncoords;
    elements = indices;
    element_count = nindices;
    update_pending = 1;
}

void frontend_set_matrix(float *matrix) {
    int n;
    for(n = 0; n < 16; n++)
        modelview_matrix[n] = matrix[n];
    matrix_dirty = 1;
}
