#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "image.h"
#include "zpixel.h"
#include <glib.h>
#include "stack2.h"
void calculDegradation(Zpixel* zpixel ,my_stack_t* pile , void (*critere)(Zpixel * zpixel , my_stack_t * stack)){
   (*critere)(zpixel, pile);
}
int estPuissanceDeDeux(int n) {
    return (n & (n - 1)) == 0 && n != 0;
}
int puissanceDeDeuxSuivante(int n) {
    int puissance = 1;
    while (puissance < n) {
        puissance *= 2;
    }
    return puissance;
}

GNode* CreateArbreZpixel(int x, int y, int taille, Image* image,void (*critere)(Zpixel * zpixel , my_stack_t * stack)) {
    if (x < 0 || y < 0 || x > image->largeur-1 || y > image->hauteur-1) {
        return NULL;
    }
    if(!estPuissanceDeDeux(taille)){
        taille = puissanceDeDeuxSuivante(taille);
        //printf("la taille est %d\n" , taille);
    }
    Zpixel* zpixel = createZpixel(taille, x, y, 0, 0, 0, 0.0);
    GNode* noeud = g_node_new(zpixel);
    if (taille == 1) {
        unsigned char r = x % 256, g = y % 256, b = (x + y) % 256;
        initZpixel(zpixel,taille, x, y, r, g, b, 0.0);
    } else {
        GNode* filsGaucheHaut = CreateArbreZpixel(x, y, taille / 2, image,critere);
        GNode* filsDroiteHaut = CreateArbreZpixel(x + taille / 2, y, taille / 2, image,critere);
        GNode* filsGaucheBas = CreateArbreZpixel(x, y + taille / 2, taille / 2, image,critere);
        GNode* filsDroiteBas = CreateArbreZpixel(x + taille / 2, y + taille / 2, taille / 2, image,critere);

        my_stack_t* pile = stack_create(4);
        int rtot=0 , gtot=0 , btot=0 ,nbFils=0;
    if (filsGaucheHaut ) {
        g_node_append(noeud, filsGaucheHaut);
        stack_push(pile,filsGaucheHaut);
        rtot += ((Zpixel *)(filsGaucheHaut->data))->R;
        gtot += ((Zpixel *)(filsGaucheHaut->data))->G;
        btot += ((Zpixel *)(filsGaucheHaut->data))->B;
        nbFils++;
    }

    if (filsDroiteHaut) {
        g_node_append(noeud, filsDroiteHaut);
        stack_push(pile,filsDroiteHaut);
        rtot += ((Zpixel *)(filsDroiteHaut->data))->R;
        gtot += ((Zpixel *)(filsDroiteHaut->data))->G;
        btot += ((Zpixel *)(filsDroiteHaut->data))->B;
        nbFils++;
    }

    if (filsGaucheBas) {
        g_node_append(noeud, filsGaucheBas);
        stack_push(pile,filsGaucheBas);
        rtot += ((Zpixel *)(filsGaucheBas->data))->R;
        gtot += ((Zpixel *)(filsGaucheBas->data))->G;
        btot += ((Zpixel *)(filsGaucheBas->data))->B;
        nbFils++;
    }

    if (filsDroiteBas) {
        g_node_append(noeud, filsDroiteBas);
        stack_push(pile,filsDroiteBas);
        rtot += ((Zpixel *)(filsDroiteBas->data))->R;
        gtot += ((Zpixel *)(filsDroiteBas->data))->G;
        btot += ((Zpixel *)(filsDroiteBas->data))->B;
        nbFils++;
    }

    if(nbFils>0){
        zpixel->R = rtot / nbFils;
        zpixel->G = gtot / nbFils;
        zpixel->B= btot / nbFils;
    }
   //printf("Nombre de fils du nœud (%d, %d, %d): %d\n", zpixel->x, zpixel->y, zpixel->size, nbFils);
   
    calculDegradation(zpixel ,pile,critere);
    }
    return noeud;
}
void afficheArbreZpixel( GNode* arbre_zpixel, Image* image, double seuilDonee){
    if(arbre_zpixel == NULL|| seuilDonee <0){
        return;
    }
    Zpixel* zpixel= arbre_zpixel->data;
    //printf("AfficheArbreZpixel: x=%d, y=%d, size=%d\n", zpixel->x, zpixel->y, zpixel->size);
    if(zpixel->size==1|| zpixel->degradation<=seuilDonee){
        projectionImage(zpixel, image);
    }else{
        GNode* fils = arbre_zpixel->children;
        while(fils){
            afficheArbreZpixel(fils,image,seuilDonee);
            fils=fils->next;
        }
    }
}
Image* copie_image(GNode* arbre_pixel, Image* image, double seuilDonne){
    Image* degradation=createImage(image->hauteur,image->largeur,image->rowstride);
    afficheArbreZpixel(arbre_pixel, degradation,seuilDonne);
    return degradation;
}  
void degradationTaille(Zpixel* zpixel, my_stack_t* pile){
    (void) pile;
    zpixel->degradation=zpixel->size;
}
void degradationParLuminoste(Zpixel* zpixel, my_stack_t* pile){
    if (stack_is_empty(pile)) {
        return;
    }

    Zpixel* zpixel_lum = (Zpixel*)(((GNode*)stack_pop(pile))->data);
    double lumonisite_max = luminosite(zpixel_lum);

    while (!stack_is_empty(pile)) {
        GNode* fils = (GNode*)stack_pop(pile);
        
        if (fils != NULL && fils->data != NULL) {
            double lum = luminosite((Zpixel*)(fils->data));

            //printf("Luminosité du pixel: %lg\n", lum); 

            if (lum > lumonisite_max) {
                lumonisite_max = lum;
            }
        }
    }

    zpixel->degradation = lumonisite_max;

    //printf("Dégradation finale: %lg\n", zpixel->degradation); 
}
void degradationDistanceMax(Zpixel* zpixel, my_stack_t* pile) {
    if (stack_is_empty(pile)) {
        return;
    }

    Zpixel* zpixel_ref = (Zpixel*)(((GNode*)stack_pop(pile))->data);
    double distance_max = 0.0;

    while (!stack_is_empty(pile)) {
        GNode* fils1 = (GNode*)stack_pop(pile);

        if (fils1 != NULL && fils1->data != NULL) {
            Zpixel* zpixel1 = (Zpixel*)(fils1->data);

            GNode* fils2 = (GNode*)stack_pop(pile);

            if (fils2 != NULL && fils2->data != NULL) {
                Zpixel* zpixel2 = (Zpixel*)(fils2->data);

                double distance = distance2pixels(zpixel1, zpixel2);

                //printf("Distance entre pixels (%d, %d) et (%d, %d): %lg\n", zpixel1->x, zpixel1->y, zpixel2->x, zpixel2->y, distance);

                if (distance > distance_max) {
                    distance_max = distance;
                }
            }
        }
    }

    zpixel->degradation = distance_max;

   //printf("Dégradation finale: %lg\n", zpixel->degradation); 
}

