#include "vgl.h"
#include <vermilion.h>
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

GLuint ProgramObject;
VBObject objectRen;
GLuint tex;

GLint render_model_matrix_loc;


void init()
{
	ShaderInfo shaders[] =
	{
		{ GL_VERTEX_SHADER, "render.v" },
		{ GL_FRAGMENT_SHADER, "render.g" },
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
        { GL_FRAGMENT_SHADER, "LayerRender.frag" },
        { GL_NONE,"" }
    };
    ProgramObject = LoadShaders(shadersObejct);
    render_model_matrix_loc = glGetUniformLocation(ProgramObject, "model_matrix");


    objectRen.LoadFromVBM("../../media/ninja.vbm", 0, 1, 2);//ÈË


    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

}

void display()
{
    static unsigned int Time = GetTickCount();

    vmath::mat4 modle = vmath::mat4::identity();

    unsigned int timeNow = GetTickCount();
    float dt = float((timeNow - Time) % 8000) / 1000.0f;
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 1.0f, 0.0f));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glUseProgram(ProgramObject);

	vmath::mat4 modleTemp = vmath::translate(0.0f, -0.8f, 0.0f) * vmath::scale(0.008f, 0.008f, 0.008f) *modle;


    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, modleTemp);
    objectRen.Render();

	glUseProgram(Program);
	vmath::mat4 V = vmath::mat4::identity();
	glUniformMatrix4fv(glGetUniformLocation(Program, "VMatrix"), 1, GL_FALSE, V);

	glBindVertexArray(Va);
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





