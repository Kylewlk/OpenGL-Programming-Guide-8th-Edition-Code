#include <iostream>

#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"

using namespace std;

GLuint pro;
GLuint Vertex;

GLuint vboVert;
GLuint vboColor;

GLfloat vertices[][2] = { { -0.9,-0.9 },{ 0.9,-0.9},{ 0.9,0.9},{ -0.9, 0.9} };
GLfloat vertColor[][4] = { { 1.0,0,0,1.0 },{ 0,1.0,0,1.0 },{ 0,0,1.0,1.0 },{ 1.0,1.0,0,1.0 } };

void Init()
{
    ShaderInfo shaders[] = { { GL_VERTEX_SHADER, "test03.vert" },{ GL_FRAGMENT_SHADER, "test03.frag" } ,{ GL_NONE, NULL } };
    pro = LoadShaders(shaders);
    glUseProgram(pro);
    GLuint pos, color;
    pos = glGetAttribLocation(pro, "pos");
    color = glGetAttribLocation(pro, "col");

    glGenVertexArrays(1, &Vertex);
    glBindVertexArray(Vertex);

    glGenBuffers(1, &vboVert);
    glBindBuffer(GL_ARRAY_BUFFER, vboVert);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(pos);

    glGenBuffers(1, &vboColor);
    glBindBuffer(GL_ARRAY_BUFFER, vboColor);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertColor), vertColor, GL_STATIC_DRAW);

    glVertexAttribPointer(color, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(color);
    
    glClearColor(0.2, 0.2, 0.1, 1.0);
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(Vertex);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glFlush();

}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(400, 400);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow(argv[0]);

    if (glewInit())
    {
        cout << "Unable to initialize GLEW.." << endl;
        return 1;
    }
    Init();
    glutDisplayFunc(Display);
    glutMainLoop();

    return 0;
}