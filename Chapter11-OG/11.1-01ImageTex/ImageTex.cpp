

#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
#include "vbm.h"
#include <iostream>
using namespace std;

GLuint program;
GLuint vao;
GLuint vbo;
GLfloat vert[] = {  -1.0f, -1.0f,    1.0f,-1.0f,     1.0f, 1.0f,    -1.0f,1.0f, };

GLuint Prog_o;
VBObject obj;

const int WIDTH = 1024;
const int HEIGHT = 1024;
GLuint tex;
GLuint buffZero;



void init()
{
    ShaderInfo si[] = {
        { GL_VERTEX_SHADER, "show.vert" },
        { GL_FRAGMENT_SHADER, "show.frag" },
        { GL_NONE, "" }
    };
    program = LoadShaders(si);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);


    ShaderInfo obsi[] = {
        {GL_VERTEX_SHADER, "ImageTex.vert"},
        {GL_FRAGMENT_SHADER, "ImageTex.frag"},
        {GL_NONE, NULL}
    };
    Prog_o = LoadShaders(obsi);
    obj.LoadFromVBM("../../media/unit_sphere.vbm", 0, 1, 2);

    glGenBuffers(1, &buffZero);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffZero);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, WIDTH*HEIGHT * 4*sizeof(float), NULL, GL_STATIC_DRAW);
    void* p =glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
    memset(p, 0x00, WIDTH*HEIGHT * 4*sizeof(float));
    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);


    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    static unsigned int Time = GetTickCount();

    vmath::mat4 modle = vmath::mat4::identity();

    unsigned int timeNow = GetTickCount();
    float dt = float((timeNow - Time) % 8000) / 1000.0f;
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(1.0f, 0.0f, 0.0f));
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 0.0f, 1.0f));
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 1.0f, 0.0f));
    modle *= vmath::scale(0.3f, 0.3f, 0.3f);


	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffZero);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
	glBindImageTexture(1, tex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);


    glUseProgram(Prog_o);
    glUniformMatrix4fv(glGetUniformLocation(Prog_o, "modelMatrix"), 1, GL_FALSE, modle);
    obj.Render();

	//glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);//有些显卡上去掉此行代码，图像会有明显瑕疵。

	GLsync sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	glClientWaitSync(sync, GL_SYNC_FLUSH_COMMANDS_BIT, GL_MAX_SERVER_WAIT_TIMEOUT);

	glBindImageTexture(0, tex, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F);
	glUseProgram(program);
    glBindVertexArray(vao);
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
    glutInitWindowSize(600, 600);
    glutCreateWindow("Test OpenGL");

    if (glewInit() != 0)
    {
        cout << "Can not initialize GLEW" << endl;
        return 1;
    }

    init();
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}









