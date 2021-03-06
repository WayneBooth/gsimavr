
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>

#include "logger.h"
#include "view.h"
#include "model.h"
#include "controller.h"

int mouseButState[] = {0, 0, 0};
float pins[30][4];
float w = 1;
float l = 50;
float t = 200;
int ww = VP_X;
int hh = VP_Y;




//############################################
//############################################
//############################################

void drawPin( int pin, float x, float y, int colour ) {
	UNUSED(colour);
	if( y > t ) {
		y -= 2;
	}
	else {
		y -= 8;
	}
        glColor3f(0.6F,0.6F,0.6F);
	glBegin(GL_POLYGON);
        	glVertex2f( x, y );
	        glVertex2f( x+17, y );
                glVertex2f( x+17, y+10 );
                glVertex2f( x, y+10 );
	glEnd();

	if( y > t ) {
		y -= 7;
	}
	else {
		y += 27;
	}
	pin++;
	int len = snprintf(NULL, 0, "%d", pin);
	char *st = (char *)malloc(len+1);
	snprintf(st, len+1, "%d", pin);
        glColor3f(0.4F,0.4F,0.4F);
	glPushMatrix();
	glTranslatef( x, y, 0 );
	glScalef(0.08, -0.08, 0.08);
	int i = 0;
	for( i = 0; i < len; i++ ) {
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, st[i]); // Print a character on the screen
	}
	glPopMatrix();
	free(st);


}

void drawWire( int pin, float x, float y, int colour ) {
	UNUSED(pin);
	if( colour ) {
        	glColor3f(1.0F,0.2F,0.2F);
	}
	else {
        	glColor3f(0.0F,0.0F,0.0F);
	}
	if( y > t ) {
		y += 5;
	}
	else {
		y -= 60;
	}
	x += 8;
	glLineWidth(5.0F);
	glBegin(GL_LINES);
        	glVertex2f( x, y );
        	glVertex2f( x, y + 55 );
	glEnd();
	glLineWidth(1.0F);
}

void drawArrow( float x, float y, int pointUp ) {
	if( y > t ) {
		y += 20;
	}
	else {
		y -= 80;
		pointUp ^= 1;
	}
	x -= 7;

	glBegin(GL_POLYGON);
	if( pointUp ) {
	        glVertex2f( x+15, y );
		glVertex2f( x+30, y+30 );
                glVertex2f( x+20, y+30 );
	        glVertex2f( x+20, y+60 );
        	glVertex2f( x+10, y+60 );
                glVertex2f( x+10, y+30 );
	        glVertex2f( x, y+30 );
	}
	else {
	        glVertex2f( x+15, y+60 );
	        glVertex2f( x, y+30 );
	        glVertex2f( x+10, y+30 );
	        glVertex2f( x+10, y );
	        glVertex2f( x+20, y );
	        glVertex2f( x+20, y+30 );
	        glVertex2f( x+30, y+30 );
	}
	glEnd();
}

void drawOutput( int pin, float x, float y, int colour ) {
	UNUSED(pin);
	if( colour ) {
        	glColor3f(1.0F,0.3F,0.3F);
	}
	else {
        	glColor3f(0.7F,0.7F,0.7F);
	}
	
	drawArrow( x, y, 0 );
}


void drawInputs( int pin, float x, float y, int colour ) {
	if( colour ) {
        	glColor3f(0.3F,0.3F,1.0F);
	}
	else {
        	glColor3f(0.7F,0.7F,0.7F);
	}

	drawArrow( x, y, 1 );

	if( y > t ) {
                y += 20;
        }
        else {
                y -= 80;
        }
        x -= 8;

	pins[pin+1][0] = x;
	pins[pin+1][1] = y;
	pins[pin+1][2] = x+32;
	pins[pin+1][3] = y+60;
}


//############################################
//############################################
//############################################

void drawElements( void (*f)(int, float, float, int), uint32_t elements, int colour ) {

	int i;

	for( i = 0 ; i < (PINS / 2) ; i++ ) {
		if( elements & ( 1 << i ) ) {
			float x = l + ( i * ( w / (PINS/2) ) );
			(*f)( i, x+20, t+H, colour );
		}
	}

	for( i = (PINS / 2) ; i < PINS ; i++ ) {
		if( elements & ( 1 << i ) ) {
			float x = l + ( (PINS - i) * ( w / (PINS/2) ) );
			(*f)( i, x-20, t, colour );
		}
	}
}

void drawChip(void) {

	float r;
	int i;

        glColor3f(0.3F,0.3F,0.3F);
        glBegin(GL_POLYGON);
                glVertex2f( l,   t );
                glVertex2f( l+w+20, t );
                glVertex2f( l+w+20, t+H );
                glVertex2f( l,   t+H );
        glEnd();

        glColor3f(0.4F,0.4F,0.4F);
	glBegin(GL_POLYGON);
		r = 0;
		while( r <= PI ) {
			glVertex2f( l + ( 14 * sin( r ) ), (t + (0.5 * H) + ( 14 * cos( r ) ) ) );
			r += PI/10;
		}
	glEnd();
        glColor3f(0.35F,0.35F,0.35F);
	glBegin(GL_POLYGON);
		r = 0;
		while( r <= PI ) {
			glVertex2f( l + (H * 0.15) + ( 6 * sin( r ) ), (t + (0.85 * H) + ( 6 * cos( r ) ) ) );
			r += PI/10;
		}
	glEnd();

	char *chipname = CHIPNAME();
	int len = strlen( chipname );
        glColor3f(0.6F,0.6F,0.6F);
	glPushMatrix();
	glTranslatef( l + (w / 4) , t + (H / 1.8), 0 );
	glScalef(0.15, -0.15, 0.15);
	for( i = 0; i < len; i++ ) {
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, chipname[i]); // Print a character on the screen
	}
	glPopMatrix();

	drawElements( drawPin, 0xFFFFFFF, 1 );	

}

// #####################################################
// #####################################################
// #####################################################


void updateCamera(void) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, ww, 0, hh, -1, 1);
	glScalef(1, -1, 1);
	glTranslatef(0, -hh, 0);
}

void changeSize(int w, int h) {

	ww = w;
	hh = h;
	glViewport(0, 0, w, h); 

	updateCamera();
}

void renderScene(void) {

	glClearColor(0.8F, 0.8F, 0.8F, 1.0F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawChip();
	drawElements( drawWire,   get_positive_power(),   1 );
	drawElements( drawWire,   get_negative_power(),   0 );
	drawElements( drawOutput, get_positive_outputs(), 1 );
	drawElements( drawOutput, get_negative_outputs(), 0 );
	drawElements( drawInputs, get_positive_inputs(),  1 );
	drawElements( drawInputs, get_negative_inputs(),  0 );

	glutSwapBuffers();
	glutPostRedisplay();
}

void mouseFunc( int button, int state, int x, int y ) {

	LOG( LOGGER_DEBUG, "Mouse Button %d, is in state %d\n", button, state);

	int i;
	for( i = 1 ; i < PINS ; i++ ) {
		if( pins[i][0] < x && pins[i][1] < y && pins[i][2] > x && pins[i][3] > y ) {

			if( state == GLUT_DOWN ) {
				mouseButState[button] = i;
			}

			if( state == GLUT_UP ) {
				if( mouseButState[button] == i ) {
					changeInput( i, button );
				}
				mouseButState[button] = 0;
			}
		}
	}
	
}


void setupInterface( int argc, char **argv ) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(VP_X,VP_Y);
	glutCreateWindow("GSimAvr a Simple Graphical wrapper over SimAVR");

	// Calculate the width of the chip
        float ratio = ( (PINS - 8) * 0.125 ) + 1;
	w = (ratio * H);

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutMouseFunc(mouseFunc);
}

void mainLoop( void ) {

	glutMainLoop();
}

