

#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"

#include <iostream>
using namespace std;

GLuint program;
GLuint vao;
GLuint vbo;

GLfloat vert[]={ -0.9f, -0.9f,    0.9f, -0.9f,     0.9f, 0.9f,    -0.9f, 0.9f, 
				1.0, 0.0, 0.0,    0.0, 1.0, 0.0,  0.0, 0.0, 1.0, 0.0, 0.0, 1.0
};


void init()
{
	ShaderInfo si[] = {
		{ GL_VERTEX_SHADER, "Triangle.v"},
		{GL_TESS_CONTROL_SHADER, "Triangle.tesc"},
		{GL_TESS_EVALUATION_SHADER, "Triangle.tese"},
		{ GL_FRAGMENT_SHADER, "Triangle.g"},
		{GL_NONE, ""}
	};

	program = LoadShaders(si);

    glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float)*2*4));
	glEnableVertexAttribArray(1);

	glClearColor(0.1, 0.1, 0.1, 1.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);
	glPatchParameteri(GL_PATCH_VERTICES, 3);

	glPointSize(10);
	
	glBindVertexArray(vao);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_PATCHES, 0, 3);

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
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE|GLUT_STENCIL);
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









