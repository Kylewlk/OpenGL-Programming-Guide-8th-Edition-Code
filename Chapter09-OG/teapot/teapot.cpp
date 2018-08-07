
#include <iostream>

#include "vgl.h"
#include "mat.h"
#include "LoadShaders.h"
#include "Shapes/Teapot.h"

using namespace std;

GLuint  PLoc;  // Projection matrix
GLuint  InnerLoc;  // Inner tessellation paramter
GLuint  OuterLoc;  // Outer tessellation paramter

GLfloat  Inner = 1.0;
GLfloat  Outer = 1.0;

//----------------------------------------------------------------------------

void
init( void )
{
    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    enum { ArrayBuffer, ElementBuffer, NumVertexBuffers };
    GLuint buffers[NumVertexBuffers];
    glGenBuffers( NumVertexBuffers, buffers );
    glBindBuffer( GL_ARRAY_BUFFER, buffers[ArrayBuffer] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(TeapotVertices),
		  TeapotVertices, GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, buffers[ElementBuffer] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(TeapotIndices),
                  TeapotIndices, GL_STATIC_DRAW );

    // Load shaders and use the resulting shader program
    ShaderInfo  shaders[] = {
	{ GL_VERTEX_SHADER,          "teapot.vert" },
	{ GL_TESS_CONTROL_SHADER,    "teapot.cont" },
 	{ GL_TESS_EVALUATION_SHADER, "teapot.eval" },
 	{ GL_FRAGMENT_SHADER,        "teapot.frag" },
	{ GL_NONE, NULL }
    };

    GLuint program = LoadShaders( shaders );
    glUseProgram( program );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_DOUBLE, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );

    PLoc = glGetUniformLocation( program, "P" );
    InnerLoc = glGetUniformLocation( program, "Inner" );
    OuterLoc = glGetUniformLocation( program, "Outer" );

    glUniform1f( InnerLoc, Inner );
    glUniform1f( OuterLoc, Outer );
    
	mat4  modelview = Translate( -0.2625f, -1.575f, -1.0f );
	modelview *= Translate( 0.0f, 0.0f, -7.5f );
    glUniformMatrix4fv( glGetUniformLocation( program, "MV" ),
			1, GL_TRUE, modelview );

    glPatchParameteri( GL_PATCH_VERTICES, NumTeapotVerticesPerPatch );
    
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glDrawElements( GL_PATCHES, NumTeapotVertices,
		    GL_UNSIGNED_INT, BUFFER_OFFSET(0) );
    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
reshape( int width, int height )
{
    glViewport( 0, 0, width, height );

    GLfloat  aspect = GLfloat(width)/height;

    mat4  projection = Perspective( 60.0, aspect, 5, 10 );
//     mat4  projection = Frustum( -3, 3, -3, 3, 5, 10 );
    glUniformMatrix4fv( PLoc, 1, GL_TRUE, projection );
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
	case 'q': case 'Q': case 033 /* Escape key */:
	    exit( EXIT_SUCCESS );
	    break;

	case 'i': 
	    Inner--;
	    if ( Inner < 1.0 )  Inner = 1.0;
	    glUniform1f( InnerLoc, Inner );
	    break;

	case 'I':
	    Inner++;
	    if ( Inner > 64 )  Inner = 64.0;
	    glUniform1f( InnerLoc, Inner );
	    break;

	case 'o': 
	    Outer--;
	    if ( Outer < 1.0 )  Outer = 1.0;
	    glUniform1f( OuterLoc, Outer );
	    break;

	case 'O':
	    Outer++;
	    if ( Outer > 64 )  Outer = 64.0;
	    glUniform1f( OuterLoc, Outer );
	    break;

	case 'r':
	    Inner = 1.0;
	    Outer = 1.0;
	    glUniform1f( InnerLoc, Inner );
	    glUniform1f( OuterLoc, Outer );
	    break;

	case 'm': {
	    static GLenum mode = GL_FILL;
	    mode = ( mode == GL_FILL ? GL_LINE : GL_FILL );
	    glPolygonMode( GL_FRONT_AND_BACK, mode );
	} break;
    }

    glutPostRedisplay();
}

//----------------------------------------------------------------------------

int
main( int argc, char *argv[] )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize( 512, 512 );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow( "teapot" );

    glewInit();
    glGetError(); 

    init();

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
