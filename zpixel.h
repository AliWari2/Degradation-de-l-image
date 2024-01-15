#ifndef _ZPIXEL_H
#define _ZPIXEL_H
#include "image.h"
typedef struct{
    int size;
    int x;
    int y;
    unsigned char R;
    unsigned char G;
    unsigned char B;
    double degradation;
}Zpixel;
Zpixel* createZpixel( int size,int x,int y,unsigned char R,unsigned char G,unsigned char B,double degradation);
void initZpixel(Zpixel* zpixel, int size,int x,int y, unsigned char R, unsigned char G, unsigned char B, double degradation);
void initZpixelBlanc(Zpixel* zpixel);
void initZpixelNoir(Zpixel* zpixel);
double luminosite(Zpixel* zpixel);
double saturation(Zpixel* zpixel);
double distance2pixels(Zpixel* zpixel1,Zpixel* zpixel2);
void projectionImage(Zpixel* zpixel, Image* image);
#endif