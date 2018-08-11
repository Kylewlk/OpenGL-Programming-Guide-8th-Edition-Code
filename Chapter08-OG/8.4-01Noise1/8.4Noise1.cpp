#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
#include "vbm.h"
#include <iostream>
using namespace std;

GLuint Program;

float Verts[400] = {0.0};
//float Verts[] = { 0.0, 0.0,   0.9, 0.0,    0.9, 0.9,    0.0, 0.9 };

GLuint Va;
GLuint vbo;


/////

float Noise1(int x)//����һ��[-1.0, 1.0]�����ڵ������
{
	x = (x << 13) ^ x;
	return (1.0 - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / (float(0x7fffffff)/2)/*1073741824.0*/);
}

float SmoothedNoise_1(int x) // ƽ���������ʹ�����������仯̫��
{
	return Noise1(x) / 2 + Noise1(x - 1) / 4 + Noise1(x + 1) / 4;
}

float InterpolatedNoise_1(float x)// �������ֵ�����Ǻ�����ֵ����ʹ�����������
{

	int integer_X = int(x);//��������
	float fractional_X = x - integer_X;//С������
	float v1 = SmoothedNoise_1(integer_X);
	float v2 = SmoothedNoise_1(integer_X + 1);

	float	ft = fractional_X * 3.141592f;
	float f = (1 + cos(ft)) * 0.5f;
	return v2*(1 - f) + v1*f;//��ֵ
}

float persistence = 1.0f / 1.20f;
int Number_Of_Octaves = 4;

float PerlinNoise_1D(float x) //����ͬƵ�ʵ���������
{
	float total = 0;
	float p = persistence;
	int n = Number_Of_Octaves;
	float frequency = 1.0f;
	float amplitude = 1.0f;
	for (int i = 1; i <= n; i++)
	{
		frequency *= 2.0;
		amplitude *= p; // Ƶ��Խ�ߵ��������ԽС
		total = total + InterpolatedNoise_1(x * frequency) * amplitude;
	}
	return total;
}


void init()
{
	ShaderInfo shaders[] =
	{
		{ GL_VERTEX_SHADER, "8.4Noise1.v" },
		{ GL_FRAGMENT_SHADER, "8.4Noise1.g" },
		{ GL_NONE,"" }
	};
	Program = LoadShaders(shaders);

	glGenVertexArrays(1, &Va);
	glBindVertexArray(Va);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), NULL, GL_DYNAMIC_COPY);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(Program);


	static unsigned int Time = GetTickCount();
	unsigned int timeNow = GetTickCount();
	float dt = float((timeNow - Time)) / 10000.0f;
	glUniform1f(glGetUniformLocation(Program, "dt"), dt);


	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);


	glBindVertexArray(Va);
	float ft = 0.0;
	float n = 0.0;
	for (int i = 0; i < 200; i++)
	{
		Verts[i * 2] = i*1.8 / 200.0f - 0.9f;

		ft = PerlinNoise_1D(i * 2 / 200.0f + dt);
		n = PerlinNoise_1D(i * 4 / 200.0f);
		Verts[i * 2 + 1] = ( n * 0.5f + ft * 0.5f);
	}
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Verts), Verts);

	glDrawArrays(GL_LINE_STRIP, 0, 200);

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
	glutCreateWindow("Test VBM");

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



