#include <iostream>


#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"

using namespace std;


struct Vertex
{
    GLfloat position[3];
    GLfloat TexCoord[2];
};

Vertex Verts[] = {
    { { -0.8f,-0.8f,0.0f },{ 0.0f,0.0f } },
    { { 0.8f,-0.8f,0.0f },{ 1.0f,0.0f } },
    { { -0.8f,0.8f,0.0f },{ 0.0f,1.0f } },
    { { 0.8f,0.8f,0.0f },{ 1.0f,1.0f } }, };

GLuint Program = 0;

GLuint vert;
GLuint vbo;

GLuint tex;

void Init()
{
    ShaderInfo si[] = { { GL_VERTEX_SHADER, "PointSprite.vert" },{ GL_FRAGMENT_SHADER, "PointSprite.frag" },{ GL_NONE, NULL } };
    Program = LoadShaders(si);

    glGenVertexArrays(1, &vert);
    glBindVertexArray(vert);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(Verts->position)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    float texData[] = { 1.0, 1.0, 0.0, 1.0,
        1.0, 0.0, 1.0, 1.0,
        0.0, 1.0, 1.0, 1.0,
        0.0, 1.0 ,0.0, 1.0 };
    GLuint PiexlUnpack;
    glGenBuffers(1, &PiexlUnpack);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, PiexlUnpack);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, sizeof(texData), texData, GL_STATIC_DRAW);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 2, 2);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 2, 2, GL_RGBA, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
    glUseProgram(Program);

}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vert);
    glUniform1i(0, 0);

    glPointSize(60);
    glDrawArrays(GL_POINTS, 0, 4);

    glutSwapBuffers();

    glutPostRedisplay();
	Sleep(30);
}


int main(int argc, char*argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE | GLUT_STENCIL);
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



