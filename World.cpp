#include "world.h"
#include "data.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <stdio.h>
#include <time.h>
#include "point.h"
#include "balle.h"
#include "raquette.h"
#include "brique.h"
#include <cstdlib>
#include <algorithm>
#include <stb/stb_image.h>

/* ++++++++++++++++++++++++++++ */
/* +++ Fonction build_world +++ */
/* ++++++++++++++++++++++++++++ */
void build_world(World* monde){
/* ======================= */
/* === Initialisations === */
/* ======================= */
   monde->currentGameLevel = 1;
   monde->currentGameScore = 0;
   monde->restingLives = INITIAL_LIVES_NUMBER;
   monde->hauteur_plafond = WINDOW_HEIGHT-BANDEAU_HEIGHT;

  build_raquette(&(monde->raquette));   //construction de la raquette

  for (int i = 0; i < NIVEAU_1NBB; i++) {

	  float A =  i * (monde->niveau1[i].width/2 + 60);
	  float B = WINDOW_WIDTH - 60;
	  
	  float D = A / B;
	  int j = (int)D;
	  float R = D - (float)j;
	  
	  float Y = 40 + monde->niveau1[i].height + j * (monde->niveau1[i].height + 40);
	 
	  
	  
	  build_brique(&(monde->niveau1[i]), B*R +60, monde->hauteur_plafond - Y);
	   


	  /*if (monde->niveau1[i].center.x + monde->niveau1[i].width < WINDOW_WIDTH) {
		  build_brique(&(monde->niveau1[i]), i * (20 + monde->niveau1[i].width), monde->hauteur_plafond - 35);
	  }
	  

	  else {
		  build_brique(&(monde->niveau1[i]), i * (20 + monde->niveau1[i].width), monde->hauteur_plafond - i * 35);
		  printf("test2");
		  build_brique(&(monde->niveau1[i]), 20 + monde->niveau1[i].width, monde->hauteur_plafond - 35);
	  }*/
	  
  }
	/*	int c = 0;
	  for (int i = 0; i < NIVEAU_1NBB; i++) {
		  
		  if (monde->niveau1[i].vie == 0) {
			  c++;
		  }

  }

	  for (int i = 0; i < NIVEAU_2NBB; i++) {
		  if (c == 20) {
			  float A = i * (monde->niveau2[i].width / 2 + 60);
			  float B = WINDOW_WIDTH - 60;

			  float D = A / B;
			  int j = (int)D;
			  float R = D - (float)j;

			  float Y = 40 + monde->niveau2[i].height + j * (monde->niveau2[i].height + 40);



			  build_brique(&(monde->niveau2[i]), B * R + 60, monde->hauteur_plafond - Y);



		  }
	  }*/

  //inissializassion des balles

  for(int i=0; i<INITIAL_LIVES_NUMBER; i++){
	  build_balle(&(monde->balle[i]));
  
  }
   //A FINIR...
}
void drawBitmapString(char*texte, void*police, Color*color, Point*position){
	glColor3d(color->red, color->green, color->blue);
	glRasterPos2d(position->x, position->y);
	for(unsigned int i = 0; i<strlen(texte); i++){
		glutBitmapCharacter(police, texte[i]);
	}
}

void simul_world(World* monde){
	//calcul du tps ecoul�
	static clock_t old_time = clock();
	clock_t new_time = clock();
	double dt = (double)(new_time - old_time)/(double)(CLOCKS_PER_SEC);
	old_time = new_time;
	if(dt == 0.0) return;
	for (int i=0; i<INITIAL_LIVES_NUMBER; i++){
		Balle* balleI = &(monde->balle[i]);
		if(balleI->isAlive){
			//deplact des balles
			move_balle(balleI, dt);
			//collisions
			collision_plafond(balleI, monde->hauteur_plafond);
			collision_murs(balleI);
			collision_raquette(balleI, &monde->raquette);
			
			for (int j = 0; j < NIVEAU_1NBB; j++) {
				collision_brique(balleI, &monde->niveau1[j]);
				despawn_brique(&monde->niveau1[j]);
			}
			if (balleI->position.y <= -balleI->radius){
				balleI->isAlive = false;
			}
			 
		}
	}
}




void draw_bandeau(World* world){
//dessin du plafond
	glColor3d(BANDEAU_RED_COLOR, BANDEAU_GREEN_COLOR, BANDEAU_BLUE_COLOR);
	glBegin(GL_LINES);
		glVertex2f(0.0, world->hauteur_plafond);
		glVertex2f(WINDOW_WIDTH, world->hauteur_plafond);
	glEnd();
//ecriture des informations
	char texte[40];
	sprintf(texte, "score : %4d  -level : %1d  -vies : %1d", world->currentGameScore, world->currentGameLevel, world->restingLives);
	printf("%s \n", texte);
	Color color;
	color.red = BANDEAU_RED_COLOR;
	color.green = BANDEAU_GREEN_COLOR;
	color.blue = BANDEAU_BLUE_COLOR;
	Point position;
	position.x = (WINDOW_WIDTH - 9*strlen(texte))/2;
	position.y = world->hauteur_plafond + (BANDEAU_HEIGHT - 15)/2;
	drawBitmapString(texte, GLUT_BITMAP_9_BY_15, &color, &position);
}

/* +++++++++++++++++++++++++++ */
/* +++ Fonction draw_world +++ */
/* +++++++++++++++++++++++++++ */
void draw_world(World* world){
/* ============================= */
/* === Dessin de la raquette === */
/* ============================= */
	draw_raquette(&(world->raquette));
	
/* ==================================== */
/* === Dessin des briques restantes === */
/* ==================================== */
	for (int i = 0; i < NIVEAU_1NBB; i++) {

		draw_brique(&(world->niveau1[i]));
	}

	/*int c = 0;
	for (int i = 0; i < NIVEAU_1NBB; i++) {

		if (world->niveau1[i].vie = 0) {
			c++;
		}
	}
	if(c == 20){
	for (int i = 0; i < NIVEAU_2NBB; i++) {

		draw_brique(&(world->niveau2[i]));
	}
	}*/

/* ============================================ */
/* === Dessin (de la balle) (ou des balles) === */
/* ============================================ */
	for(int i=0; i<INITIAL_LIVES_NUMBER; i++){
		draw_balle(&(world->balle[i]));
	}
/* ======================================================== */
/* === Dessin du panneau d'affichage (score, vies, ...) === */
/* ======================================================== */
	draw_bandeau(world);

/* ================================ */
/* === Autres dessins �ventuels === */
/* ================================ */





   //A FAIRE...
	

}