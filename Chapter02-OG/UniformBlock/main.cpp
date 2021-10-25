#include <iostream>

#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"
#include <stddef.h>


GLuint Program;
GLuint vao;
GLuint ubo;

void init()
{
	ShaderInfo shaders[] = { {GL_VERTEX_SHADER, "UniformBlock.vert"},{GL_FRAGMENT_SHADER, "UniformBlock.frag"}, {GL_NONE, NULL} };
	Program = LoadShaders(shaders);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint b, n[3]{ 0, 1, 2 };
	glGenBuffers(1, &b);
	glBindBuffer(GL_ARRAY_BUFFER, b);
	glBufferData(GL_ARRAY_BUFFER, sizeof(n), n, GL_STATIC_DRAW);

	GLint in = glGetAttribLocation(Program, "n");
	glEnableVertexAttribArray(in);
	glVertexAttribIPointer(in, 1, GL_UNSIGNED_INT, 0, BUFFER_OFFSET(0));
	
	GLint uboSize = 0;
	ubo = glGetUniformBlockIndex(Program, "Vertice");
	glGetActiveUniformBlockiv(Program, ubo, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);
	std::cout << "Bolck Index: " << ubo << '\n';
	std::cout << "Bolck Size: " << uboSize << '\n';

	const GLuint binding = 3;
	//glUniformBlockBinding(Program, ubo, binding);

	struct sDtata
	{
		GLfloat v[3][4];
		GLfloat color[4];
	}
	//uniform 数据
	Data = { {{-0.9f, -0.9f, 0.0f, 1.0f}, { 0.9f, -0.9f, 0.0f, 1.0f }, {0.0f, 0.9f, 0.0f, 1.0f }},
	           {0.2f, 0.7f, 1.0f, 1.0f} };

	//验证结构体sDtata，与uniform块格式是否一致。
	char *names[] = { "v", "color" };
	//char *names[] = { "Named.v", "Named.color" };
	GLuint Index[2];
	GLint offset[2];
	glGetUniformIndices(Program, 2, names, Index);
	glGetActiveUniformsiv(Program, 2, Index, GL_UNIFORM_OFFSET, offset);
	if (uboSize != sizeof(Data) 
		|| offsetof(sDtata,v) != offset[0] //offsetof可以返回结构中字段的字节偏移
		|| offsetof(sDtata, color) != offset[1])
	{
		std::cout << "Data Do not mutch.." << std::endl;
	}



	glGenBuffers(1, &b);
	glBindBuffer(GL_UNIFORM_BUFFER, b);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(Data), &Data, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, binding, b);

	glUseProgram(Program);
	glClearColor(0.5f, 0.0f, 0.2f, 1.0f);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glFlush();
	Sleep(30);
}



int main(int argc, char *arg[])
{
	glutInit(&argc, arg);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(arg[0]);

	if (glewInit())
	{
		std::cout << "Unable to initialize GLEW.." << std::endl;
		return 1;
	}

	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}




