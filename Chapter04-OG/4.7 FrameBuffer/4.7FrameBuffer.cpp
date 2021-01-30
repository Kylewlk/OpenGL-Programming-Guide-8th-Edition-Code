#include <iostream>


#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"

using namespace std;


struct Vertex
{
    GLubyte color[4];
    GLfloat position[3];
};

Vertex Verts[9] = { { { 255,0,0,255 },{ 0.0f, 0.9f, 0.0f } },
{ { 0,255,0,255 },{ -0.9f, -0.9f, 0.0f } },
{ { 0,0,255,255 },{ 0.9f, -0.9f, 0.0f } } ,

{ { 255,255,255,255 },{ 0.0f, 0.8f, -0.2f } } ,
{ { 255,255,255,255 },{ -0.4f, 0.0f, -0.2f } } ,
{ { 255,255,255,255 },{ 0.4f, 0.0f, -0.2f } } ,

{ { 255,255,255,255 },{ 0.0f, 1.0f, 0.2f } } ,
{ { 255,255,255,255 },{ -0.4f, 0.2f, 0.2f } } ,
{ { 255,255,255,255 },{ 0.4f, 0.2f, 0.2f } } };

GLuint Program = 0;

GLuint vert;
GLuint vbo;

GLuint RendBuf[3], FrameBuf;


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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(Verts->color)));
	glEnableVertexAttribArray(1);

    glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
    glUseProgram(Program);

    glGenRenderbuffers(3, RendBuf);//������ɫ������һ����Ȼ���
    glBindRenderbuffer(GL_RENDERBUFFER, RendBuf[0]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, 200, 200);

    glBindRenderbuffer(GL_RENDERBUFFER, RendBuf[1]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 200, 200);

	glBindRenderbuffer(GL_RENDERBUFFER, RendBuf[2]);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, 200, 200);

    glGenFramebuffers(1, &FrameBuf);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FrameBuf);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, RendBuf[0]);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RendBuf[1]);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, RendBuf[2]);
}

void Display()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FrameBuf);//���Ƶ�֡����
    glViewport(0, 0, 200, 200);//�����ӿڴ�С��֡����һ��

	GLenum bufs[2] = { GL_COLOR_ATTACHMENT0 , GL_COLOR_ATTACHMENT1};//����ͬʱ���Ƶ�������ɫ����
	glDrawBuffers(2, bufs);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    float Color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, Color);//�ڶ�������0����ָGL_COLOR_ATTACHMENT0��ɫ�������䱳�����Ϊ��ɫ

    glBindVertexArray(vert);

    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 6);//��֡�����л���

	glBindFramebuffer(GL_READ_FRAMEBUFFER, FrameBuf);//��֡��������Ϊ��ȡ����
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);//�����ƻ�����Ϊ���ڵ�֡����
    glViewport(0, 0, 400, 400);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//��������
	glReadBuffer(GL_COLOR_ATTACHMENT0);//���ô�GL_COLOR_ATTACHMENT0��ȡ����
	glBlitFramebuffer(0, 0, 200, 200, 0, 0, 200, 200, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glReadBuffer(GL_COLOR_ATTACHMENT1);//���ô�GL_COLOR_ATTACHMENT1��ȡ����
	glBlitFramebuffer(0, 0, 200, 200, 200, 0, 400, 200, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	//�ڴ���֡����ֱ�ӻ���һ��������
	glDrawBuffer(GL_BACK);
    glDrawArrays(GL_TRIANGLES, 6, 3);

	//��ȡ���ز���
    static bool IsReadPixel = true;
    if (IsReadPixel)
    {
        IsReadPixel = false;
        GLuint Pixels[50][50]{ 0 };
        glReadBuffer(GL_COLOR_ATTACHMENT0);//���û����ȡ�ĸ���
        glReadPixels(150, 0, 50, 50, GL_RGBA, GL_UNSIGNED_BYTE, Pixels);//��ȡGL_READ_FRAMEBUFFER���أ����λ�ú�ɫ�Ƚ϶� ��ȡ�����ö� ff0000ff��ֵ
		int n = glGetError();
		//GL_INVALID_ENUM;
        for (int i = 0; i < 50; ++i)
        {
            for (int j = 0; j< 50; ++j)
            {
                cout << hex << Pixels[i][j] << "  ";
            }
            cout << endl;
        }
    }
    glutSwapBuffers();
    Sleep(30);
}


int main(int argc, char*argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH);
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



