//////////////////////////////////////////////////////////////////////////////
//
//  Gouraud.cpp
//
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

#include "vgl.h"
#include "LoadShaders.h"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0, vColor = 1 };

GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];

const GLuint  NumVertices = 6;

//----------------------------------------------------------------------------
//
// init
//

void
init( void )
{
    glGenVertexArrays( NumVAOs, VAOs );
    glBindVertexArray( VAOs[Triangles] );

    struct VertexData {
        GLubyte color[4];
        GLfloat position[4];
    };

    VertexData vertices[NumVertices] = {
        {{ 255,   0,   0, 255 }, { -0.90, -0.90 }},  // Triangle 1
        {{   0, 255,   0, 255 }, {  0.85, -0.90 }},
        {{   0,   0, 255, 255 }, { -0.90,  0.85 }},
        {{  10,  10,  10, 255 }, {  0.90, -0.85 }},  // Triangle 2
        {{ 100, 100, 100, 255 }, {  0.90,  0.90 }},
        {{ 255, 255, 255, 255 }, { -0.85,  0.90 }}
    };

    glGenBuffers( NumBuffers, Buffers );
    glBindBuffer( GL_ARRAY_BUFFER, Buffers[ArrayBuffer] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices),
                  vertices, GL_STATIC_DRAW );

    ShaderInfo  shaders[] = {
        { GL_VERTEX_SHADER, "gouraud.vert" },
        { GL_FRAGMENT_SHADER, "gouraud.frag" },
        { GL_NONE, NULL }
    };

    GLuint program = LoadShaders( shaders );
    glUseProgram( program );

    glVertexAttribPointer( vColor, 4, GL_UNSIGNED_BYTE,
                           GL_TRUE, sizeof(VertexData), BUFFER_OFFSET(0) );
    glVertexAttribPointer( vPosition, 2, GL_FLOAT,
                           GL_FALSE, sizeof(VertexData),
                           BUFFER_OFFSET(sizeof(vertices[0].color)) );

    glEnableVertexAttribArray( vColor );
    glEnableVertexAttribArray( vPosition );
}

//----------------------------------------------------------------------------
//
// keyboard 
//

void
keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
      case 033:  // ASCII Escape Key Code
        exit( EXIT_SUCCESS );
        break;

      case 'm': {
        static GLenum  mode = GL_FILL;

        mode = ( mode == GL_FILL ? GL_LINE : GL_FILL );
        glPolygonMode( GL_FRONT_AND_BACK, mode );
      } break;
    }

    glutPostRedisplay();
}

//----------------------------------------------------------------------------
//
// display
//

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );

    glBindVertexArray( VAOs[Triangles] );
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );

    glFlush();
}

//----------------------------------------------------------------------------
//
// main
//

int
main( int argc, char** argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA );
    glutInitWindowSize( 512, 512 );
    glutInitContextVersion( 4, 0 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow( argv[0] );

    if ( glewInit() ) {
        cerr << "Unable to initialize GLEW ... exiting" << endl;
        exit( EXIT_FAILURE );
    }

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
}
