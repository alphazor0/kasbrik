#ifndef RAQUETTE_H
#define RAQUETTE_H

#include "color.h"
#include "point.h"

typedef struct Raquette
{
	int width,height;
	Color color;
	Point center;
}Raquette;

void build_raquette(Raquette*);
void draw_raquette(Raquette*);
#endif