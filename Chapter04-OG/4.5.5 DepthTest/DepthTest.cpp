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

Vertex Verts[6] = 
{ { { 255,0,0,255 },    {  0.0f,  0.0f, 0.0f } },
  { { 0,255,0,255 },    { -0.9f, -0.9f, 0.0f } },
  { { 0,0,255,255 },    {  0.9f, -0.9f, 0.0f } } ,

  { { 255,255,255,255 },{  0.0f,  0.4f, 0.1f } } ,
  { { 255,255,255,255 },{ -0.4f, -0.4f, 0.1f } } ,
  { { 255,255,255,255 },{  0.4f, -0.4f, 0.1f } } };

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
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(Verts->color)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    glClearColor(0.2, 0.1, 0.3, 1.0);
    glUseProgram(Program);

    glEnable(GL_DEPTH_TEST);
}

void Display()
{
    //glDrawBuffer(GL_FRONT_AND_BACK);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vert);

    glEnable(GL_DEPTH_TEST);

	glEnableVertexAttribArray(0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //glDisable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(0.0, -3.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glVertexAttrib4f(0, 0.0,0.3,1.0,1.0);
    glDisableVertexAttribArray(0);

    glLineWidth(85);
    glDrawArrays(GL_TRIANGLES, 0, 6);


    glutSwapBuffers();
    glutPostRedisplay();
	Sleep(20);
}


int main(int argc, char*argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
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



