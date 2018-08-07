#include <iostream>


#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"

using namespace std;


struct Vertex
{
    GLubyte color[4];
    GLfloat position[3];
};

Vertex Verts[6] = { { { 255,0,0,255 },{ 0.6f, 0.9f, 0.0f } },
{ { 0,255,0,255 },{ -0.9f, -0.9f, 0.0f } },
{ { 0,0,255,255 },{ 0.9f, -0.9f, 0.0f } } ,
{ { 255,255,255,255 },{ 0.3f, 0.0f, 0.2f } } ,
{ { 255,255,255,255 },{ -0.4f, -0.8f, 0.2f } } ,
{ { 255,255,255,255 },{ 0.4f, -0.8f, 0.2f } } };

GLuint Program = 0;

GLuint vert;
GLuint vbo;

void Init()
{
    ShaderInfo si[] = { { GL_VERTEX_SHADER, "Chpater04.vert" },{ GL_FRAGMENT_SHADER, "Chapter04.frag" },{ GL_NONE, NULL } };
    Program = LoadShaders(si);

    glGenVertexArrays(1, &vert);
    glBindVertexArray(vert);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(Verts->color)));
    glEnableVertexAttribArray(1);

    glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
    glUseProgram(Program);

}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vert);

    glEnable(GL_BLEND);//启用融合
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//启用透明绘制
    glEnable(GL_LINE_SMOOTH);//启用线段平滑
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // 设置线段平滑程度
    glLineWidth(6);
    glDrawArrays(GL_LINE_LOOP, 0, 3);

    glEnable(GL_BLEND);//启用融合
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//启用透明绘制
    glEnable(GL_POLYGON_SMOOTH);//启用图形平滑
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST); //设置图形平滑程度
    glDrawArrays(GL_TRIANGLES, 3, 3);

    glutSwapBuffers();
    glutPostRedisplay();
    Sleep(20);
}


int main(int argc, char*argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE |GLUT_STENCIL);
    glutInitWindowSize(400, 400);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("Test OpenGL Chapter 04");

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



