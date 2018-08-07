#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
#include <iostream>
using namespace std;


float Vertices[] = {
    //top
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,

    //bottom
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    //front
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,

    //back
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    //left
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,

    //right
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

};

float vNormal[] = {
    //top
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,

    //bottom
    0.0f,  -1.0f,  0.0f,
    0.0f,  -1.0f,  0.0f,
    0.0f,  -1.0f,  0.0f,
    0.0f,  -1.0f,  0.0f,

    //front
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,

    //back
    0.0f,  0.0f,  -1.0f,
    0.0f,  0.0f,  -1.0f,
    0.0f,  0.0f,  -1.0f,
    0.0f,  0.0f,  -1.0f,

    //left
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,

    //right
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
};


float color[] = {

    //top
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,

    //bottom
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,

    //front
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,

    //back
    1.0f,  0.0f,  1.0f,
    1.0f,  0.0f,  1.0f,
    1.0f,  0.0f,  1.0f,
    1.0f,  0.0f,  1.0f,

    //left
    1.0f,  1.0f,  0.0f,
    1.0f,  1.0f,  0.0f,
    1.0f,  1.0f,  0.0f,
    1.0f,  1.0f,  0.0f,

    //right
    0.0f,  1.0f,  1.0f,
    0.0f,  1.0f,  1.0f,
    0.0f,  1.0f,  1.0f,
    0.0f,  1.0f,  1.0f,
};

GLuint Program;

GLuint verts;
GLuint vBo;
GLuint vCo;
GLuint vNo;

GLuint ULocModel;
GLuint ULocPorjView;

void init()
{
	ShaderInfo si[] = { { GL_VERTEX_SHADER, "HemisphereLight.v" },{ GL_FRAGMENT_SHADER, "HemisphereLight.g" },{ GL_NONE, "" } };

	Program = LoadShaders(si);

    glGenVertexArrays(1, &verts);
    glBindVertexArray(verts);
    glGenBuffers(1, &vBo);
    glBindBuffer(GL_ARRAY_BUFFER, vBo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &vCo);
    glBindBuffer(GL_ARRAY_BUFFER, vCo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &vNo);
    glBindBuffer(GL_ARRAY_BUFFER, vNo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vNormal), vNormal, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(2);


    ULocModel = glGetUniformLocation(Program, "matModel");
    ULocPorjView = glGetUniformLocation(Program, "matPorjectView");



    glClearColor(0.1f, 0.2f, 0.1f, 1.0f);

}

void display()
{
    static unsigned int Time = GetTickCount();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vmath::mat4 modle = vmath::mat4::identity();
    vmath::mat4 ProjView = vmath::mat4::identity();

    modle *= vmath::scale(0.2f, 0.2f, 0.2f);

    unsigned int timeNow = GetTickCount();
    float dt = float((timeNow - Time) % 8000) / 1000.0f;
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(1.0f, 0.0f, 0.0f));
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 1.0f, 0.0f));
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 0.0f, 1.0f));
    modle = vmath::translate(0.0f, 0.3f, 0.0f) * modle;


    glUseProgram(Program);
    glUniformMatrix4fv(ULocModel, 1, GL_FALSE, modle);
    glUniformMatrix4fv(ULocPorjView, 1, GL_FALSE, ProjView);


    vmath::vec3 LightSkyColor(0.9, 0.9, 0.9);
    vmath::vec3 LightGroundColor(0.2, 0.2, 0.2);
    vmath::vec3 LightPosition(0.0, 3.0, 0.0);
    glUniform3fv(glGetUniformLocation(Program, "LightSkyColor"), 1, LightSkyColor);
    glUniform3fv(glGetUniformLocation(Program, "LightGroundColor"), 1, LightGroundColor);
    glUniform3fv(glGetUniformLocation(Program, "LightPosition"), 1, LightPosition);

    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glBindVertexArray(verts);
    for (int i = 0; i < 6; ++i)
    {
        glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
    }

    modle = vmath::translate(0.0f, -0.9f, 0.0f) * modle;
    glUniformMatrix4fv(ULocModel, 1, GL_FALSE, modle);
    for (int i = 0; i < 6; ++i)
    {
        glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
    }


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
    glutInitWindowSize(400, 400);
    glutCreateWindow("Test chapter07");

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





