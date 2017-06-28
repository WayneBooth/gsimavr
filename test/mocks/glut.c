#include <GL/glut.h>
#include "../../src/logger.h"


void glutInit( int* pargc, char** argv ) {
  LOG( LOGGER_WARNING, "Simulating 'glutInit'\n" );
}

void glutInitWindowPosition( int x, int y ) {
  LOG( LOGGER_WARNING, "Simulating 'glutInitWindowPosition'\n" );
}

void glutInitWindowSize( int x, int y ) {
  LOG( LOGGER_WARNING, "Simulating 'glutInitWindowSize'\n" );
}

int glutCreateWindow( const char* title ) {
  LOG( LOGGER_WARNING, "Simulating 'glutCreateWindow'\n" );
  return 1;
}

void glBegin( GLenum mode ) {
  LOG( LOGGER_WARNING, "Simulating 'glBegin'\n" );
}

void glEnd() {
  LOG( LOGGER_WARNING, "Simulating 'glEnd'\n" );
}

void glVertex2f( float x, float y ) {
  LOG( LOGGER_WARNING, "Simulating 'glVertex2f'\n" );
}

void glColor3f( float r, float g, float b ) {
  LOG( LOGGER_WARNING, "Simulating 'glColor3f'\n" );
}

void glPushMatrix() {
  LOG( LOGGER_WARNING, "Simulating 'glPushMatrix'\n" );
}

void glTranslatef( float x, float y, float z ) {
  LOG( LOGGER_WARNING, "Simulating 'glTranslatef'\n" );
}

void glScalef( float x, float y, float z) {
  LOG( LOGGER_WARNING, "Simulating 'glScalef'\n" );
}

void glutStrokeCharacter( void* font, int character ) {
  LOG( LOGGER_WARNING, "Simulating 'glutStrokeCharacter'\n" );
}

void glPopMatrix() {
  LOG( LOGGER_WARNING, "Simulating 'glPopMatrix'\n" );
}

void glLineWidth( float w ) {
  LOG( LOGGER_WARNING, "Simulating 'glLineWidth'\n" );
}

void test_font() {
  LOG( LOGGER_WARNING, "Simulating 'test_font'\n" );
}

void *glutStrokeMonoRoman=(void *)test_font;

void glClearColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha ) {
  LOG( LOGGER_WARNING, "Simulating 'glClearColor'\n" );
}

void glClear( GLbitfield mask ) {
  LOG( LOGGER_WARNING, "Simulating 'glClear'\n" );
}

void glutSwapBuffers() {
  LOG( LOGGER_WARNING, "Simulating 'glutSwapBuffers'\n" );
}

void glMatrixMode( GLenum mode ) {
  LOG( LOGGER_WARNING, "Simulating 'glMatrixMode'\n" );
}

void glLoadIdentity() {
  LOG( LOGGER_WARNING, "Simulating 'glLoadIdentity'\n" );
}

void glOrtho( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val ) {
  LOG( LOGGER_WARNING, "Simulating 'glOrtho'\n" );
}

void glViewport( GLint x, GLint y, GLint w, GLint h ) {
  LOG( LOGGER_WARNING, "Simulating 'glViewport'\n" );
}

void glutDisplayFunc( void (* callback)( void ) ) {
  LOG( LOGGER_WARNING, "Simulating 'glutDisplayFunc'\n" );
}

void glutReshapeFunc( void (* callback)( int, int ) ) {
  LOG( LOGGER_WARNING, "Simulating 'glutReshapeFunc'\n" );
}

void glutMouseFunc( void (* callback)( int, int, int, int ) ) {
  LOG( LOGGER_WARNING, "Simulating 'glutMouseFunc'\n" );
}

void glutPostRedisplay() {
  LOG( LOGGER_WARNING, "Simulating 'glutPostRedisplay'\n" );
}

void glutMainLoop() {
  LOG( LOGGER_WARNING, "Simulating 'glutMainLoop'\n" );
}

