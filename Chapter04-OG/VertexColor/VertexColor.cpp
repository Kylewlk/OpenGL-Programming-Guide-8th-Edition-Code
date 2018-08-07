#include <iostream>


#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"

using namespace std;


struct Vertex
{
	GLubyte color[4];
	GLfloat position[2];
};

Vertex Verts[3] = { { { 255,0,0,255 },{ 0.8, 0.9 } },
					{ { 0,255,0,255 },{ -0.9, -0.9 } },
					{ { 0,0,255,255 },{ 0.9, -0.9 } } };

GLuint Program = 0;

GLuint vert;
GLuint vbo;

void Init()
{
	ShaderInfo si[] = { {GL_VERTEX_SHADER, "Chpater04.vert"},{GL_FRAGMENT_SHADER, "Chapter04.frag"}, {GL_NONE, NULL} };
	Program = LoadShaders(si);	

	glGenVertexArrays(1, &vert);
	glBindVertexArray(vert);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(Verts->color)));
	glEnableVertexAttribArray(1);


	glClearColor(0.0, 0.0, 0.0, 1.0);
	glUseProgram(Program);
}

void Display()
{
	//glScissor(80, 80, 250, 200);
	//glEnable(GL_SCISSOR_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	//glDisable(GL_MULTISAMPLE);

	glBindVertexArray(vert);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
	glutPostRedisplay();

    Sleep(20);
}


int main(int argc, char*argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE | GLUT_MULTISAMPLE);
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



