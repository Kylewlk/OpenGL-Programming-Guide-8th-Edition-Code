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

Vertex Verts[9] = { { { 255,0,0,255 },{ 0.0f, 0.9f, 0.0f } },
{ { 0,255,0,255 },{ -0.9f, -0.9f, 0.0f } },
{ { 0,0,255,255 },{ 0.9f, -0.9f, 0.0f } } ,

{ { 255,255,255,255 },{ 0.0f, 0.8f, -0.2f } } ,
{ { 255,255,255,255 },{ -0.4f, 0.0f, -0.2f } } ,
{ { 255,255,255,255 },{ 0.4f, 0.0f, -0.2f } } ,

{ { 255,255,255,255 },{ 0.0f, 0.0f, 0.2f } } ,
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(vert);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    GLuint QueryIDs[2];
    glGenQueries(2, QueryIDs);
    glBeginQuery(GL_SAMPLES_PASSED, QueryIDs[0]);
    glDrawArrays(GL_TRIANGLES, 3, 3);
    glEndQuery(GL_SAMPLES_PASSED);

    glBeginQuery(GL_SAMPLES_PASSED, QueryIDs[1]);
    glDrawArrays(GL_TRIANGLES, 6, 3);
    glEndQuery(GL_SAMPLES_PASSED);

    // 关闭深度测试测试条件渲染
    glDisable(GL_DEPTH_TEST);

    glBeginConditionalRender(QueryIDs[0], GL_QUERY_WAIT);
    glDrawArrays(GL_TRIANGLES, 3, 3);
    glEndConditionalRender();

    glBeginConditionalRender(QueryIDs[1], GL_QUERY_WAIT);
    glDrawArrays(GL_TRIANGLES, 6, 3);
    glEndConditionalRender();

    glDeleteQueries(2, QueryIDs);

    glutSwapBuffers();
    glutPostRedisplay();

}


int main(int argc, char*argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
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



