#include <iostream>


#include "vgl.h"
#include "vermilion.h"

#include "LoadShaders.h"
#include "vmath.h"

using namespace std;


struct Vertex
{
	GLfloat position[3];
	GLfloat TexCoord[2];
};

Vertex Verts[] = {
	{ { -0.9f,0.9f,0.0f },{ 0.0f,1.0f } },
	{ { -0.9f,0.3f,0.0f },{ 0.0f,0.0f } },
	{ { -0.3f,0.9f,0.0f },{ 1.0f,1.0f } },
	{ { -0.3f,0.3f,0.0f },{ 1.0f,0.0f } }, 

	//{ { -0.3f,0.9f,0.0f },{ 0.0f,1.0f } },
	//{ { -0.3f,0.3f,0.0f },{ 0.0f,0.0f } },
	//{ { 0.3f,0.9f,0.0f },{ 1.0f,1.0f } },
	//{ { 0.3f,0.3f,0.0f },{ 1.0f,0.0f } },

	//{ { 0.3f,0.9f,0.0f },{ 0.0f,1.0f } },
	//{ { 0.3f,0.3f,0.0f },{ 0.0f,0.0f } },
	//{ { 0.9f,0.9f,0.0f },{ 1.0f,1.0f } },
	//{ { 0.9f,0.3f,0.0f },{ 1.0f,0.0f } },

	//{ { -0.9f,0.3f,0.0f },{ 0.0f,1.0f } },
	//{ { -0.9f,-0.3f,0.0f },{ 0.0f,0.0f } },
	//{ { -0.3f,0.3f,0.0f },{ 1.0f,1.0f } },
	//{ { -0.3f,-0.3f,0.0f },{ 1.0f,0.0f } },

	//{ { -0.3f,0.3f,0.0f },{ 0.0f,1.0f } },
	//{ { -0.3f,-0.3f,0.0f },{ 0.0f,0.0f } },
	//{ { 0.3f,0.3f,0.0f },{ 1.0f,1.0f } },
	//{ { 0.3f,-0.3f,0.0f },{ 1.0f,0.0f } },


	//{ { 0.3f,0.3f,0.0f },{ 0.0f,1.0f } },
	//{ { 0.3f,-0.3f,0.0f },{ 0.0f,0.0f } },
	//{ { 0.9f,0.3f,0.0f },{ 1.0f,1.0f } },
	//{ { 0.9f,-0.3f,0.0f },{ 1.0f,0.0f } },

	//{ { -0.9f,-0.3f,0.0f },{ 0.0f,1.0f } },
	//{ { -0.9f,-0.9f,0.0f },{ 0.0f,0.0f } },
	//{ { -0.3f,-0.3f,0.0f },{ 1.0f,1.0f } },
	//{ { -0.3f,-0.9f,0.0f },{ 1.0f,0.0f } },

	//{ { -0.3f,-0.3f,0.0f },{ 0.0f,1.0f } },
	//{ { -0.3f,-0.9f,0.0f },{ 0.0f,0.0f } },
	//{ { 0.3f,-0.3f,0.0f },{ 1.0f,1.0f } },
	//{ { 0.3f,-0.9f,0.0f },{ 1.0f,0.0f } },

	//{ { 0.3f,-0.3f,0.0f },{ 0.0f,1.0f } },
	//{ { 0.3f,-0.9f,0.0f },{ 0.0f,0.0f } },
	//{ { 0.9f,-0.3f,0.0f },{ 1.0f,1.0f } },
	//{ { 0.9f,-0.9f,0.0f },{ 1.0f,0.0f } },
};

GLuint Program = 0;

GLuint vert;
GLuint vbo;

GLuint tex;

GLuint texCube;
GLuint texPanel[6];

void Init()
{
	ShaderInfo si[] = { { GL_VERTEX_SHADER, "TextureView.vert" },{ GL_FRAGMENT_SHADER, "TextureView.frag" },{ GL_NONE, NULL } };
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


	float texData[] = { 1.0, 0.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 1.0,
		1.0, 1.0 ,0.0, 1.0 };
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexStorage2D(GL_TEXTURE_2D, 2, GL_RGBA8, 2, 2);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 2, 2, GL_RGBA, GL_FLOAT, texData);

	GLenum e;

	//glGenTextures(1, texPanel);
	//glTextureView(texPanel[0], GL_TEXTURE_2D, tex, GL_RGBA8, 0, 1, 0, 1);
	//e = glGetError();
	//glActiveTexture(GL_TEXTURE2);
	//glBindTexture(GL_TEXTURE_2D, texPanel[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glDeleteTextures(1, &tex);

	e = glGetError();
	vglImageData image;
	//texCube = vglLoadTexture("../../media/TantolundenCube.dds", 0, &image);
	texCube = vglLoadTexture("../../media/test.dds", 0, &image);
	e = glGetError();

	glGenTextures(6, texPanel);
	glTextureView(texPanel[0], GL_TEXTURE_2D, texCube, image.internalFormat, 0, image.mipLevels, 0, 1);
//	glTextureView(texPanel[0], GL_TEXTURE_2D, texCube, image.internalFormat, 0, image.mipLevels, 0, 1);
	e = glGetError();
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texPanel[0]);
	vglUnloadImage(&image);



	glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
	glUseProgram(Program);
	Sleep(30);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vert);

	vmath::mat4 ModelView = vmath::mat4::identity();


	//ModelView = vmath::scale(3.0f, 3.0f, 0.0f) * ModelView;

	for (int i = 0; i< 1; ++i)
	{
		for (int j = 0; j < 1; j++)
		{
			ModelView = vmath::translate(0.63f*i, -0.63f*j, 0.0f);
			glUniformMatrix4fv(1, 1, GL_FALSE, ModelView);
//			glActiveTexture(GL_TEXTURE2);
//			glBindTexture(GL_TEXTURE_2D, texPanel);
			glUniform1i(0, 2);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}
	}

	glutSwapBuffers();

	glutPostRedisplay();

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



