#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
#include "vbm.h"
#include <iostream>
using namespace std;

GLuint Program;

float Verts[] = {
    -0.9, -0.9,   0.9, -0.9,    0.9, 0.9,    -0.9, 0.9 ,
    0.0, 0.0,     1.0, 0.0,     1.0, 1.0,     0.0, 1.0,

};

GLuint Va;
GLuint vbo;

GLuint buf;

void init()
{
    ShaderInfo shaders[] =
    {
        { GL_VERTEX_SHADER, "BufferObject.vert" },
        { GL_FRAGMENT_SHADER, "BufferObject.frag" },
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

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float) * 2 * 4));
    glEnableVertexAttribArray(3);

	glGenBuffers(1, &buf);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, buf);
	glBufferData(GL_SHADER_STORAGE_BUFFER, 8192, NULL, GL_DYNAMIC_COPY);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buf);


    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

}

void display()
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(Program);

    glBindVertexArray(Va);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


	static bool IsOutBuf = true;
	if (IsOutBuf)
	{
		IsOutBuf = false;
		float *fData = nullptr;
		int *count;
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, buf);
		count = (int*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_WRITE);
		fData = (float*)(count + 1);

		cout << "count: " << *count << endl;
		for (size_t i = 0; i < 4; i++)
		{
			cout << "Position: ";
			for (size_t j = 0; j < 4; j++)
			{
				cout << fData[i * 6 + j] << " ";
			}
			cout << endl;
			cout << "Tex: ";
			for (size_t j = 0; j < 2; j++)
			{
				cout << fData[i * 6 + 4 + j] << " ";
			}
			cout << endl;
		}

		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	}
	

	static int FrameCount = 0;

	if (FrameCount %100 == 1)
	{
		int *count;
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, buf);
		count = (int*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_WRITE);
		cout << "count: " << *count << endl;
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	}
	++FrameCount;
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
    glutCreateWindow("Test");

    if (glewInit() != 0)
    {
        cout << "Unable to initialize GLEW." << endl;
        return 0;
    }

    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}



