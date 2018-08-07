
#include "vgl.h"
#include "mat.h"
#include "CheckError.h"
#include "LoadShaders.h"

GLuint  PLoc;  // Projection matrix

const GLfloat  zNear = 1.0;
const GLfloat  zFar  = 3.0;

const int  NumVertices = 4;  // vertices in our patch

//----------------------------------------------------------------------------

void
init( void )
{
    // Create a vertex array object
    enum { Patch, NumVAOs };
    GLuint VAOs[NumVAOs];
    glGenVertexArrays( NumVAOs, VAOs );
    glBindVertexArray( VAOs[Patch] );

    // Create and initialize a buffer object
    enum { Array, NumBuffers };
    GLuint buffers[NumBuffers];
    glGenBuffers( NumBuffers, buffers );
    glBindBuffer( GL_ARRAY_BUFFER, buffers[Array] );
    
    GLfloat vertices[NumVertices][2] = {
	{ -0.5, -0.5 },
	{  0.5, -0.5 },
	{  0.5,  0.5 },
	{ -0.5,  0.5 }
    };
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices),
		  vertices, GL_STATIC_DRAW );

    // Load shaders and use the resulting shader program
    ShaderInfo  shaders[] = {
	{ GL_VERTEX_SHADER,          "simple.vert" },
	{ GL_TESS_CONTROL_SHADER,    "simple.cont" },
 	{ GL_TESS_EVALUATION_SHADER, "simple.eval" },
 	{ GL_FRAGMENT_SHADER,        "simple.frag" },
	{ GL_NONE, NULL }
    };

    GLuint program = LoadShaders( shaders );
    glUseProgram( program );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 2, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );

    PLoc = glGetUniformLocation( program, "P" );
    
    mat4  modelview = Translate( 0.0, 0.0, -0.5*(zNear + zFar) ) * RotateX( -50.0 );
    //mat4 modelview = mat4(1.0);
    glUniformMatrix4fv( glGetUniformLocation( program, "MV" ),
			1, GL_TRUE, modelview );

    glPatchParameteri( GL_PATCH_VERTICES, 4 );

    glEnable( GL_DEPTH_TEST );

    glClearColor( 0.0, 0.0, 0.0, 1.0 );
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glDrawArrays( GL_PATCHES, 0, NumVertices );
    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
reshape( int width, int height )
{
    glViewport( 0, 0, width, height );

    GLfloat  aspect = GLfloat(width)/height;

    mat4  projection = Perspective( 60.0, aspect, zNear, zFar );
    glUniformMatrix4fv( PLoc, 1, GL_TRUE, projection );

    glutPostRedisplay();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
	case 'q': case 'Q': case 033 /* Escape key */:
	    exit( EXIT_SUCCESS );
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
    glutCreateWindow( "patch" );

    glewInit();

    init();

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
