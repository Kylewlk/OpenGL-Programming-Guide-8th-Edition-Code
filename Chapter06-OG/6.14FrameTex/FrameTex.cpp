#include <iostream>


#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"

using namespace std;


struct Vertex
{
    GLfloat position[3];
    GLfloat TexCoord[2];
};

Vertex Verts[] = {
    { { -0.8f,-0.8f,0.0f },{ 0.0f,0.0f } },
    { { 0.2f,-0.8f,0.0f },{ 1.0f,0.0f } },
    { { -0.8f,0.2f,0.0f },{ 0.0f,1.0f } },
    { { 0.2f,0.2f,0.0f },{ 1.0f,1.0f } }, };

GLuint Program = 0;

GLuint vert;
GLuint vbo;

GLuint tex;

GLuint texFrame;
GLuint vertFrame;
GLuint vboFrame;
Vertex VertsFrame[] = {
    { { 0.22f,0.22f,0.0f },{ 0.0f,0.0f } },
    { { 0.8f,0.22f,0.0f },{ 1.0f,0.0f } },
    { { 0.22f,0.8f,0.0f },{ 0.0f,1.0f } },
    { { 0.8f,0.8f,0.0f },{ 1.0f,1.0f } }, };


GLuint Framet;

void Init()
{
    ShaderInfo si[] = { { GL_VERTEX_SHADER, "Chpater06.vert" },{ GL_FRAGMENT_SHADER, "Chapter06.frag" },{ GL_NONE, NULL } };
    Program = LoadShaders(si);

    glGenVertexArrays(1, &vert);
    glBindVertexArray(vert);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(Verts->position)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    glGenVertexArrays(1, &vertFrame);
    glBindVertexArray(vertFrame);
    glGenBuffers(1, &vboFrame);
    glBindBuffer(GL_ARRAY_BUFFER, vboFrame);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertsFrame), VertsFrame, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(Verts->position)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    float texData[] = { 1.0, 1.0, 0.0, 1.0,
        1.0, 0.0, 1.0, 1.0,
        0.0, 1.0, 1.0, 1.0,
        0.0, 1.0 ,0.0, 1.0 };

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 2, 2);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 2, 2, GL_RGBA, GL_FLOAT, texData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLuint err = 0;

    glGenTextures(1, &texFrame);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texFrame);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 200, 200, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    err = glGetError();

    glGenFramebuffers(1, &Framet);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, Framet);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texFrame, 0);//将纹理绑定到帧缓存颜色附件

    glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
    glUseProgram(Program);

}

void Display()
{

    static bool IsRendertoTex = true;
    if (IsRendertoTex)
    {
		//绘制一帧到纹理
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, Framet);
        glViewport(0, 0, 200, 200);
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(vert);
    glUniform1i(0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    if (IsRendertoTex)
    {
        IsRendertoTex = false;

        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texFrame);
        glGenerateMipmap(GL_TEXTURE_2D);//生成纹理的mipmap

        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);

        glViewport(0, 0, 400, 400);

    }
    else
    {
        glBindVertexArray(vertFrame);
        glUniform1i(0, 1);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
    glutSwapBuffers();

    glutPostRedisplay();

}


int main(int argc, char*argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE | GLUT_STENCIL);
    glutInitWindowSize(400, 400);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("Test OpenGL Chapter 06");

    if (glewInit())
    {
        cout << "Unable to Initialize GLEW." << endl;
        return 1;
    }
    Init();
    glutDisplayFunc(Display);
    glutMainLoop();

    return 0;
}



