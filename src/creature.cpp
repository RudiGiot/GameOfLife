//
//  creature.cpp
//  LifeGame
//
//  Created by Buron on 5/03/14.
//
//


#include "creature.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>


//constructeurs pour créature
creature::creature(){}

creature::creature(int xExp,int yExp,int predationExp,int deplacementExp,int reproductionExp,
                   char typeExp,int energieExp){
    x=xExp;
    y=yExp;
    predation=predationExp;
    deplacement=deplacementExp;
    reproduction=reproductionExp;
    type=typeExp;
    energie=energieExp;
}

//méthode de déplacement sur une créature
void creature::deplacementCreature(int lowerBoundx,int upperBoundx,int lowerBoundy,int upperBoundy,int xBestPrey, int yBestPrey){
    int randomNumberx=0;
    int randomNumbery=0;
    int randomNumberSigne=0;
    
    if(xBestPrey==10000 && yBestPrey==10000){//dans ce cas, pas de cible à portée -> déplacement aléatoire
    //on génère des nombre aléatoires compris entre - déplacement et déplacement
    randomNumberSigne=rand()%(2);
    if(randomNumberSigne==0){
        randomNumberx=(rand()%(this->deplacement+1))*-1;
    }else if (randomNumberSigne==1){
        randomNumberx=rand()%(this->deplacement+1);
    }
    randomNumberSigne=rand()%(2);
    if(randomNumberSigne==0){
        randomNumbery=(rand()%(this->deplacement+1))*-1;
    }else if (randomNumberSigne==1){
        randomNumbery=rand()%(this->deplacement+1);
    }
    
    if(this->x+randomNumberx > lowerBoundx && this->x+randomNumberx < upperBoundx &&
       this->y+randomNumbery > lowerBoundy && this->y+randomNumbery < upperBoundy ){ //limite du cadre
        this->x=this->x+randomNumberx;
        this->y=this->y+randomNumbery;
           }
    }else{ //la cible à portée a les coordonnées (xBestPrey ; yBestPrey)
      
        if(this->x-xBestPrey>=0 && this->y-yBestPrey>=0){//cible en - -
            if(this->x-this->deplacement > lowerBoundx &&
               this->y-this->deplacement > lowerBoundy ){ //limite du cadre
            this->x=this->x-this->deplacement;
            this->y=this->y-this->deplacement;
            }
        }else if(this->x-xBestPrey<=0 && this->y-yBestPrey>=0){ // + -
            if(this->x+this->deplacement < upperBoundx &&
               this->y-this->deplacement > lowerBoundy ){ //limite du cadre
            this->x=this->x+this->deplacement;
            this->y=this->y-this->deplacement;
            }
        }else if(this->x-xBestPrey>=0 && this->y-yBestPrey<=0){ // - +
            if(this->x-this->deplacement > lowerBoundx &&
               this->y-this->deplacement < upperBoundy ){ //limite du cadre
            this->x=this->x-this->deplacement;
            this->y=this->y+this->deplacement;
            }
        }else if(this->x-xBestPrey<=0 && this->y-yBestPrey<=0){ // + +
            if(this->x-this->deplacement < upperBoundx &&
               this->y-this->deplacement < upperBoundy ){ //limite du cadre
            this->x=this->x+this->deplacement;
            this->y=this->y+this->deplacement;
            }
        }
    }
}

