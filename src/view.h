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

void renderScene(void);
void setupInterface( int, char **);
void mainLoop(void);

#endif
