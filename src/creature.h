//
//  creature.h
//  LifeGame
//
//  Created by Buron on 5/03/14.
//
//

#ifndef __LifeGame__creature__
#define __LifeGame__creature__


class creature{
    public:
    //Variables
    int x;
    int y;
    int energie;
    int predation;
    int deplacement;
    int reproduction; /*predation 1->5/deplacement 1->5/reproduction 1->3*/
    char type; /*h = herbivore/p = predateur/v = vegetal*/
    
       
    //constructeurs
    creature();
    creature(int xExp, int yExp, int predationExp, int deplacementExp, int reproductionExp,
             char typeExp,int energieExp);
    void deplacementCreature(int lowerBoundx,int upperBoundx,int lowerBoundy,int upperBoundy,int xBestPrey, int yBestPrey);

};

#endif /* defined(__LifeGame__creature__) */

