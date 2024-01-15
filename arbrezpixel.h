#ifndef _ARBREZPIXEL_H
#define _ARBREZPIXEL_H
#include "image.h"
#include "zpixel.h"
#include <glib.h>
#include "stack2.h"
void calculDegradation(Zpixel* zpixel);
int puissanceDeDeuxSuivante(int n);
GNode* CreateArbreZpixel(int x, int y, int taille, Image* image,void (*critere)(Zpixel * zpixel , my_stack_t * stack));
void afficheArbreZpixel( GNode* arbre_zpixel, Image* image, double seuilDonee);
Image* copie_image(GNode* arbre_pixel, Image* image, double seuilDonne);
void degradationTaille(Zpixel* zpixel, my_stack_t* pile);
void degradationParLuminoste(Zpixel* zpixel, my_stack_t* pile);
void degradationDistanceMax(Zpixel* zpixel, my_stack_t* pile);
#endif




