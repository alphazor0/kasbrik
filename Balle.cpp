#include "balle.h"
#include "data.h"
#include "raquette.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>
#include "point.h"
#include "brique.h"
#include <stb/stb_image.h>

void build_balle(Balle *balle)
{
	balle->radius = BALLE_RADIUS;
	balle->color.red = BALLE_RED_COLOR;
	balle->color.green = BALLE_GREEN_COLOR;
	balle->color.blue = BALLE_BLUE_COLOR;
	balle->vitesse.x = 0.0f;
	balle->vitesse.y = BALLE_SPEED;
	balle->isAlive = false;
	// pos balle
}


int widthImg, heightImg, numColCh;
unsigned char* bytes = stbi_load("xdd.png", &widthImg, &heightImg, &numColCh, 0);




void draw_balle(Balle *balle)
{
	/*GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_texture0);
	glBindTexture(GL_Texture_2D, texture);*/

	if (balle->isAlive)
	{
		glColor3d(balle->color.red, balle->color.green, balle->color.blue);
		glBegin(GL_POLYGON);
		for (int i = 0; i < COTE_CERCLE; i++)
		{
			float theta = 2 * PI * i / COTE_CERCLE;
			glVertex2f(balle->position.x + balle->radius * cos(theta), balle->position.y + balle->radius * sin(theta));
		}
		glEnd();
	}
}
void move_balle(Balle *balle, double dt)
{
	balle->position.x += balle->vitesse.x * dt;
	balle->position.y += balle->vitesse.y * dt;
}
void collision_plafond(Balle *balle, float hauteur_plafond)
{
	if (balle->position.y >= hauteur_plafond - balle->radius)
	{
		if (balle->vitesse.y > 0)
		{
			balle->vitesse.y *= (-1);
		}
	}
}
void collision_murs(Balle *balle)
{
	if (balle->position.x >= WINDOW_WIDTH - balle->radius)
	{
		if (balle->vitesse.x > 0)
		{
			balle->vitesse.x *= (-1);
		}
	}
	else if (balle->position.x <= balle->radius)
	{
		if (balle->vitesse.x < 0)
		{
			balle->vitesse.x *= (-1);
		}
	}
}

void collision_raquette(Balle *balle, Raquette *raq)
{
	double x2 = raq->center.x - 0.5 * raq->width;
	double x1 = x2 - balle->radius;
	double x3 = x2 + raq->width;
	double x4 = x3 + balle->radius;
	double xballe = balle->position.x;
	double yballe = balle->position.y;
	if (xballe < x1)
	{
		return;
	}
	else if (xballe < x2)
	{
		if (yballe <= raq->height + balle->radius)
		{
			Point cb = {xballe - x2, yballe - raq->height};
			double dist = norme(cb);
			if (dist <= balle->radius)
			{
				Point normale = {cb.x / dist, cb.y / dist};
				double vn = pscal(balle->vitesse, normale);
				if (vn < 0)
				{
					Point tangente = {-normale.y, normale.x};
					double vt = pscal(balle->vitesse, tangente);
					balle->vitesse.x = -vn * normale.x + vt * tangente.x;
					balle->vitesse.y = -vn * normale.y + vt * tangente.y;
				}
			}
		}
	}
	else if (xballe <= x3)
	{
		if (yballe <= raq->height + balle->radius)
		{
			balle->vitesse.y *= (-1);
		}
	}
	else if (xballe <= x4)
	{
		Point cb = {xballe - x4, yballe - raq->height};
		double dist = norme(cb);
		if (dist <= balle->radius)
		{
			Point normale = {cb.x / dist, cb.y / dist};
			double vn = pscal(balle->vitesse, normale);
			if (vn < 0)
			{
				Point tangente = {-normale.y, normale.x};
				double vt = pscal(balle->vitesse, tangente);
				balle->vitesse.x = vn * normale.x - vt * tangente.x;
				balle->vitesse.y = -vn * normale.y + vt * tangente.y;
			}
		}
	}
	else
		return;
}

void collision_brique(Balle* balle, Brique* bri)
{
	double x2 = bri->center.x - 0.5 * bri->width;
	double x1 = x2 - balle->radius;
	double x3 = x2 + bri->width;
	double x4 = x3 + balle->radius;
	double xballe = balle->position.x;
	double yballe = balle->position.y;
	double y2 = bri->center.y - 0.5 * bri->height;
	double y1 = y2 - balle->radius;
	double y3 = y2 + bri->height;
	double y4 = y3 + balle->radius;

	if (xballe < x1)
	{

		return;
	}
	else if (xballe < x2)
	{
		if (yballe < y1)
		{
			return;
		}

		else if (yballe < y2)
		{
			Point cb = { xballe - x2, y2 - yballe };
			double dist = norme(cb);
			if (dist <= balle->radius)
			{
				Point normale = { cb.x / dist, cb.y / dist };
				double vn = pscal(balle->vitesse, normale);

				Point tangente = { -normale.y, normale.x };
				double vt = pscal(balle->vitesse, tangente);
				balle->vitesse.x = vn * normale.x - vt * tangente.x;
				balle->vitesse.y = -vn * normale.y + vt * tangente.y; // tout �a coin bas gauche
				bri->vie--;
			}
		}
		else if (yballe < y3)
		{
			Point cb = { xballe - x2, 0 };
			double dist = norme(cb);
			if (dist <= balle->radius)
			{
				balle->vitesse.x *= -1;
				bri->vie--;
			}
		}
		else if (yballe < y4)
		{
			Point cb = { xballe - x2, y4 - yballe };
			double dist = norme(cb);
			if (dist <= balle->radius)
			{
				Point normale = { cb.x / dist, cb.y / dist };
				double vn = pscal(balle->vitesse, normale);

				Point tangente = { -normale.y, normale.x };
				double vt = pscal(balle->vitesse, tangente);
				balle->vitesse.x = vn * normale.x - vt * tangente.x;
				balle->vitesse.y = -vn * normale.y + vt * tangente.y;
				bri->vie--;
			}
		}
	}
	else if (xballe < x3)
	{
		if (yballe < y1)
		{
			return;
		}

		if (yballe < y2)
		{

			Point cb = { 0, y2 - yballe };
			double dist = norme(cb);
			if (dist <= balle->radius)
			{
				balle->vitesse.y *= -1;
				bri->vie--;
			}
		}
		if (yballe < y4)
		{

			Point cb = { 0, y4 - yballe };
			double dist = norme(cb);
			if (dist <= balle->radius)
			{
				balle->vitesse.y *= -1;
				bri->vie--;
			}
		}


	}
	else if (xballe < x4)
	{
		if (yballe < y1) {
			return;
		}


		if (yballe < y2)
		{
			Point cb = { xballe - x3, y2 - yballe };
			double dist = norme(cb);
			if (dist <= balle->radius)
			{
				Point normale = { cb.x / dist, cb.y / dist };
				double vn = pscal(balle->vitesse, normale);

				Point tangente = { -normale.y, normale.x };
				double vt = pscal(balle->vitesse, tangente);
				balle->vitesse.x = vn * normale.x - vt * tangente.x;
				balle->vitesse.y = -vn * normale.y + vt * tangente.y;
				bri->vie--;
			}
		}

		else if (yballe < y3)
		{
			Point cb = { xballe - x3, 0 };
			double dist = norme(cb);
			if (dist <= balle->radius)
			{
				balle->vitesse.x *= -1;
				bri->vie--;
			}
		}
		else if (yballe < y4)
		{
			Point cb = { xballe - x3, yballe - y3};
			double dist = norme(cb);
			if (dist <= balle->radius)
			{
				Point normale = { cb.x / dist, cb.y / dist };
				double vn = pscal(balle->vitesse, normale);

				Point tangente = { -normale.y, normale.x };
				double vt = pscal(balle->vitesse, tangente);
				balle->vitesse.x = vn * normale.x - vt * tangente.x;
				balle->vitesse.y = -vn * normale.y + vt * tangente.y;
				bri->vie--;
			}
		}
	}
}
	