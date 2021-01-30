#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
#include "vbm.h"
#include <iostream>
using namespace std;

GLuint Program;

float Verts[] = { -0.9f, -0.9f,   0.9f, -0.9f,    0.9f, 0.9f,    -0.9f, 0.9f };

GLuint vao;
GLuint vbo;

void init()
{
    ShaderInfo shaders[] =
    {
        { GL_VERTEX_SHADER, "BrickSquare.vert" },
        { GL_FRAGMENT_SHADER, "BrickSquare.frag" },
        { GL_NONE,"" }
    };
    Program = LoadShaders(shaders);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);


    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

}

void display()
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(Program);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

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
	else
	{
		Sleep(30);
	}
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitContextVersion(4, 3);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Test VBM");

    if (glewInit() != 0)
    {
        cout << "Unable to initilizate GLEW." << endl;
        return 0;
    }

    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}



