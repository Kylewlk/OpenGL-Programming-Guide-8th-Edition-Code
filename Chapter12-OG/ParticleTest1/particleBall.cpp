

#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
#include "vbm.h"
#include <iostream>
using namespace std;

GLuint program;
GLuint vao[2];
GLuint vbo[2];
GLuint tex[2];


const int GROUP_SIZE = 128;
const int GROUP_COUNT = 500;
const int PARTICLE_COUNT = GROUP_SIZE * GROUP_COUNT;

struct Particle
{
    vmath::vec2 Pos;
    vmath::vec2 Velocity;
    vmath::vec4 Color;
};

void init()
{
    ShaderInfo si[] = {
        { GL_VERTEX_SHADER, "particleBall.v" },
        { GL_FRAGMENT_SHADER, "particleBall.g" },
        { GL_NONE, "" }
    };
    program = LoadShaders(si);
    glGenVertexArrays(2, vao);
    glGenBuffers(2, vbo);
    glGenTextures(2, tex);

    for (int i = 0; i<2; ++i)//绘制时不允许改变绘制使用的缓存，不用计算着色器时需要两个纹理缓存，一个用于绘制，一个用来存储改变后的顶点数据。
    {
        glBindVertexArray(vao[i]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Particle)*PARTICLE_COUNT, NULL, GL_DYNAMIC_COPY);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(sizeof(vmath::vec4)));
        glEnableVertexAttribArray(1);


        glBindTexture(GL_TEXTURE_BUFFER, tex[i]);
        glTexParameteri(GL_TEXTURE_BUFFER, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_BUFFER, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, vbo[i]);


#define RandFloat() float(float((rand()%20000 - 10000) )/10000.0)
#define RandColor() float(float((rand()%10000))/10000.0)

        glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
        Particle *tempP = (Particle *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        for (int i = 0; i< PARTICLE_COUNT; ++i)
        {
            tempP[i].Pos = vmath::vec2(RandFloat() * 0.05, RandFloat()*0.05);
            tempP[i].Velocity = vmath::normalize(vmath::vec2( RandFloat(), RandFloat()));
            tempP[i].Color = vmath::vec4(RandColor(), RandColor(), RandColor(), 1.0f);
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }






    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    static unsigned int Time = GetTickCount();

    vmath::mat4 modle = vmath::mat4::identity();

    unsigned int timeNow = GetTickCount();
    float dt = float((timeNow - Time) & 0x3FF) / 1024.0f;
	Time = timeNow;

    static int FrameCount = 0;
    ++FrameCount;

    glUseProgram(program);
	glUniform1f(glGetUniformLocation(program, "dt"), dt);

    glEnable(GL_POINT_SIZE);
    glPointSize(2);

 	glBindImageTexture(0, tex[FrameCount % 2], 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
    glBindVertexArray(vao[(FrameCount-1) % 2]);
    glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

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
        cout << "Can not initilizate GLEW" << endl;
        return 1;
    }

    init();
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}









