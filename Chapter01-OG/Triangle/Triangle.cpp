#include <iostream>
using namespace std;

#include "stdio.h"
#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"

enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {ArrayBuffer, NumBuffers};
enum Attrib_IDs {vPosition = 0};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

GLuint program;

void init()
{
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	GLfloat vertices[NumVertices][2] = {
		{-0.9f,-0.9f},
		{0.85f,-0.90f},
		{-0.90f, 0.85f},
		{0.90f, -0.85f},
		{0.90f,0.90f},
		{-0.85f, 0.90f}
	};
	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	ShaderInfo shaders[] = { {GL_VERTEX_SHADER, "triangles.vert"},{GL_FRAGMENT_SHADER, "triangles.frag"},{GL_NONE, NULL} };

	program = LoadShaders(shaders);
	glUseProgram(program);

    GLuint pos = glGetAttribLocation(program, "vPosition");
	glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(pos);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glFlush();
	Sleep(30);//减少CPU的占用
}


int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(argv[0]);

	if (glewInit())
	{
		cout << "Unable to initialize GLEW.. " << endl;
		return 1;
	}
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
