#include <iostream>


#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"

using namespace std;


struct Vertex
{
    GLfloat position[3];
    GLfloat TexCoord[2];
};

Vertex Verts[] = {
{ {-0.8f,-0.8f,0.0f},{0.0f,0.0f}},
{ { 0.2f,-0.8f,0.0f },{ 1.0f,0.0f } },
{ { -0.8f,0.2f,0.0f },{ 0.0f,1.0f } },
{ { 0.2f,0.2f,0.0f },{ 1.0f,1.0f } }, };

GLuint Program = 0;

GLuint vert;
GLuint vbo;

GLuint tex;

GLuint texCopy;
GLuint vertCopy;
GLuint vboCopy;

Vertex VertsCopy[] = {
{ {0.22f,0.22f,0.0f},{0.0f,0.0f}},
{ { 0.8f,0.22f,0.0f },{ 1.0f,0.0f } },
{ { 0.22f,0.8f,0.0f },{ 0.0f,1.0f } },
{ { 0.8f,0.8f,0.0f },{ 1.0f,1.0f } }, };

void Init()
{
    ShaderInfo si[] = { { GL_VERTEX_SHADER, "Chpater06.vert" },{ GL_FRAGMENT_SHADER, "Chapter06.frag" },{ GL_NONE, NULL } };
    Program = LoadShaders(si);

    glGenVertexArrays(1, &vert);
    glBindVertexArray(vert);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(Verts->position)));
	glEnableVertexAttribArray(1);
    glBindVertexArray(0);

	glGenVertexArrays(1, &vertCopy);
	glBindVertexArray(vertCopy);
	glGenBuffers(1, &vboCopy);
	glBindBuffer(GL_ARRAY_BUFFER, vboCopy);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertsCopy), VertsCopy, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(Verts->position)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

    float texData[] = {1.0, 1.0, 0.0, 1.0,
                       1.0, 0.0, 1.0, 1.0,
                       0.0, 1.0, 1.0, 1.0,
                       0.0, 1.0 ,0.0, 1.0};
    GLuint PiexlUnpack;
    glGenBuffers(1, &PiexlUnpack);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, PiexlUnpack);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, sizeof(texData), texData, GL_STATIC_DRAW);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 2, 2);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 2, 2, GL_RGBA, GL_FLOAT, NULL);//使用GL_PIXEL_UNPACK_BUFFER设置纹理缓存

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
    glUseProgram(Program);
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vert);
	glUniform1i(0, 0);//设置纹理单元0为采样器中的值。

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);//绘制图形

	static bool IsCopytoTex = true;
	if (IsCopytoTex)
	{
		IsCopytoTex = false;
		glGenTextures(1, &texCopy);
		glActiveTexture(GL_TEXTURE1);//使用纹理单元1设置纹理
		glBindTexture(GL_TEXTURE_2D, texCopy);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 200, 200);
		glCopyTexSubImage2D(GL_TEXTURE_2D, 0,0, 0, 0, 0, 200, 200);//从当前帧缓存中拷贝纹理书籍
		//glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, 300, 300, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	}
	else
	{
		glBindVertexArray(vertCopy);
		glUniform1i(0, 1);//使用拷贝生成的纹理数据。

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
    glutSwapBuffers();

    glutPostRedisplay();
	Sleep(30);
}


int main(int argc, char*argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE | GLUT_STENCIL);
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



