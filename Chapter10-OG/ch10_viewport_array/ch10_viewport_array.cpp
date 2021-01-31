/* $URL$
   $Rev$
   $Author$
   $Date$
   $Id$
 */

#include "vapp.h"
#include "vutils.h"
#include "vbm.h"
#include "LoadShaders.h"
#include "vmath.h"

#include <stdio.h>

BEGIN_APP_DECLARATION(ViewportArrayApplication)
    // Override functions from base class
    virtual void Initialize(const char * title);
    virtual void Display(bool auto_redraw);
    virtual void Finalize(void);
    virtual void Reshape(int width, int height);

    // Member variables
    float aspect;
    GLuint prog;
    GLuint vao;
    GLuint vbo;
    VBObject object;

    int w, h;

    GLint model_matrix_pos;
    GLint projection_matrix_pos;
END_APP_DECLARATION()

DEFINE_APP(ViewportArrayApplication, "Viewport Array")

void ViewportArrayApplication::Initialize(const char * title)
{
    base::Initialize(title);


	ShaderInfo si[] = { { GL_VERTEX_SHADER,"viewport.vert" },{ GL_GEOMETRY_SHADER ,"viewport.geom" },{ GL_FRAGMENT_SHADER,"viewport.frag" },{GL_NONE, ""} };
    prog = LoadShaders(si);
    glUseProgram(prog);

    model_matrix_pos = glGetUniformLocation(prog, "model_matrix");
    projection_matrix_pos = glGetUniformLocation(prog, "projection_matrix");

    object.LoadFromVBM("../../media/ninja.vbm", 0, 1, 2);
}

void ViewportArrayApplication::Display(bool auto_redraw)
{
    float t = float(GetTickCount() & 0x3FFF) / float(0x3FFF);
    static const vmath::vec3 X(1.0f, 0.0f, 0.0f);
    static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
    static const vmath::vec3 Z(0.0f, 0.0f, 1.0f);

    glClearColor( 0.3f, 0.1f, 0.2f, 1.0f );
    glClearDepth( 1.0f );
    glDisable(GL_SCISSOR_TEST);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable(GL_SCISSOR_TEST);


    glUseProgram(prog);

    vmath::mat4 p(vmath::frustum(-1.0f, 1.0f, aspect, -aspect, 1.0f, 5000.0f));
    vmath::mat4 m[4];

    for (int i = 0; i < 4; i++)
    {
        m[i] = vmath::mat4(vmath::translate(0.0f, 0.0f, 100.0f * sinf(6.28318531f * t + i) - 230.0f) *
                           vmath::rotate(360.0f * t * float(i + 1), X) *
                           vmath::rotate(360.0f * t * float(i + 2), Y) *
                           vmath::rotate(360.0f * t * float(5 - i), Z) *
                           vmath::translate(0.0f, -80.0f, 0.0f));
    }

    glUniformMatrix4fv(model_matrix_pos, 4, GL_FALSE, m[0]);
    glUniformMatrix4fv(projection_matrix_pos, 1, GL_FALSE, p);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    object.Render();

    base::Display();
}

void ViewportArrayApplication::Finalize(void)
{
    glUseProgram(0);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(prog);
    glDeleteVertexArrays(1, &vao);
}

void ViewportArrayApplication::Reshape(int width, int height)
{
    const float wot = float(width) * 0.5f;
    const float hot = float(height) * 0.5f;

    glViewportIndexedf(0, 0.0f, 0.0f, wot, hot);
    glViewportIndexedf(1, wot, 0.0f, wot, hot);
    glViewportIndexedf(2, 0.0f, hot, wot, hot);
    glViewportIndexedf(3, wot, hot, wot, hot);
    w = width; h = height;
    glScissorIndexed(0, wot / 4.0, hot / 4.0, wot / 2.0, hot / 2.0);
    //glScissorIndexed(1, wot / 2.0 + wot, hot / 2.0, wot / 2.0, hot / 2.0);
    //glScissorIndexed(2, wot / 2.0, hot / 2.0+ hot, wot / 2.0, hot / 2.0);
    //glScissorIndexed(3, wot / 2.0+ wot, hot / 2.0+ hot, wot / 2.0, hot / 2.0);
    glEnable(GL_SCISSOR_TEST);

    aspect = hot / wot;
}
