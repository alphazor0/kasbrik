#include "brique.h"
#include "data.h"
#include <windows.h>
#include <gl/gl.h>


void build_brique(Brique* bri, float x, float y)
{
bri->width = BRIQUE_WIDTH;  
bri->height = BRIQUE_HEIGHT;
bri->color.red = BRIQUE_RED_COLOR;
bri->color.blue = BRIQUE_BLUE_COLOR;
bri->color.green = BRIQUE_GREEN_COLOR;
bri->vie = BRIQUE_NORMALE_VIE;
bri->center.x = x;
bri->center.y = y;
bri->casse = false;
}


void draw_brique(Brique* bri){
	if (bri->casse == false) {
		glColor3f(bri->color.red, bri->color.green, bri->color.blue);
		glBegin(GL_QUADS);
		glVertex2f(bri->center.x - bri->width / 2, bri->center.y - bri->height / 2);
		glVertex2f(bri->center.x - bri->width / 2, bri->center.y + bri->height / 2);
		glVertex2f(bri->center.x + bri->width / 2, bri->center.y + bri->height / 2);
		glVertex2f(bri->center.x + bri->width / 2, bri->center.y - bri->height / 2);
		glEnd();
	}
}

void despawn_brique(Brique* bri) {
	if (bri->vie == 0) {
		bri->casse = true;
		bri->center.x = -150.0;
		bri->center.y = -150.0;
	}

}