/* $URL$
   $Rev$
   $Author$
   $Date$
   $Id$
 */

#include "vgl.h"
#include <vermilion.h>

#include "vapp.h"
#include "vutils.h"
#include "vbm.h"

#include "vmath.h"

#include <stdio.h>

BEGIN_APP_DECLARATION(LoadTextureExample)
    // Override functions from base class
    virtual void Initialize(const char * title);
    virtual void Display(bool auto_redraw);
    virtual void Finalize(void);
    virtual void Reshape(int width, int height);

    // Member variables
    float aspect;
    GLuint base_prog;
    GLuint vao;

    GLuint quad_vbo;

    GLuint tex;
END_APP_DECLARATION()

DEFINE_APP(LoadTextureExample, "Simple Static Texture Example")

void LoadTextureExample::Initialize(const char * title)
{
    base::Initialize(title);

    base_prog = glCreateProgram();

    static const char quad_shader_vs[] =
        "#version 330 core\n"
        "\n"
        "layout (location = 0) in vec2 in_position;\n"
        "layout (location = 1) in vec2 in_tex_coord;\n"
        "\n"
        "out vec2 tex_coord;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = vec4(in_position, 0.5, 1.0);\n"
        "    tex_coord = in_tex_coord;\n"
        "}\n"
    ;

    static const char quad_shader_fs[] =
        "#version 330 core\n"
        "\n"
        "in vec2 tex_coord;\n"
        "\n"
        "layout (location = 0) out vec4 color;\n"
        "\n"
        "uniform sampler2D tex;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "    color = texture(tex, tex_coord);\n"
        "}\n"
    ;

    vglAttachShaderSource(base_prog, GL_VERTEX_SHADER, quad_shader_vs);
    vglAttachShaderSource(base_prog, GL_FRAGMENT_SHADER, quad_shader_fs);

    glGenBuffers(1, &quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);

    static const GLfloat quad_data[] =
    {
         0.75f, -0.75f,
        -0.75f, -0.75f,
        -0.75f, 0.75f,
         0.75f, 0.75f,

         0.0f, 0.0f,
         1.0f, 0.0f,
         1.0f, 1.0f,
         0.0f, 1.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_data), quad_data, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(8 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glLinkProgram(base_prog);

    glGenTextures(1, &tex);
	glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, tex);

    static const unsigned char texture_data[] =
    {
        0xF0, 0x00, 0xF0, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xF0, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF
    };

    glTexStorage2D(GL_TEXTURE_2D, 4, GL_R8, 8, 8);
    glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    0, 0,
                    8, 8,
                    GL_RED, GL_UNSIGNED_BYTE,
                    texture_data);

	int n = glGetError();

    static const GLint swizzles[] = { GL_RED, GL_RED, GL_RED, GL_ONE };
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzles);//RGB���������к�ɫ����������Ϊ��ɫ

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenerateMipmap(GL_TEXTURE_2D);
}

void LoadTextureExample::Display(bool auto_redraw)
{
    float t = float(GetTickCount() & 0x3FFF) / float(0x3FFF);
    static const vmath::vec3 X(1.0f, 0.0f, 0.0f);
    static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
    static const vmath::vec3 Z(0.0f, 0.0f, 1.0f);

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_CULL_FACE);
    glUseProgram(base_prog);
	glUniform1i(glGetUniformLocation(base_prog, "tex"), 2);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, tex);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    base::Display();
}

void LoadTextureExample::Finalize(void)
{
    glUseProgram(0);
    glDeleteProgram(base_prog);
    glDeleteTextures(1, &tex);
    glDeleteVertexArrays(1, &tex);
}

void LoadTextureExample::Reshape(int width, int height)
{
    glViewport(0, 0 , width, height);

    aspect = float(height) / float(width);
}
