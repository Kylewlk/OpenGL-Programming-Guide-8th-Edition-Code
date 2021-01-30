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

Vertex Verts[4] = { { { 255,0,0,255 },{ 0.5f, 0.5f, 0.0f } },
{ { 0,255,0,255 },{ -0.5f, 0.5f, 0.0f } },
{ { 0,0,255,255 },{ -0.5f, -0.5f, 0.0f } },
{ { 0,0,255,255 },{ 0.5f, -0.5f, 0.0f } } };

GLuint ProgramSquare = 0;

GLuint vaoLine;
GLuint vbo;
GLuint tb; //只做第一次绘制时输出使用

GLuint ProgramPoint = 0;

GLuint vaos[2];
GLuint tbPoint[2];

GLuint TransBack;

void Init()
{
	char *oVerts = "oPostion";
    ShaderInfo si[] = { { GL_VERTEX_SHADER, "Square.vert" },{ GL_FRAGMENT_SHADER, "Square.frag" },{ GL_NONE, NULL } };
    ProgramSquare = LoadShaders(si);
	glTransformFeedbackVaryings(ProgramSquare, 1, &oVerts, GL_INTERLEAVED_ATTRIBS);
	glLinkProgram(ProgramSquare);


    glGenVertexArrays(1, &vaoLine);
    glBindVertexArray(vaoLine);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(Verts->color)));
    glEnableVertexAttribArray(1);

	glGenBuffers(1, &tb);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, tb);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(float)*4*8, NULL, GL_DYNAMIC_COPY);


    ShaderInfo siPoint[] = { { GL_VERTEX_SHADER, "Point.vert" },{ GL_FRAGMENT_SHADER, "Point.frag" },{ GL_NONE, NULL } };
	ProgramPoint = LoadShaders(siPoint);
	glTransformFeedbackVaryings(ProgramPoint, 1, &oVerts, GL_INTERLEAVED_ATTRIBS);
	glLinkProgram(ProgramPoint);

	//glGenTransformFeedbacks(1, &TransBack);
	//glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, TransBack);

	float iPoint[8] = { 0.0, 0.9, 0.0, 1.0 , //前面四个值代表点的初始距离
		               -0.5, 0.5, -0.5, 0.5};//后面四个值店面矩形框的左右下上的位置
	glGenBuffers(1, &tbPoint[0]);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, tbPoint[0]);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(iPoint), iPoint, GL_DYNAMIC_COPY);

	glGenVertexArrays(1, &vaos[0]);
	glBindVertexArray(vaos[0]);
    glBindBuffer(GL_ARRAY_BUFFER, tbPoint[0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float)*4));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &tbPoint[1]);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, tbPoint[1]);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(iPoint), iPoint, GL_DYNAMIC_COPY);

	glGenVertexArrays(1, &vaos[1]);
	glBindVertexArray(vaos[1]);
	glBindBuffer(GL_ARRAY_BUFFER, tbPoint[1]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float) * 4));
	glEnableVertexAttribArray(1);


    glClearColor(0.2f, 0.1f, 0.3f, 1.0f);

}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);

	static float RectColor[4] = { 0.0, 0.0, 1.0, 1.0 };

    glUseProgram(ProgramSquare);
    GLuint color = glGetUniformLocation(ProgramSquare, "color");
    glUniform4fv(color, 1, RectColor);


	glBindVertexArray(vaoLine);
    glLineWidth(5.0f);
	glDrawArrays(GL_LINE_LOOP, 0, 4);//会绘制四根线最终有八个点

	static bool IsOutTb = true;
	if (IsOutTb)
	{
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tb);//使用默认的Transform feedback对象

		glBeginTransformFeedback(GL_LINES);
		glDrawArrays(GL_LINE_LOOP, 0, 4);//会绘制四根线最终有八个点
		glEndTransformFeedback();

		IsOutTb = false;
		float tbV[8][4] = { 0.0f };//读取矩形框四根线八个点的位置信息。
		//glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, tb);
		glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(tbV), tbV);
		for (int i = 0; i<8; ++i)
		{
			for (int j = 0; j<4; ++j)
			{
				cout << tbV[i][j] << "  ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}

	float t = float(GetTickCount() & 0x3FFFF);
	static float q = t;
	static unsigned int  FrameCount = 0;
	++FrameCount;
	glUseProgram(ProgramPoint);
	glUniform1f(0, (t - q)/1000.0f);
	q = t;

	if ((FrameCount % 2)  == 0)
	{
		glBindVertexArray(vaos[0]);// 使用tbPoint[0]进行绘制，使用tbPoint[1]存储TransfromFeedback数据
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbPoint[1]);
	}
	else
	{
		glBindVertexArray(vaos[1]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbPoint[0]);
	}
	glPointSize(10.0f);

	glBeginTransformFeedback(GL_POINTS);
	glDrawArrays(GL_POINTS, 0, 1);
	glEndTransformFeedback();

	float tbV[4] = { 0.0f };
	glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(tbV), tbV);//获取最新点的位置

	if (tbV[1] > -0.5 && tbV[1] < 0.5)//t[1]为点Y轴的位置，根据点的位置改变矩形框的颜色
	{
		RectColor[0] = 1.0;
		RectColor[1] = 0.0;
	}
	else
	{
		RectColor[0] = 0.0;
		RectColor[1] = 1.0;
	}

    glutSwapBuffers();
    glutPostRedisplay();
    Sleep(20);
}


int main(int argc, char*argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE | GLUT_STENCIL);
    glutInitWindowSize(400, 400);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("Test OpenGL");

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

