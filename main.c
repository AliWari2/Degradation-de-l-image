#include "zpixel.h"
#include "image.h"
#include <math.h>
#include <stdio.h>
#include "arbrezpixel.h"
// #include <glib.h>
#include "stack2.h"
int main(){
    //Creation d'un zpixel
    Zpixel* zpixel = createZpixel(2,1,1,255,234,235,2.0);
    if(zpixel == NULL || zpixel->size!=2 ||zpixel->x!=1 || zpixel->y!=1|| zpixel->R!=255 || zpixel->G!=234 || zpixel->B!=235 || zpixel->degradation!=2.0){
        printf(" la creation du zpixel a echoué \n");
    }
    //Creation d'un zpixel Noir et zpixelBlanc
    Zpixel* zpixelBlanc= createZpixel(5,1,1,255,234,235,2.0);
    Zpixel* zpixelNoir = createZpixel(7,1,1,255,234,235,2.0);
    initZpixelBlanc(zpixelBlanc);
    initZpixelNoir(zpixelNoir);
    if(zpixelBlanc->R!=255 || zpixelBlanc->G !=255 || zpixelBlanc->B !=255){
        printf("la creation du pixel blanc a echoué\n");
        return 1;
    }
    if(zpixelNoir->R!=0||zpixelNoir->G!=0||zpixelNoir->B!=0){
        printf("la creation du pixel Noir a echoué");
        return 1;
    }
    double lum=luminosite(zpixelBlanc);
    if(lum != 255){
        printf("le calcul de luminosite pour le pixel Noir a echoué\n");
        return 1;
    }
    double sat=saturation(zpixelNoir);
    if(sat!=0){
        printf("le calcul saturation pour le pixel Blanc a echoué\n");
        return 1;
    }
    Zpixel* zpixel2 = createZpixel(1,1,1,255,245,235,3.0);
    double distance= distance2pixels(zpixel,zpixel2);
    if(distance !=11){
        printf("le calcul du distance a echoué \n");
        return 1;
    }
    Image* image= createImage(10,10,31);
    Image* image1 = createImage(2,2,7);
    if(image == NULL || image->hauteur!=10||image->largeur!=10||image->rowstride!=31){
        printf("la creation de l'image a echoué\n");
        return 1;
    }
   
   // projectionImage(zpixel, image);
    //affichage(image);
    Zpixel * zp = createZpixel(3,1,1,20,52,20,0);
    Zpixel * zpix= createZpixel(3,3,9,19,20,21,0.0);
    Image * image2 = createImage(10,10,31);
    //printf("Projection du zpixel rouge gris de taille %d sur l'image (3,3)\n" , zpix->size);
    //projectionImage(zpix,image2);
    //affichage(image2);
   /*  

    
    }*/
   GNode* CreateArbre = CreateArbreZpixel(0, 0, 16, image2, &degradationParLuminoste);
    if(CreateArbre == NULL){
        printf("La creation de l'arbre a echoué");
    }
    Zpixel* arbrepixel = (Zpixel*)CreateArbre->data;
    if(arbrepixel==NULL){
        printf("La creation du zpixel dans l'arbre a echoué");
    }
     //printf("La x est %d,%d,%d\n",arbrepixel->x,arbrepixel->size,arbrepixel->y);
    if (arbrepixel->x != 0 || arbrepixel->y != 0 || arbrepixel->size != 16) {
        printf("la creation de l'arbre du pixel a echoue \n");
    }
    //afficheArbreZpixel(CreateArbre, image2, 0);
    Image * imag = copie_image(CreateArbre, image, 4);
    affichage(imag);
}




