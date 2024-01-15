#include "zpixel.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "image.h"
Zpixel* createZpixel( int size,int x,int y,unsigned char R,unsigned char G,unsigned char B,double degradation){
    Zpixel* zpixel;
    zpixel=(Zpixel*)malloc(sizeof(Zpixel));
    if(zpixel==NULL) return NULL;
    initZpixel( zpixel,size, x,y, R, G, B,degradation);
    return zpixel;
}
void initZpixel(Zpixel* zpixel, int size,int x,int y, unsigned char R, unsigned char G, unsigned char B, double degradation){
    zpixel->size=size;
    zpixel->x=x;
    zpixel->y=y;
    zpixel->R=R;
    zpixel->G=G;
    zpixel->B=B;
    zpixel->degradation=degradation;
}
void initZpixelBlanc(Zpixel* zpixel){
    zpixel->R=255;
    zpixel->G=255;
    zpixel->B=255;
}
void initZpixelNoir(Zpixel* zpixel){
    zpixel->R=0;
    zpixel->G=0;
    zpixel->B=0;
}
double luminosite(Zpixel* zpixel){
    unsigned char R=zpixel->R;
    unsigned char G=zpixel->G;
    unsigned char B=zpixel->B;
    float M=fmax(R,(fmax(G,B)));
    float m=fmin(R,(fmin(G,B)));
    if(M+m == 0) return 0;
    float lumonisite=((M+m)/2);
    return lumonisite;
}
double saturation(Zpixel* zpixel){
    unsigned char R=zpixel->R;
    unsigned char G=zpixel->G;
    unsigned char B=zpixel->B;
    float M=fmax(R,(fmax(G,B)));
    float m=fmin(R,(fmin(G,B)));
    float saturation;
    if(M+m == 0) return 0;
    if(luminosite(zpixel)<128){
        saturation=(255 * (M-m)/(M+m));
    }
    else{
        saturation=(255*(M-m)/(511-(M+m)));
    }
    return saturation;
}
double distance2pixels(Zpixel* zpixel1,Zpixel* zpixel2){
    unsigned char R1=zpixel1->R;
    unsigned char R2=zpixel2->R;
    unsigned char G1=zpixel1->G;
    unsigned char G2=zpixel2->G;
    unsigned char B1=zpixel1->B;
    unsigned char B2=zpixel2->B;
    return sqrt(((R2-R1)*(R2-R1))+((G2-G1)*(G2-G1))+((B2-B1)*(B2-B1)));
}
void projectionImage(Zpixel* zpixel, Image* image) {
    for (int i = zpixel->x; i < zpixel->x + zpixel->size && i < image->largeur; i++) {
        for (int j = zpixel->y; j < zpixel->y + zpixel->size && j < image->hauteur; j++) {
            // Vérifier que les indices restent dans les limites de l'image
            if (i >= 0 && j >= 0) {
                setImage(image, i, j, zpixel->R, zpixel->G, zpixel->B);
            }
        }
    }
}
