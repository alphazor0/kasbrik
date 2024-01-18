#include "raquette.h"
#include "data.h"
#include <windows.h>
#include <gl/gl.h>


void build_raquette(Raquette* raq)
{
raq->width = RAQUETTE_WIDTH;  
raq->height = RAQUETTE_HEIGHT;
raq->color.red = RAQUETTE_RED_COLOR;
raq->color.blue = RAQUETTE_BLUE_COLOR;
raq->color.green = RAQUETTE_GREEN_COLOR;
raq->center.x = WINDOW_WIDTH/2;
raq->center.y = RAQUETTE_HEIGHT/2;
}


void draw_raquette(Raquette* raq){
	glColor3f(raq->color.red, raq->color.green, raq->color.blue);
	glBegin(GL_QUADS);
		glVertex2f(raq->center.x-raq->width/2,0);
		glVertex2f(raq->center.x-raq->width/2,raq->height);
		glVertex2f(raq->center.x+raq->width/2,raq->height);
		glVertex2f(raq->center.x+raq->width/2,0);
	glEnd();
}