

#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"

#include <iostream>
using namespace std;

GLuint program;
GLuint vao;
GLuint vbo;

GLfloat vert[] = { 
    0.0f, 0.9f, -0.9f,    -0.9f,-0.9f, -0.9f,     0.9f, -0.9f,-0.9f,    0.0f,0.0f, 0.9f,

    1.0, 0.0, 0.0,       0.0, 1.0, 0.0,        0.0, 0.0, 1.0,         0.0, 1.0, 1.0
};

GLuint Tfb;

GLuint vaos[2];
GLuint vbos[2];
GLuint program2;

void init()
{
	ShaderInfo si[] = {
		{ GL_VERTEX_SHADER, "TransformTriangle.v" },
		{ GL_GEOMETRY_SHADER, "TransformTriangle.geom" },
		{ GL_NONE, "" }
	};

	program = LoadShaders(si);

	char *Varying[] = {"lColor","lPos","gl_NextBuffer","rColor","rPos"};
	glTransformFeedbackVaryings(program, 5, Varying, GL_INTERLEAVED_ATTRIBS);
	glLinkProgram(program);

	ShaderInfo si2[] = {
		{ GL_VERTEX_SHADER, "TransformTriangle.v" },
		{ GL_FRAGMENT_SHADER, "TransformTriangle.g" },
		{ GL_NONE, "" }
	};
	program2 = LoadShaders(si2);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float) * 3 * 4));
    glEnableVertexAttribArray(1);

	glGenTransformFeedbacks(1, &Tfb);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, Tfb);
	glGenBuffers(2, vbos);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, vbos[0]);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(float) * 4*2 * 20, NULL, GL_DYNAMIC_COPY);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbos[0]);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, vbos[1]);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(float) * 4*2 * 20, NULL, GL_DYNAMIC_COPY);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, vbos[1]);


	glGenVertexArrays(2, vaos);
	glBindVertexArray(vaos[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(sizeof(float)* 4));//postion
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(0));//color
	glEnableVertexAttribArray(1);
	glBindVertexArray(vaos[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(sizeof(float) * 4));//postion
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);


    glClearColor(0.1, 0.1, 0.1, 1.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_POINT_SIZE);
    glPointSize(20);
    glUseProgram(program);

    static unsigned int Time = GetTickCount();

    vmath::mat4 modle = vmath::mat4::identity();
	vmath::mat4 d = vmath::mat4::identity();

    unsigned int timeNow = GetTickCount();
    float dt = float((timeNow - Time) % 8000) / 1000.0f;
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(1.0f, 0.0f, 0.0f));
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 0.0f, 1.0f));
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 1.0f, 0.0f));
    modle *= vmath::scale(0.3f, 0.3f, 0.3f);

    d = vmath::translate(-0.3f, 0.0f, 0.0f);
    modle = d * modle;
    d = vmath::translate(0.6f, 0.0f, 0.0f);

    glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, modle);
    glUniformMatrix4fv(glGetUniformLocation(program, "dMatrix"), 1, GL_FALSE, d);

	static bool IsQueen = true;
	GLuint q[2];

	glEnable(GL_RASTERIZER_DISCARD); //∆¡±Œπ‚’§ªØ
    glBindVertexArray(vao);
    glEnable(GL_DEPTH_TEST);
	if (IsQueen)
	{
		glGenQueries(2, q);
		glBeginQueryIndexed(GL_PRIMITIVES_GENERATED, 0, q[1]);
		glBeginQueryIndexed(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, 0, q[0]);
	}

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, Tfb);
	glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_LINES_ADJACENCY, 0, 4);
	glEndTransformFeedback();
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	glDisable(GL_RASTERIZER_DISCARD);

	if (IsQueen)
	{
		IsQueen = false;
		glEndQueryIndexed(GL_PRIMITIVES_GENERATED, 0);
		glEndQueryIndexed(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, 0);
		int n = -1;
		glGetQueryObjectiv(q[0], GL_QUERY_RESULT, &n);
		cout<< "Primitives Count: " << n << endl;
		glGetQueryObjectiv(q[1], GL_QUERY_RESULT, &n);
		cout << "Transform feedback Primitives Count: " << n << endl << endl;
		glDeleteQueries(2, q);
	}




	glUseProgram(program2);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(vaos[0]);
	//glDrawArrays(GL_POINTS, 1, 1);
	glDrawTransformFeedbackStream(GL_TRIANGLES, Tfb, 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(vaos[1]);
	glDrawTransformFeedbackStream(GL_TRIANGLES, Tfb, 1);

	static bool IsOutTb = true;
	if (IsOutTb)
	{
		IsOutTb = false;
		float tbV[24][4] = { 0.0f };
		glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, vbos[0]);
		glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(tbV), tbV);
		for (int i = 0; i < 24; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				cout << tbV[i][j] << "  ";
			}
			cout << endl;
		}
		cout << endl << endl;
		glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, vbos[1]);
		glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(tbV), tbV);
		for (int i = 0; i < 24; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				cout << tbV[i][j] << "  ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}


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









