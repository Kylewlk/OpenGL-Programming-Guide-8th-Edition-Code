#include "vgl.h"
#include <vermilion.h>
#include "vmath.h"
#include "LoadShaders.h"
#include "vbm.h"
#include <iostream>
using namespace std;

GLuint Program;


float Verts[] = {
	-0.9f, -0.9f,   0.9f, -0.9f,    0.9f, 0.9f,    -0.9f, 0.9f,
	0.0f, 0.0f,     1.0f, 0.0f,     1.0f, 1.0f,     0.0f, 1.0f,

};

GLuint Va;
GLuint vbo;

GLuint ProgramObject;
VBObject objectRen;
GLuint tex;
GLuint FrameBuffer;
const GLuint Width = 500;
const GLuint Height = 500;

GLint render_model_matrix_loc;


void init()
{
	ShaderInfo shaders[] =
	{
		{ GL_VERTEX_SHADER, "render.vert" },
		{ GL_FRAGMENT_SHADER, "render.frag" },
		{ GL_NONE,"" }
	};
	Program = LoadShaders(shaders);

	glGenVertexArrays(1, &Va);
	glBindVertexArray(Va);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float) * 2 * 4));
	glEnableVertexAttribArray(1);




    ShaderInfo shadersObejct[] =
    {
        { GL_VERTEX_SHADER, "LayerRender.vert" },
		{ GL_GEOMETRY_SHADER, "LayerRender.geom" },
		{ GL_FRAGMENT_SHADER, "LayerRender.frag" },
        { GL_NONE,"" }
    };
    ProgramObject = LoadShaders(shadersObejct);
    render_model_matrix_loc = glGetUniformLocation(ProgramObject, "model_matrix");


    objectRen.LoadFromVBM("../../media/ninja.vbm", 0, 1, 2);//人


	//GLuint depthBuffer;
	//glGenRenderbuffers(1, &depthBuffer);
	//glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, Width, Height);

	//GLuint colorBuffer;
	//glGenRenderbuffers(1, &colorBuffer);
	//glBindRenderbuffer(GL_RENDERBUFFER, colorBuffer);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, Width, Height);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, Width, Height, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	GLuint depthTex;
	glGenTextures(1, &depthTex);
	glBindTexture(GL_TEXTURE_2D_ARRAY, depthTex);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT32, Width, Height, 2, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenFramebuffers(1, &FrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	//glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorBuffer);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTex, 0); //深度附件也需要分层
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex, 0);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void display()
{
    static unsigned int Time = GetTickCount();

    vmath::mat4 modle = vmath::mat4::identity();

    unsigned int timeNow = GetTickCount();
    float dt = float((timeNow - Time) % 8000) / 1000.0f;
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 1.0f, 0.0f));

	/***********开始生成分层纹理*************/
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FrameBuffer);
	glViewport(0, 0, Width, Height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glUseProgram(ProgramObject);
	vmath::mat4 modleTemp = vmath::translate(0.0f, -0.8f, 0.0f) * vmath::scale(0.008f, 0.008f, 0.008f) *modle;
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, modleTemp);
    objectRen.Render();

	//glBindFramebuffer(GL_READ_FRAMEBUFFER, FrameBuffer);//将帧缓存设置为读取缓存
	//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);//将绘制缓存设为窗口的帧缓存
	//glViewport(0, 0, 400, 400);
	//glBlitFramebuffer(0, 0, 300, 300, 0, 0, 400, 400, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	/**************开始绘制纹理******************/
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glViewport(0, 0, 400, 400);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(Program);
	vmath::mat4 V = vmath::mat4::identity();
	glBindVertexArray(Va);

	V = vmath::translate(-0.5f, 0.0f, 0.0f) * vmath::scale(0.5f, 0.5f, 0.5f);
	glUniformMatrix4fv(glGetUniformLocation(Program, "VMatrix"), 1, GL_FALSE, V);
	glUniform1i(0, 0);//绘制数组纹理中的第一层
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	V = vmath::translate(0.5f, 0.0f, 0.0f) * vmath::scale(0.5f, 0.5f, 0.5f);
	glUniformMatrix4fv(glGetUniformLocation(Program, "VMatrix"), 1, GL_FALSE, V);
	glUniform1i(0, 1);//绘制数组纹理中的第二层
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex);
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
    glutInitWindowSize(400, 400);
    glutCreateWindow("Test OpenGL");

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





