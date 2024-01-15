#include "image.h"
#include <stdlib.h>
#include <stdio.h>
Image* createImage(int largeur,int hauteur,int rowstride){
    //rowstride = 3*largeur +1;
    if(rowstride<=3*largeur){
        return NULL;
    }
    Image* newImage=(Image*)malloc(sizeof(Image));
    if(newImage==NULL){
        return NULL;
    }
    newImage->largeur=largeur;
    newImage->hauteur=hauteur;
    newImage->rowstride=rowstride;
    newImage->pixels=(unsigned char*)malloc(rowstride*hauteur);
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            setImage(newImage,i,j,0,0,0);
        }
    }
    if(newImage->pixels==NULL){
        free(newImage);
        return NULL;
    }
    return newImage;
}
void freeImage(Image* image){
    if(image != NULL){
        if(image->pixels !=NULL){
            free(image->pixels);
        }
        free(image);
    }
}
void affichage(Image* image){
    unsigned char r,g,b;
    int code;
    for(int i=0;i<image->hauteur;i++){
        for(int j=0;j<image->largeur;j++){
            getImage(image,i,j,&code,&r,&g,&b);
            if(code==0) break;
            printf(" (%03u,%03u,%03u) " , r,g,b);
        }
        printf("\n");
    }
}
void getImage(Image* image, int x,int y,int *code,unsigned char* r, unsigned char* g,unsigned char* b){
    *r= *(image->pixels+ x*image->rowstride+(y*3));
    *g= *(image->pixels+ x*image->rowstride+(y*3+1));
    *b= *(image->pixels+ x*image->rowstride+(y*3+2));
    *code=1;
}
void setImage(Image* image,int x , int y, unsigned char r, unsigned char g, unsigned char b){
    if(x<0||x>=image->hauteur || y<0 || y>=image->largeur){
        return;
    }
    *(image->pixels+ x*image->rowstride+(y*3))=r;
    *(image->pixels+ x*image->rowstride+(y*3+1))=g;
    *(image->pixels+ x*image->rowstride+(y*3+2))=b;
}
