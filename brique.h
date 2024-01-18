#ifndef BRIQUE_H
#define BRIQUE_H
#include "color.h"
#include "point.h"
#include "brique.h"


typedef struct Brique
{
	int width,height;
	Color color;
	Point center;
	int vie;
	bool casse;

	
}Brique;


void build_brique(Brique*, float, float);
void draw_brique(Brique*);
void despawn_brique(Brique*);
































#endif