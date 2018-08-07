#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
#include "vbm.h"
#include <iostream>
using namespace std;

GLuint Program;
VBObject object;
VBObject object1;
VBObject object2;
VBObject object3;
VBObject object4;
VBObject object5;


GLint render_model_matrix_loc;


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


    object.LoadFromVBM("../../media/unit_torus.vbm", 0, 1, 2);//圆环
    object1.LoadFromVBM("../../media/unit_cone.vbm", 0, 1, 2);//圆锥
    object2.LoadFromVBM("../../media/unit_cube.vbm", 0, 1, 2);//正方体
    object3.LoadFromVBM("../../media/unit_cylinder.vbm", 0, 1, 2);//圆柱体
    object4.LoadFromVBM("../../media/unit_pipe.vbm", 0, 1, 2);//管道
    object5.LoadFromVBM("../../media/unit_sphere.vbm", 0, 1, 2);//球体


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

    modleTemp = vmath::translate(-0.4f, 0.6f, 0.0f) * vmath::scale(0.2f, 0.2f, 0.2f)* modle;
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, modleTemp);
    object.Render();

    modleTemp = vmath::translate(-0.4f, 0.0f, 0.0f) * vmath::scale(0.2f, 0.2f, 0.2f)* modle;
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, modleTemp);
    object1.Render();

    modleTemp = vmath::translate(-0.4f, -0.6f, 0.0f) * vmath::scale(0.3f, 0.3f, 0.3f)* modle;
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, modleTemp);
    object2.Render();

    modleTemp = vmath::translate(0.4f, 0.6f, 0.0f) * vmath::scale(0.2f, 0.2f, 0.2f)* modle;
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, modleTemp);
    object3.Render();

    modleTemp = vmath::translate(0.4f, 0.0f, 0.0f) * vmath::scale(0.2f, 0.2f, 0.2f)* modle;
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, modleTemp);
    object4.Render();

    modleTemp = vmath::translate(0.4f, -0.6f, 0.0f) * vmath::scale(0.25f, 0.25f, 0.25f)* modle;
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, modleTemp);
    object5.Render();



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





