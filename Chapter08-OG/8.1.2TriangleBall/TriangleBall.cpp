#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
#include "vbm.h"
#include <iostream>
using namespace std;

GLuint Program;
VBObject object;

GLuint Panel[3];
GLuint BaseColor;
GLuint PatternColor;

GLint render_model_matrix_loc;

void init()
{
    ShaderInfo shaders[] =
    {
        { GL_VERTEX_SHADER, "TriangleBall.vert" },
        { GL_FRAGMENT_SHADER, "TriangleBall.frag" },
        { GL_NONE,"" }
    };
    Program = LoadShaders(shaders);

    render_model_matrix_loc = glGetUniformLocation(Program, "VMatrix");

    Panel[0] = glGetUniformLocation(Program, "Panel[0]");
    Panel[1] = glGetUniformLocation(Program, "Panel[1]");
    Panel[2] = glGetUniformLocation(Program, "Panel[2]");

    BaseColor = glGetUniformLocation(Program, "BaseColor");
    PatternColor = glGetUniformLocation(Program, "PatternColor");

    object.LoadFromVBM("../../media/unit_sphere.vbm", 0, 1, 2);


    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

}

void display()
{
    static unsigned int Time = GetTickCount();

    vmath::mat4 modle = vmath::mat4::identity(), modleTemp;

    unsigned int timeNow = GetTickCount();
    float dt = float((timeNow - Time) % 8000) / 1000.0f;
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(1.0f, 0.0f, 0.0f));
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 1.0f, 0.0f));
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 0.0f, 1.0f));



    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUseProgram(Program);

    glUniform4fv(Panel[0], 1, vmath::vec4( 2.0f, -1.0f, 0.0f, 0.6f));
    glUniform4fv(Panel[1], 1, vmath::vec4(-2.0f, -1.0f, 0.0f, 0.6f));
    glUniform4fv(Panel[2], 1, vmath::vec4(0.0f, 1.0f, 0.0f, 0.7f));

    glUniform4fv(BaseColor, 1, vmath::vec4(0.5f, 0.8f, 0.9f, 1.0f));
    glUniform4fv(PatternColor, 1, vmath::vec4(1.0f, 0.3f, 0.2f, 1.0f));

    modleTemp = vmath::scale(0.3f, 0.3f, 0.3f)* modle;
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, modleTemp);
    object.Render();


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



