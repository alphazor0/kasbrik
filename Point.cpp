#include <math.h>
#include "point.h"



double norme(Point p){
	return sqrt(p.x*p.x + p.y*p.y);
}

double pscal(Point p, Point q){
	return (p.x*q.x + p.y*q.y) ;
}