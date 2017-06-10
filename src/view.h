#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>

#define PI 3.14159265
#define VP_X 800
#define VP_Y 600

#ifndef __VIEW_H__
#define __VIEW_H__

//######## CHIP DETAILS #######
#define PINS 28
#define	H 150
#define RATIO 3.5

void drawPin( int, float x, float y, int colour );
void drawWire( int, float x, float y, int colour );
void drawOutput( int, float x, float y, int colour );
void drawInputs( int, float x, float y, int colour );
void drawElements( void (*f)(int, float, float, int), uint32_t elements, int colour );
void drawChip(void);
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);
void updateCamera(void);
void changeSize(int w, int h);
void renderScene(void);
void setupInterface( int, char **);
void mainLoop(void);

#endif
