#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
#include "vbm.h"
#include <iostream>
using namespace std;

GLuint Program;
VBObject objectLang;
VBObject objectRen;
VBObject objectTuzi;
VBObject objectYuan;
GLint render_model_matrix_loc;
GLint render_projection_matrix_loc;


GLuint ULocModel;
GLuint ULocPorjView;

void init()
{
    ShaderInfo shaders[] =
    {
        { GL_VERTEX_SHADER, "TestVBM.vert" },
        { GL_FRAGMENT_SHADER, "TestVBM.frag" },
        { GL_NONE,"" }
    };
    Program = LoadShaders(shaders);
    render_model_matrix_loc = glGetUniformLocation(Program, "model_matrix");
    render_projection_matrix_loc = glGetUniformLocation(Program, "projection_matrix");


    objectLang.LoadFromVBM("../../media/armadillo_low.vbm", 0, 1, 2);//ÀÇ
    objectRen.LoadFromVBM("../../media/ninja.vbm", 0, 1, 2);//ÈË
    objectTuzi.LoadFromVBM("../../media/bunny.vbm", 0, 1, 2);//ÍÃ×Ó
    objectYuan.LoadFromVBM("../../media/torus.vbm", 0, 1, 2);//Ô²»·

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

}

void display()
{
    static unsigned int Time = GetTickCount();

    vmath::mat4 modle = vmath::mat4::identity();

    unsigned int timeNow = GetTickCount();
    float dt = float((timeNow - Time) % 8000) / 1000.0f;
    //modle *= vmath::rotate(45.0f*dt, vmath::vec3(1.0f, 0.0f, 0.0f));
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 1.0f, 0.0f));
    //modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 0.0f, 1.0f));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glUseProgram(Program);

    vmath::mat4 modleTemp = vmath::translate(0.4f, 0.4f, 0.0f) * vmath::scale(0.004f, 0.004f, 0.004f) *modle;
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, modleTemp);
    objectLang.Render();

    modleTemp = vmath::translate(-0.4f, 0.2f, 0.0f) * vmath::scale(0.004f, 0.004f, 0.004f) *modle;
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, modleTemp);
    objectRen.Render();

    modleTemp = vmath::translate(-0.4f, -0.4f, 0.0f) * vmath::scale(4.0f, 4.0f, 4.0f) *modle;
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, modleTemp);
    objectTuzi.Render();

    modleTemp = vmath::translate(0.4f, -0.4f, 0.0f) * vmath::scale(0.01f, 0.01f, 0.01f) *vmath::rotate(45.0f*dt, vmath::vec3(1.0f, 0.0f, 0.0f))*modle;
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, modleTemp);
    objectYuan.Render();


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





