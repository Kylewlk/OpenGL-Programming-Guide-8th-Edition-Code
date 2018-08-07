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

Vertex Verts[9] = { { { 255,0,0,255 },{ 0.0f, 0.9f, 0.0f } },
{ { 0,255,0,255 },{ -0.9f, -0.9f, 0.0f } },
{ { 0,0,255,255 },{ 0.9f, -0.9f, 0.0f } } ,
//三角形0不会被遮挡
{ { 255,255,255,255 },{ 0.0f, 0.8f, -0.2f } } ,
{ { 255,255,255,255 },{ -0.4f, 0.0f, -0.2f } } ,
{ { 255,255,255,255 },{ 0.4f, 0.0f, -0.2f } } ,
//三角形1被遮挡
{ { 255,255,255,255 },{ 0.0f, 0.0f, 0.2f } } ,
{ { 255,255,255,255 },{ -0.4f, -0.8f, 0.2f } } ,
{ { 255,255,255,255 },{ 0.4f, -0.8f, 0.2f } } };

GLuint Program = 0;

GLuint vert;
GLuint vbo;

void Init()
{
    ShaderInfo si[] = { { GL_VERTEX_SHADER, "Chpater04.vert" },{ GL_FRAGMENT_SHADER, "Chapter04.frag" },{ GL_NONE, NULL } };
    Program = LoadShaders(si);

    glGenVertexArrays(1, &vert);
    glBindVertexArray(vert);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(Verts->color)));
	glEnableVertexAttribArray(1);

    glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
    glUseProgram(Program);

    glEnable(GL_DEPTH_TEST);
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(vert);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    static bool isQuery = false;
    static GLint samples[2] = { 0 };
    if (!isQuery)
    {
		//查询三角形是否被遮挡
        GLuint QueryIDs[2];
        glGenQueries(2, QueryIDs);
        glBeginQuery(GL_SAMPLES_PASSED, QueryIDs[0]);
        glDrawArrays(GL_TRIANGLES, 3, 3);
        glEndQuery(GL_SAMPLES_PASSED);

        glBeginQuery(GL_SAMPLES_PASSED, QueryIDs[1]);
        glDrawArrays(GL_TRIANGLES, 6, 3);
        glEndQuery(GL_SAMPLES_PASSED);

        GLint QueryIsReady = GL_FALSE;
        for (int i = 0; i < 2; ++i)
        {
            while (!QueryIsReady)
            {
                glGetQueryObjectiv(QueryIDs[i], GL_QUERY_RESULT_AVAILABLE, &QueryIsReady);
            }

            if (QueryIsReady != GL_FALSE)
            {
                glGetQueryObjectiv(QueryIDs[i], GL_QUERY_RESULT, &samples[i]);
                cout << i << " Triangle: " << samples[i] << endl;
            }
            else
            {
                cout << i << " Triangle is not ready." << endl;
            }
        }
        glDeleteQueries(2, QueryIDs);
        isQuery = true;
    }
    if (samples[0] > 0)//值大于0则未被完全遮挡
    {
        glDrawArrays(GL_TRIANGLES, 3, 3);
    }
    if (samples[1] > 0)//值大于0则未被完全遮挡
    {
        glDrawArrays(GL_TRIANGLES, 6, 3);
    }

    glutSwapBuffers();
    glutPostRedisplay();
    Sleep(30);
}


int main(int argc, char*argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(400, 400);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("Test OpenGL Chapter 04");

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



