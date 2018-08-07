#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
#include <iostream>
using namespace std;

float Vertices[] = {
    //top
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,

    //bottom
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    //front
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,

    //back
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    //left
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,

    //right
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    //ground
    -20.0f, -4.0f,  20.0f,
    20.0f, -4.0f,  20.0f,
    -20.0f, -4.0f, -20.0f,
    20.0f, -4.0f, -20.0f,
};

float vNormal[] = {
    //top
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,

    //bottom
    0.0f,  -1.0f,  0.0f,
    0.0f,  -1.0f,  0.0f,
    0.0f,  -1.0f,  0.0f,
    0.0f,  -1.0f,  0.0f,

    //front
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,

    //back
    0.0f,  0.0f,  -1.0f,
    0.0f,  0.0f,  -1.0f,
    0.0f,  0.0f,  -1.0f,
    0.0f,  0.0f,  -1.0f,

    //left
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,

    //right
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,

    //ground
    0.0f,  -1.0f,  0.0f,
    0.0f,  -1.0f,  0.0f,
    0.0f,  -1.0f,  0.0f,
    0.0f,  -1.0f,  0.0f,

};


float color[] = {

    //top
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,

    //bottom
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,

    //front
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,

    //back
    1.0f,  0.0f,  1.0f,
    1.0f,  0.0f,  1.0f,
    1.0f,  0.0f,  1.0f,
    1.0f,  0.0f,  1.0f,

    //left
    1.0f,  1.0f,  0.0f,
    1.0f,  1.0f,  0.0f,
    1.0f,  1.0f,  0.0f,
    1.0f,  1.0f,  0.0f,

    //right
    0.0f,  1.0f,  1.0f,
    0.0f,  1.0f,  1.0f,
    0.0f,  1.0f,  1.0f,
    0.0f,  1.0f,  1.0f,

    //ground
    //0.5f,  0.7f,  0.6f,
    //0.5f,  0.7f,  0.6f,
    //0.5f,  0.7f,  0.6f,
    //0.5f,  0.7f,  0.6f,
    0.5f,  1.0f,  0.6f, 
    0.5f,  1.0f,  0.6f,
    0.5f,  1.0f,  0.6f,
    0.5f,  1.0f,  0.6f,
};

GLuint Program_light;
GLuint Program;

GLuint verts;
GLuint vBo;
GLuint vCo;
GLuint vNo;

GLuint depth_tex;
const int DEPTH_TEX_SIZE = 1024;
GLuint DepthFrame;

float texVertCoord[][2] = { {-1.0f, -1.0f}, {-1.0f, 1.0f}, {1.0f, 1.0f }, {1.0f, -1.0f} };
float texCoord[][2] = { {0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f }, {1.0f, 0.0f} };
GLuint TexVert;
GLuint TexVBO;
GLuint TexVTO;

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
    ShaderInfo light_shaders[] =
    {
        { GL_VERTEX_SHADER, "Shadow_light.vert" },
        { GL_FRAGMENT_SHADER, "Shadow_light.frag" },
        { GL_NONE,"" }
    };
    Program_light = LoadShaders(light_shaders);

    ShaderInfo shaders[] =
    {
        { GL_VERTEX_SHADER, "test.vert" },
        { GL_FRAGMENT_SHADER, "test.frag" },
        { GL_NONE,"" }
    };
    Program = LoadShaders(shaders);

    glGenTextures(1, &depth_tex);
    glBindTexture(GL_TEXTURE_2D, depth_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, DEPTH_TEX_SIZE, DEPTH_TEX_SIZE, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//比较函数必须设为GL_NONE,否则无法读取深度值
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

	GLuint renderbuf;
	glGenRenderbuffers(1, &renderbuf);
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuf);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, DEPTH_TEX_SIZE, DEPTH_TEX_SIZE);

    glGenFramebuffers(1, &DepthFrame);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, DepthFrame);
    glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_tex, 0);
	glDrawBuffer(GL_NONE);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    glGenVertexArrays(1, &verts);
    glBindVertexArray(verts);
    glGenBuffers(1, &vBo);
    glBindBuffer(GL_ARRAY_BUFFER, vBo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &vCo);
    glBindBuffer(GL_ARRAY_BUFFER, vCo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &vNo);
    glBindBuffer(GL_ARRAY_BUFFER, vNo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vNormal), vNormal, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(2);

	glGenVertexArrays(1, &TexVert);
	glBindVertexArray(TexVert);
	glGenBuffers(1, &TexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, TexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texVertCoord), texVertCoord, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
	glGenBuffers(1, &TexVTO);
	glBindBuffer(GL_ARRAY_BUFFER, TexVTO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);


    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void display()
{
    static unsigned int Time = GetTickCount();

	vmath::mat4 modle = vmath::mat4::identity();
	vmath::mat4 ProjView = vmath::mat4::identity();

	vmath::mat4 view = vmath::translate(0.0f, 0.0f, -15.0f);
	vmath::mat4 Proj = vmath::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 2.0f, 50.0f);
	vmath::mat4 modleGround = modle*vmath::mat4::identity();
	unsigned int timeNow = GetTickCount();
	float dt = float((timeNow - Time) % 8000) / 1000.0f;
	vmath::mat4 modleCube = modle;
	modleCube *= vmath::rotate(45.0f*dt, vmath::vec3(1.0f, 0.0f, 0.0f));
	modleCube *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 1.0f, 0.0f));
	modleCube *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 0.0f, 1.0f));
	vmath::vec3 LightPosition(3.0f, 6.0f, 3.0f);

	ProjView = Proj * view;

	vmath::mat4 LightProjView;
	vmath::mat4 LightView = vmath::lookat(LightPosition, vmath::vec3(0.0f), vmath::vec3(0.0f, 1.0f, 0.0f));
	LightProjView = vmath::frustum(-0.8f, 0.8f, -0.8f, 0.8f, 2.0f, 200.0f)*LightView;
	vmath::mat4 ScalBias = vmath::translate(0.5f, 0.5f, 0.5f) * vmath::scale(0.5f, 0.5f, 0.5f);

	//////////////////////////////////////////////////////////////////////////
	glUseProgram(Program_light);
	glBindFramebuffer(GL_FRAMEBUFFER, DepthFrame);
	glViewport(0, 0, DEPTH_TEX_SIZE, DEPTH_TEX_SIZE);
	glClearDepth(1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(2, 3);

	glBindVertexArray(verts);
	glUniformMatrix4fv(glGetUniformLocation(Program_light, "matPorjectViewModle"), 1, GL_FALSE, LightProjView*modleGround);
	glDrawArrays(GL_TRIANGLE_STRIP, 6 * 4, 4);

	glUniformMatrix4fv(glGetUniformLocation(Program_light, "matPorjectViewModle"), 1, GL_FALSE, LightProjView*modleCube);
	for (int i = 0; i < 6; ++i)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
	}
	glDisable(GL_POLYGON_OFFSET_FILL);



    glBindBuffer(GL_READ_FRAMEBUFFER, DepthFrame);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glViewport(0, 0, 400, 400);

    //////////////////////******绘制Light视角下的纹理*******/////////////////////////////////
    //glBlitFramebuffer(0, 0, DEPTH_TEX_SIZE, DEPTH_TEX_SIZE, 0, 0, 400, 400, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, depth_tex);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glUseProgram(Program);
	glBindVertexArray(TexVert);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);



    glutSwapBuffers();
	Sleep(30);
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
    glutCreateWindow("Test chapter07");

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





