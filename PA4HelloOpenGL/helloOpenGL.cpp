//
//  helloOpenGL
//
//  Main program for the "Hello, OpenGL" assignment.
//
// This code can be compiled as either C or C++.
//
//  Students should not be modifying this file.
//

#ifdef __cplusplus
#include <cstdlib>
#include <iostream>
#else
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#endif

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#else
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#endif

#include "shaderSetup.h"

#ifdef __cplusplus
using namespace std;
#endif

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// buffer information
bool bufferInit = false;
GLuint buffer1, buffer2, ebuffer;
GLuint program;

// geometry data
float datapoints[] = {
     0.25, -0.75, 0.0, 1.0,   0.50, -0.75, 0.0, 1.0,   0.25,  0.15, 0.0, 1.0,
     0.50, -0.75, 0.0, 1.0,   0.50,  0.15, 0.0, 1.0,   0.25,  0.15, 0.0, 1.0,
     0.25,  0.25, 0.0, 1.0,   0.50,  0.25, 0.0, 1.0,   0.25,  0.50, 0.0, 1.0,
     0.50,  0.25, 0.0, 1.0,   0.50,  0.50, 0.0, 1.0,   0.25,  0.50, 0.0, 1.0,
    -0.25, -0.75, 0.0, 1.0,   0.00, -0.75, 0.0, 1.0,  -0.25,  0.75, 0.0, 1.0,
     0.00, -0.75, 0.0, 1.0,   0.00,  0.75, 0.0, 1.0,  -0.25,  0.75, 0.0, 1.0,
    -0.75, -0.75, 0.0, 1.0,  -0.50, -0.75, 0.0, 1.0,  -0.75,  0.75, 0.0, 1.0,
    -0.50, -0.75, 0.0, 1.0,  -0.50,  0.75, 0.0, 1.0,  -0.75,  0.75, 0.0, 1.0,
    -0.50, -0.12, 0.0, 1.0,  -0.25, -0.12, 0.0, 1.0,  -0.50,  0.12, 0.0, 1.0,
    -0.25, -0.12, 0.0, 1.0,  -0.25,  0.12, 0.0, 1.0,  -0.50,  0.12, 0.0, 1.0,
};
int dataSize = sizeof(datapoints);

GLushort elements[] = {
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
     15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29
};
int elemSize = sizeof(elements);

GLfloat colors1[] = {
    0.00, 1.00, 0.00, 1.0,   0.00, 1.00, 0.00, 1.0,   0.00, 0.28, 0.72, 1.0,
    0.00, 1.00, 0.00, 1.0,   0.00, 0.28, 0.72, 1.0,   0.00, 0.28, 0.72, 1.0,
    0.00, 0.20, 0.80, 1.0,   0.00, 0.20, 0.80, 1.0,   0.00, 0.00, 1.00, 1.0,
    0.00, 0.20, 0.80, 1.0,   0.00, 0.00, 1.00, 1.0,   0.00, 0.00, 1.00, 1.0,
    1.00, 0.00, 0.00, 1.0,   1.00, 0.00, 0.00, 1.0,   1.00, 0.00, 0.00, 1.0,
    1.00, 0.00, 0.00, 1.0,   1.00, 0.00, 0.00, 1.0,   1.00, 0.00, 0.00, 1.0,
    1.00, 1.00, 0.00, 1.0,   1.00, 1.00, 0.00, 1.0,   1.00, 1.00, 0.00, 1.0,
    1.00, 1.00, 0.00, 1.0,   1.00, 1.00, 0.00, 1.0,   1.00, 1.00, 0.00, 1.0,
    1.00, 1.00, 0.00, 1.0,   1.00, 0.00, 0.00, 1.0,   1.00, 1.00, 0.00, 1.0,
    1.00, 0.00, 0.00, 1.0,   1.00, 0.00, 0.00, 1.0,   1.00, 1.00, 0.00, 1.0,
};
int colorSize1 = sizeof(colors1);

GLfloat colors2[] = {
    1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,
    1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,
    1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,
    1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,
    1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,
    1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,
    1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,
    1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,
    1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,
    1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,   1.00, 1.00, 1.00, 1.0,
};
int colorSize2 = sizeof(colors2);

int nverts = 30;

int counter = 0;

///
// create a buffer
///
GLuint makeBuffer( GLenum target, const void *data, GLsizei size )
{
    GLuint buffer;

    glGenBuffers( 1, &buffer );
    glBindBuffer( target, buffer );
    glBufferData( target, size, data, GL_STATIC_DRAW );

    return( buffer );
}


///
// create the shapes we'll display
///
void createShapes()
{

    // setup vertex buffer #1
    buffer1 = makeBuffer( GL_ARRAY_BUFFER, NULL, dataSize + colorSize1 );

    glBufferSubData( GL_ARRAY_BUFFER, 0, dataSize, datapoints );
    glBufferSubData( GL_ARRAY_BUFFER, dataSize, colorSize1, colors1 );

    // setup vertex buffer #2
    buffer2 = makeBuffer( GL_ARRAY_BUFFER, NULL, dataSize + colorSize2 );

    glBufferSubData( GL_ARRAY_BUFFER, 0, dataSize, datapoints );
    glBufferSubData( GL_ARRAY_BUFFER, dataSize, colorSize2, colors2 );

    // setup the element buffer
    ebuffer = makeBuffer( GL_ELEMENT_ARRAY_BUFFER, elements, elemSize );

    // note that the buffers have all been created
    bufferInit = true;

}


// OpenGL initialization
void init()
{

    // Load shaders and use the resulting shader program
    program = shaderSetup( "shader.vert", "shader.frag" );
    if (!program) {
#ifdef __cplusplus
        cerr << "Error setting up shaders - "
            << errorString(shaderErrorCode) << endl;
#else
        fprintf( stderr, "Error setting up shaders - %s\n",
            errorString(shaderErrorCode) );
#endif
        exit(1);
    }

    glEnable( GL_DEPTH_TEST );
    glEnable(GL_CULL_FACE);
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glCullFace(GL_BACK);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // set up the initial scene
    createShapes();
}

#ifdef __cplusplus
extern "C" {
#endif


void display( void )
{
    // clear your frame buffers
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // bind the vertex and element buffers
    if( (counter & 1) == 0 ) {
        glBindBuffer( GL_ARRAY_BUFFER, buffer1 );
    } else {
        glBindBuffer( GL_ARRAY_BUFFER, buffer2 );
    }
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer );

    // set up your attribute variables
    glUseProgram( program );
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(0) );

    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(sizeof(datapoints)) );

    // draw your shape
    glDrawElements( GL_TRIANGLES, nverts, GL_UNSIGNED_SHORT, (void *)0 );

    // swap the buffers
    glutSwapBuffers();
}


void keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
        case '1':
            counter = 0;
            break;

        case '2':
            counter = 1;
            break;

        case 033:  // Escape key
        case 'q': case 'Q':
            exit( 0 );
            break;
    }

    glutPostRedisplay();
}

void mouse( int button, int state, int x, int y )
{
    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
        counter++;
        glutPostRedisplay();
    }

}

#ifdef __cplusplus
}
#endif

int main (int argc, char **argv)
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "Hello, OpenGL!" );

#ifndef __APPLE__
    GLenum err = glewInit();
    if( err != GLEW_OK ) {
#ifdef __cplusplus
        cerr << "Error: " << glewGetErrorString(err) << endl;
#else
        fprintf( stderr, "Error: %s\n", glewGetErrorString(err) );
#endif
	exit( 1 );
    }
    if( !GLEW_VERSION_3_2 ) {
#ifdef __cplusplus
        cerr << "Error: need OpenGL 3.2 or better" << endl;
#else
        fprintf( stderr, "Error: need OpenGL 3.2 or better\n" );
#endif
	exit( 1 );
    }
#endif

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutMouseFunc( mouse );

    glutMainLoop();
    return 0;
}

