#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
#include "vbm.h"
#include <iostream>
using namespace std;

int Width = 400, Height = 400;

GLuint Program;


VBObject object;

GLint render_model_matrix_loc;
GLint view_matrix_loc;

GLuint CreateShader(GLenum Type, const char* sorce)
{
	GLuint shader;
	shader = glCreateShader(Type);

	glShaderSource(shader, 1, &sorce, NULL);
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (0 == status)
	{
		char log[1000] = { 0 };
		GLint len = 0;
		glGetShaderInfoLog(shader, sizeof(log), &len, log);
		cout << Type << ": " << log << endl;
		return -1;
	}
	return shader;
}

GLuint ULocModel;
GLuint ULocPorjView;

void init()
{
	ShaderInfo shader[] =
	{
		{ GL_VERTEX_SHADER, "FourViewport.vert" },
		{GL_GEOMETRY_SHADER, "FourViewport.geom"},
		{ GL_FRAGMENT_SHADER, "FourViewport.frag" },
		{ GL_NONE, NULL }
	};

	Program = LoadShaders(shader);

	render_model_matrix_loc = glGetUniformLocation(Program, "model_matrix");
	view_matrix_loc = glGetUniformLocation(Program, "Vmatrix");

	object.LoadFromVBM("../../media/armadillo_low.vbm", 0, 1, 2);



	glClearColor(0.1, 0.1, 0.1, 1.0);
}

void display()
{
	float vw = Width / 2.0;
	float vh = Height / 2.0;
	glViewportIndexedf(0, 0, 0, vw, vh);
	glViewportIndexedf(1, vw, 0, vw, vh);
	glViewportIndexedf(2, 0, vh, vw, vh);
	glViewportIndexedf(3, vw, vh, vw, vh);

	static unsigned int Time = GetTickCount();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vmath::mat4 modle = vmath::mat4::identity();
	vmath::mat4 ProjView = vmath::mat4::identity();

	modle *= vmath::scale(0.008f, 0.008f, 0.008f);

	//modle *= vmath::scale(4.009f, 4.009f, 4.009f);

	unsigned int timeNow = GetTickCount();
	float dt = float((timeNow - Time) % 8000) / 1000.0f;
	//modle *= vmath::rotate(45.0f*dt, vmath::vec3(1.0f, 0.0f, 0.0f));
	modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 1.0f, 0.0f));
	//modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 0.0f, 1.0f));

	vmath::mat4 View[4];
	View[0] = vmath::mat4::identity();
	View[1] = vmath::scale(1.0f, 1.0f, -1.0f);
	View[2] = vmath::lookat(vmath::vec3(0.0f), vmath::vec3(0.0f, 1.0f, 0.0f), vmath::vec3(0.0f, 0.0f, 1.0f));
	View[3] = vmath::lookat(vmath::vec3(0.0f), vmath::vec3(0.0f, -1.0f, 0.0f), vmath::vec3(0.0f, 0.0f, -1.0f));

	glUseProgram(Program);
	glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, modle);
	
	glUniformMatrix4fv(view_matrix_loc, 4, GL_FALSE, View[0]);


	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	object.Render();

	glutSwapBuffers();
	glutPostRedisplay();
	Sleep(30);
}




int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextVersion(4, 3);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Test OpenGL");

	if (glewInit() != 0)
	{
		cout << "Unable to initilizate GLEW." << endl;
		return 0;
	}

	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}





