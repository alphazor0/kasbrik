#ifndef BALLE_H
#define BALLE_H
#include "color.h"
#include "point.h"
#include "raquette.h"
#include "brique.h"


typedef struct Balle {
	float radius;
	Color color;
	Point position;
	Point vitesse;
	bool isAlive;


} Balle;
void build_balle(Balle*);
void draw_balle(Balle*);
void move_balle(Balle*, double);
void collision_plafond(Balle*, float);
void collision_murs(Balle*);
void collision_raquette(Balle*, Raquette*);
void collision_brique(Balle*, Brique*);

#endif