#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
#include "Shapes/Teapot.h"
#include <iostream>
using namespace std;

GLuint Program;

GLuint vert;
GLuint vbo;



GLint render_model_matrix_loc;
GLint render_projection_matrix_loc;


void init()
{
    ShaderInfo shaders[] =
    {
        { GL_VERTEX_SHADER, "teapot.v" },
        { GL_FRAGMENT_SHADER, "teapot.g" },
        { GL_NONE,"" }
    };
    Program = LoadShaders(shaders);
    render_model_matrix_loc = glGetUniformLocation(Program, "model_matrix");
    render_projection_matrix_loc = glGetUniformLocation(Program, "projection_matrix");

    GLfloat noramls[NumTeapotVertices][3]{ 0.0 };

    vmath::vec3 v1, v2, n, t1, t2, t3;
    for (int i = 0; i < NumTeapotVertices/3; ++i)
    {   
        t1 = vmath::vec3(TeapotVertices[i][0], TeapotVertices[i][1], TeapotVertices[i][2]);
        t2 = vmath::vec3(TeapotVertices[i+1][0], TeapotVertices[i+1][1], TeapotVertices[i+1][2]);
        t3 = vmath::vec3(TeapotVertices[i+2][0], TeapotVertices[i+2][1], TeapotVertices[i+2][2]); 
        v1 = t1 - t3;
        v2 = t2 - t3;
        n = vmath::normalize(vmath::cross(v2, v1));

        noramls[i][0] = n[0]; noramls[i][1] = n[1]; noramls[i][2] = n[2];
        noramls[i+1][0] = n[0]; noramls[i+1][1] = n[1]; noramls[i+1][2] = n[2];
        noramls[i+2][0] = n[0]; noramls[i+2][1] = n[1]; noramls[i+2][2] = n[2];
    }

    glGenVertexArrays(1, &vert);
    glBindVertexArray(vert);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TeapotVertices) + sizeof(noramls), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(TeapotVertices), TeapotVertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(TeapotVertices), sizeof(noramls), noramls);

    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(TeapotVertices)));
    glEnableVertexAttribArray(1);


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

    vmath::mat4 modleTemp = vmath::translate(0.0f, 0.0f, 0.0f) * vmath::scale(0.2f, 0.2f, 0.2f) *modle;
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, modleTemp);

    glBindVertexArray(vert);
    glDrawArrays(GL_LINE_LOOP, 0, NumTeapotVertices);

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
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitContextVersion(4, 3);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Test teapot");

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





