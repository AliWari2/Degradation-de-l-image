#ifndef _IMAGE_H
#define _IMAGE_H
typedef struct{
    int largeur;
    int hauteur;
    int rowstride;
    unsigned char* pixels;
}Image;
Image* createImage(int largeur,int hauteur,int rowstride);
void freeImage(Image* image);
void getImage(Image* image, int x,int y,int *code,unsigned char* r, unsigned char* g,unsigned char* b);
void setImage(Image* image,int x , int y, unsigned char r, unsigned char g, unsigned char b);
void affichage(Image *image);
#endif