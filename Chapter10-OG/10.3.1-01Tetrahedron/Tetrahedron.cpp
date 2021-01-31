

#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"

#include <iostream>
using namespace std;

GLuint program;
GLuint vao;
GLuint vbo;

GLfloat vert[] = { 
    0.0f, 0.9f, -0.9f,    -0.9f,-0.9f, -0.9f,     0.9f, -0.9f,-0.9f,    0.0f,0.0f, 0.9f,//四面体的四个点

    1.0, 0.0, 0.0,       0.0, 1.0, 0.0,        0.0, 0.0, 1.0,         0.0, 1.0, 1.0 //四个面的颜色
};


void init()
{
    ShaderInfo si[] = {
        { GL_VERTEX_SHADER, "Tetrahedron.vert" },
        { GL_GEOMETRY_SHADER, "Tetrahedron.geom" },
        { GL_FRAGMENT_SHADER, "Tetrahedron.frag" },
        { GL_NONE, "" }
    };

    program = LoadShaders(si);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float) * 3 * 4));
    glEnableVertexAttribArray(1);

    glClearColor(0.1, 0.1, 0.1, 1.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);

    static unsigned int Time = GetTickCount();

    vmath::mat4 modle = vmath::mat4::identity();

    unsigned int timeNow = GetTickCount();
    float dt = float((timeNow - Time) % 8000) / 1000.0f;
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(1.0f, 0.0f, 0.0f));
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 0.0f, 1.0f));
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 1.0f, 0.0f));
    modle *= vmath::scale(0.4f, 0.4f, 0.4f);


    glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, modle);


    glBindVertexArray(vao);
    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
    //glProvokingVertex(GL_LAST_VERTEX_CONVENTION);
    glDrawArrays(GL_LINES_ADJACENCY, 0, 4); //GL_LINES_ADJACENCY 刚好有四个点输入几何着色器，

    glutSwapBuffers();
}

void idle()
{
    static unsigned int Time = GetTickCount();
    unsigned int timeNow = GetTickCount();

    if (timeNow - Time > 15)
    {
        Time = timeNow;
        glutPostRedisplay();
    }
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitContextVersion(4, 3);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Test OpenGL");

    if (glewInit() != 0)
    {
        cout << "Can not initilizate GLEW" << endl;
        return 1;
    }

    init();
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}









