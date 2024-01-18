#ifndef WORLD_H
#define WORLD_H
#include "raquette.h"
#include "balle.h"
#include "data.h"
#include "brique.h"

typedef struct World {
   int currentGameLevel;   // niveau courant
   int currentGameScore;   // score courant
   int restingLives;       // nombre de vies restantes
   float hauteur_plafond;

   Raquette raquette;
   Balle balle[INITIAL_LIVES_NUMBER];
   Brique brique;
   Brique niveau1[NIVEAU_1NBB];
   //� compl�ter

} World;


void build_world(World*);
void draw_world(World*);
void draw_bandeau(World*);
void simul_world(World*);



#endif