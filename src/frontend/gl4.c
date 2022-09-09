#include "glad.h"
#include <stdio.h>

#undef NDEBUG

void error(const char *fmt, ...);

void warning(const char *fmt, ...);

void info(const char *fmt, ...);

void frontend_init_graphics(void) {
}

#ifndef NDEBUG
void APIENTRY debug_callback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar *message,
    const void *userParam
) {
    char *source_txt;
    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             source_txt = "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   source_txt = "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: source_txt = "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     source_txt = "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     source_txt = "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           source_txt = "Source: Other"; break;
    }

    char *type_txt;
    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               type_txt = "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_txt = "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  type_txt = "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         type_txt = "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         type_txt = "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              type_txt = "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          type_txt = "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           type_txt = "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               type_txt = "Type: Other"; break;
    }

    char *severity_txt;
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         severity_txt = "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       severity_txt = "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          severity_txt = "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: severity_txt = "Severity: notification"; break;
    }

    printf("%s %s %s %s\n", source_txt, type_txt, severity_txt, message);
};
#endif


const char* vertex_shader =
"#version 400\n"
"in vec4 vp;"
"uniform mat4 mvp;"
"void main() {"
"  gl_Position = mvp * vp;"
"}";

const char* fragment_shader =
"#version 400\n"
"void main() {"
"  gl_FragColor = vec4(1.0, 1.0, 0.5, 1.0);"
"}";

const char* effects_vertex_shader =
"#version 400\n"
"in vec4 vp;"
"out vec2 UV;"
"void main() {"
"  gl_Position = vp;"
"  UV = vp.xy * vec2(0.5, 0.5) + vec2(0.5, 0.5);"
"}";

const char* effects_fragment_shader =
"#version 400\n"
"in vec2 UV;"
"uniform sampler2D tex;"
"uniform sampler2D depth;"
"void main() {"
"  gl_FragColor = texture2D(tex, UV);"
"  gl_FragDepth = texture2D(depth, UV).x;"
"}";

GLuint shader_program = 0;
GLuint vbo = 0;
GLuint vao = 0;
GLuint ebo = 0;

GLuint mvp = 0;

GLuint tmp_FBO = 0;
GLuint tmp_tex = 0;
GLuint depth_tex = 0;

GLuint effects_program = 0;
GLuint quad_VBO = 0;
GLuint quad_VAO = 0;

const GLfloat quad_vertices[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f
};

void frontend_realize_graphics(int scale_factor) {
    if(!gladLoadGL()) {
        error(
            "error: OpenGL extension loading failed.\n"
        );
    }
    
    #ifndef NDEBUG
    glDebugMessageCallback(debug_callback, NULL);
    #endif

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    if(glGetError()) printf("error: could not create and bind VAO.\n");
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    if(glGetError()) printf("error: could not create and bind VBO.\n");
    
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    if(glGetError()) printf("error: could not create and bind EBO.\n");
    
    int status;
    glGenFramebuffers(1, &tmp_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, tmp_FBO);

    glGenTextures(1, &tmp_tex);
    glBindTexture(GL_TEXTURE_2D, tmp_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tmp_tex, 0);

    glGenTextures(1, &depth_tex);
    glBindTexture(GL_TEXTURE_2D, depth_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_tex, 0);

    glGenVertexArrays(1, &quad_VAO);
    glBindVertexArray(quad_VAO);

    glGenBuffers(1, &quad_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, quad_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);


    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE || glGetError())
        printf("error: could not compile vertex shader.\n");
    
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE || glGetError())
        printf("error: could not compile fragment shader.\n");
    
    shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
    if(status == GL_FALSE || glGetError())
        printf("error: could not attach and link shaders.\n");
    
    mvp = glGetUniformLocation(shader_program, "mvp");

    GLuint effects_vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(effects_vs, 1, &effects_vertex_shader, NULL);
    glCompileShader(effects_vs);
    glGetShaderiv(effects_vs, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE || glGetError())
        printf("error: could not compile effects vertex shader.\n");

    GLuint effects_fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(effects_fs, 1, &effects_fragment_shader, NULL);
    glCompileShader(effects_fs);
    glGetShaderiv(effects_fs, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE || glGetError())
        printf("error: could not compile effects fragment shader.\n");
    
    effects_program = glCreateProgram();
    glAttachShader(effects_program, effects_fs);
    glAttachShader(effects_program, effects_vs);
    glLinkProgram(effects_program);
    glGetProgramiv(effects_program, GL_LINK_STATUS, &status);
    if(status == GL_FALSE || glGetError())
        printf("error: could not attach and link effects shaders.\n");
}

int view_width, view_height;
int dimensions_dirty = 0;

void frontend_resize_graphics(int width, int height) {
    int status;
    
    view_width = width;
    view_height = height;
    dimensions_dirty = 1;
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
    
    if(dimensions_dirty) {
        glBindTexture(GL_TEXTURE_2D, tmp_tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, view_width, view_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        if(status = glGetError()) warning("warning: offscreen texture creation did not succeed (0x%x).\n", status);
        
        glBindTexture(GL_TEXTURE_2D, depth_tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, view_width, view_height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
        if(status = glGetError()) warning("warning: offscreen depth texture creation did not succeed (0x%x).\n", status);

        dimensions_dirty = 0;
    }
    
    /* Render to texture */
    GLuint defaultFBO;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&defaultFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, tmp_FBO);
    GLenum drawBuffersList[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, drawBuffersList);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_program);
    if(status = glGetError()) warning("warning: shader binding did not succeed (0x%x).\n", status);
    
    if(matrix_dirty) {
        glUniformMatrix4fv(mvp, 1, GL_FALSE, modelview_matrix);
        if(glGetError()) warning("warning: modelview matrix uploading did not succeed.\n");
        matrix_dirty = 0;
    }
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    if(status = glGetError()) warning("warning: VBO binding did not succeed (0x%x).\n", status);
    glEnableVertexAttribArray(0);
    if(glGetError()) warning("warning: enabling VBO did not succeed.\n");
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
        glDrawElements(GL_TRIANGLES, element_count, GL_UNSIGNED_INT, NULL);
        //glDrawArrays(GL_LINE_STRIP, 0, element_count); // Interesting results
        if(status = glGetError()) warning("warning: visual rendering did not succeed (0x%x).\n", status);
    }
    
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    
    /* Now apply effects */
    if (glIsFramebuffer(defaultFBO)) {
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
        GLenum drawBuffersList[1] = { GL_COLOR_ATTACHMENT0 };
        glDrawBuffers(1, drawBuffersList);
    } else {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDrawBuffer(GL_BACK);
    }
    if(status = glGetError()) warning("warning: framebuffer binding did not succeed (0x%x).\n", status);
    glUseProgram(effects_program);
    if(status = glGetError()) warning("warning: effects shader binding did not succeed (0x%x).\n", status);
    
    glBindVertexArray(quad_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, quad_VBO);
    if(status = glGetError()) warning("warning: quad VBO binding did not succeed (0x%x).\n", status);
    glEnableVertexAttribArray(0);
    if(glGetError()) warning("warning: enabling quad VBO did not succeed.\n");
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    if(status = glGetError()) warning("warning: effects VBO configuration did not succeed (0x%x).\n", status);

    GLuint programID;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&programID);

    GLuint attr_tex = glGetUniformLocation(programID, "tex");
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, tmp_tex);
    if(status = glGetError()) warning("warning: texture binding did not succeed (0x%x).\n", status);
    glUniform1i(attr_tex, 1);

    GLuint attr_depth = glGetUniformLocation(programID, "depth");
    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_2D, depth_tex);
    if(status = glGetError()) warning("warning: depth texture binding did not succeed (0x%x).\n", status);
    glUniform1i(attr_depth, 2);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    if(status = glGetError()) warning("warning: texture rendering did not succeed (0x%x).\n", status);
    
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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
