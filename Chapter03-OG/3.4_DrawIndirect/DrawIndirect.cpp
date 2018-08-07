#include <iostream>

#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"

using namespace std;

GLuint pro;
GLuint Vertex;

GLuint vbo;
GLuint cmdbo;

GLfloat vertices[][2] = { {-0.25, 0.25}, {-0.25,-0.25},{ 0.25,0.25},{ 0.25,-0.25} };

GLfloat vertColor[][4] = { {1.0,0,0,1.0}, { 0,1.0,0,1.0 },{ 0,0,1.0,1.0 },{ 1.0,1.0,0,1.0 } };

GLfloat vertPosOffsets[][2] = { { -0.5, 0.5 },{ -0.5,-0.5 },{ 0.5,0.5 },{ 0.5,-0.5 } ,{ 0.0,0.0 }};


typedef  struct {
	GLuint  count;
	GLuint  primCount;
	GLuint  first;
	GLuint  baseInstance;
} DrawArraysIndirectCommand;
DrawArraysIndirectCommand cmd = { 4, 4, 0, 0 };

void Init()
{
	ShaderInfo shaders[] = { { GL_VERTEX_SHADER, "test03.vert"}, { GL_FRAGMENT_SHADER, "test03.frag"} , {GL_NONE, NULL} };
	pro = LoadShaders(shaders);

	glGenVertexArrays(1, &Vertex);
	glBindVertexArray(Vertex);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertColor) + sizeof(vertices)+ 4 * sizeof(vertPosOffsets), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(vertColor), vertColor);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+sizeof(vertColor), sizeof(vertPosOffsets), vertPosOffsets);

	glUseProgram(pro);
	GLuint pos, color, PosOffset;
	pos = glGetAttribLocation(pro, "pos");
	color = glGetAttribLocation(pro, "col");
	PosOffset = glGetAttribLocation(pro, "PosOffset");

	glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(pos);

	glVertexAttribPointer(color, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));
	glEnableVertexAttribArray(color);
    glVertexAttribDivisor(color, 1); //开启后为四种不同颜色的单色正方形

	glVertexAttribPointer(PosOffset, 2, GL_FLOAT, GL_FALSE, sizeof(vertPosOffsets[0]), BUFFER_OFFSET(sizeof(vertices)+sizeof(vertColor)));
	glEnableVertexAttribArray(PosOffset);
    glVertexAttribDivisor(PosOffset, 1);//每个实力更新一次

	glGenBuffers(1, &cmdbo);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, cmdbo);
	glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(cmd), &cmd, GL_STATIC_DRAW);

}


//typedef  struct {
//	uint  count;
//	uint  primCount;
//	uint  first;
//	uint  baseInstance;
//} DrawArraysIndirectCommand;
//
//const DrawArraysIndirectCommand *cmd = (const DrawArraysIndirectCommand *)indirect;
//glDrawArraysInstancedBaseInstance(mode, cmd->first, cmd->count, cmd->primCount, cmd->baseInstance);


void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(Vertex);

	glDrawArraysIndirect(GL_TRIANGLE_STRIP, BUFFER_OFFSET(0));
	//glDrawArraysInstancedBaseInstance(GL_TRIANGLE_STRIP, cmd.first, cmd.count, cmd.primCount, cmd.baseInstance);

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