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

Vertex Verts[3] = { { { 255,0,0,255 },{ 0.0f, 0.9f } },
					{ { 0,255,0,255 },{ -0.9f, -0.9f } },
					{ { 0,0,255,255 },{ 0.9f, -0.9f } } };

float VertsNone[3][2] = { { 0.0f, 0.4f  },
                          { -0.4f, -0.4f } ,
                          { 0.4f, -0.4f  }};

GLuint Program = 0;

GLuint vert;
GLuint vbo;

GLuint vertNone;
GLuint vboNone;

void Init()
{
	ShaderInfo si[] = { { GL_VERTEX_SHADER, "Chpater04.vert" },{ GL_FRAGMENT_SHADER, "Chapter04.frag" },{ GL_NONE, NULL } };
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



	glGenVertexArrays(1, &vertNone);
	glBindVertexArray(vertNone);
    glGenBuffers(1, &vboNone);
    glBindBuffer(GL_ARRAY_BUFFER, vboNone);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertsNone), VertsNone, GL_STATIC_DRAW);
    glDisableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(1);


	glUseProgram(Program);

	glClearColor(0.2, 0.1, 0.3, 1.0);//���ñ�����ɫ
    glClearStencil(0x0);//����ģ���ʼֵ
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);//���Ʊ�����ɫ������ģ��ֵ�����Ϊ 0x0
	//glEnable(GL_SCISSOR_TEST);
	//glScissor(0, 0, 300, 300);
    glEnable(GL_STENCIL_TEST);

	//�����ο�����
	glBindVertexArray(vertNone);
	//����ģ���������ͨ��
    glStencilFunc(GL_ALWAYS, 0x1, 0x1);
	//����ģ��ֵ�����滻Ϊ 0x1
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	//��ֹ������ɫ���Ӷ�������Ƴ�ͼ�Σ�ֻ�����ģ��ֵ
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDrawArrays(GL_TRIANGLES, 0, 3);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    //glClear(GL_COLOR_BUFFER_BIT);

	//���Ʋ�ɫ������
	glBindVertexArray(vert);
	//����ģ��ֵ������ 0x1ʱ��ͨ��ģ����ԣ������ο����������������ز���ͨ��ģ�����
    glStencilFunc(GL_NOTEQUAL, 0x1, 0x1);
	//����ģ��ֵ������
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glDrawArrays(GL_TRIANGLES, 0, 3);


	glutSwapBuffers();
	glutPostRedisplay();
	Sleep(30);
}


int main(int argc, char*argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_STENCIL );
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



