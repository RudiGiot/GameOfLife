#include "testApp.h"
#include "creature.h"
#include <iostream>
#include <list>
#include <cstdio>
#include <cstdlib>
#include <ctime>


/** !! INFOS Life Game
 *  Auteur : Buron Nathan
 *  Cette application fonctionne avec un fichier de configuration 
 *  lfConfig.xml qui se trouve dans les datas du projet
 *  C'est dans ce fichier qu'il est possible de changer tout un tas de paramtres
 *  Notamment les caractŽristiques des crŽatures
 *  (ne se met ˆ jour que pour les enfants futurs des crŽatures dŽjˆ prŽsentes)
 *  Ce fichier pointe lui-mme dans les datas pour les skins des crŽatures
 *  Le font et le background 
 *
 *  La mise ˆ jour se fait avec la touche 'l'
 *
 *  Bon amusement !
 */
//--------------------------------------------------------------
void testApp::setup(){
    ReadConfig();
       
    deadWorld=false;
    
    counterDivCycle=0;
    countPred=nbrPredInit;
    countHerb=nbrHerbInit;
    countVeg=nbrVegInit;
    countInva=0;
    xForInsertion=0;
    yForInsertion=0;
    
    ofBackground(0,0,0);
    populate();
    
    sprintf(cadrePressedString,"null");
    sprintf(xAndyVisedString,"null");
    sprintf(InsertionCadre,"null");
    sprintf(InsertionCycle,"null");
    sprintf(EradicationCadre,"null");
    sprintf(EradicationCycle,"null");
    }

//--------------------------------------------------------------
void testApp::update(){
    
    counterDivCycle++;
    if (counterDivCycle>DivCycle) {        /*on divise le temps pour l'incrŽmentation de cycle*/
        counterDivCycle=0;
        countCycle++;
        sprintf (actualCycleString, "%i", countCycle);
    }
    

        vieGlobal();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(255,255,255);
    backgroundImage.draw(15+XCalib, 15+YCalib);
    
    
    
    ofSetColor(100,75,50);
    ofFill();
    
    /*Pas de fond*/
    if(!BackgroundActif){
    ofRect(15+XCalib,15+YCalib,1060,805);
    }
    //boutons
    ofSetColor(255, 255, 255);
    ofRect(1100+XCalib,285+YCalib,135,20); //insŽrer
    ofRect(1100+XCalib,485+YCalib,150,20); //Žradiquer
    ofRect(1100+XCalib,566+YCalib,150,20); //Žradication totale
    ofRect(1100+XCalib,600+YCalib,50,20); //reset
        
    /*Quadrillage*/
    ofSetColor(255);
    ofDrawBitmapString("A", 5+XCalib, 190+YCalib);
    ofDrawBitmapString("B", 5+XCalib, 610+YCalib);
    ofDrawBitmapString("1", 200+XCalib, 10+YCalib);
    ofDrawBitmapString("2", 550+XCalib, 10+YCalib);
    ofDrawBitmapString("3", 900+XCalib, 10+YCalib);
    /*Fin du dessin de la grille du monde*/
    
    /*Statistiques*/
    ofDrawBitmapString("Life Game", 1100+XCalib, 20+YCalib);
    ofDrawBitmapString("Monde", 1100+XCalib, 45+YCalib);
    ofDrawBitmapString("Cycles parcourus :", 1100+XCalib, 60+YCalib);
    ofDrawBitmapString(actualCycleString, 1100+XCalib, 71+YCalib);
    /*ici, rentrer les valeurs statistiques obtenues lors du parcours des listes*/
    ofDrawBitmapString("Statistiques :", 1100+XCalib, 85+YCalib);
    ofDrawBitmapString(percentVegetalsGlobalString, 1100+XCalib, 96+YCalib);
    ofDrawBitmapString(percentHerbivorsGlobalString, 1100+XCalib, 107+YCalib);
    ofDrawBitmapString(percentPredatorsGlobalString, 1100+XCalib, 118+YCalib);
    /*ici, rentrer le nombre de "cycles" de monde effectuŽs*/
    ofDrawBitmapString("Cadre Vise :", 1100+XCalib, 145+YCalib);
    ofDrawBitmapString(cadreVisedString, 1100+XCalib, 156+YCalib);
    ofDrawBitmapString(xAndyVisedString, 1130+XCalib, 156+YCalib); /*ici, rentrer les valeurs envent mouseMoved*/
    ofDrawBitmapString("Statistiques cadre :", 1100+XCalib, 170+YCalib);
    ofDrawBitmapString(percentVegetalsZoneString, 1100+XCalib, 181+YCalib);
    ofDrawBitmapString(percentHerbivorsZoneString, 1100+XCalib, 192+YCalib);
    ofDrawBitmapString(percentPredatorsZoneString, 1100+XCalib, 203+YCalib);
    /*gestion de la nouvelle espce*/
    ofDrawBitmapString("Espece invasive", 1100+XCalib, 250+YCalib);
    ofDrawBitmapString("Lieu selectionne :", 1100+XCalib, 265+YCalib);
    ofDrawBitmapString(cadrePressedString, 1100+XCalib, 276+YCalib); /*ici, rentrer les valeurs envent mousePressed*/
    ofDrawBitmapString(xAndyPressedString, 1130+XCalib, 276+YCalib);
    ofSetColor(0);
    ofDrawBitmapString("Inserer l'espece", 1100+XCalib, 300+YCalib); /*bouton*/
    ofSetColor(255);
    ofDrawBitmapString("Details Insertion : ", 1100+XCalib, 330+YCalib);
    ofDrawBitmapString(InsertionCadre, 1100+XCalib,342+YCalib);
    ofDrawBitmapString(InsertionCycle, 1150+XCalib, 342+YCalib);
    ofDrawBitmapString("Invasive monde :", 1100+XCalib, 358+YCalib);
    ofDrawBitmapString(percentInvasivesGlobalString, 1100+XCalib, 370+YCalib);
    ofDrawBitmapString("Invasive cadre : ", 1100+XCalib, 382+YCalib);
    ofDrawBitmapString(percentInvasivesZoneString, 1100+XCalib, 394+YCalib);
    /*Eradication de l'espce*/
    ofDrawBitmapString("Eradication", 1100+XCalib, 450+YCalib);
    ofDrawBitmapString("Cadre selectionne :", 1100+XCalib, 465+YCalib);/*mousePressed*/
    ofDrawBitmapString(cadrePressedString, 1100+XCalib, 476+YCalib);
    ofSetColor(0);
    ofDrawBitmapString("Eradication Cadre", 1100+XCalib, 500+YCalib); /*transformer ce texte en bouton*/
    ofSetColor(255);
    ofDrawBitmapString("Details Eradication :", 1100+XCalib, 530+YCalib);
    ofDrawBitmapString(EradicationCadre, 1100+XCalib, 542+YCalib);
    ofDrawBitmapString(EradicationCycle, 1150+XCalib, 542+YCalib);
    ofSetColor(0);
    ofDrawBitmapString("Eradication Totale", 1100+XCalib, 580+YCalib);
    ofDrawBitmapString("Reset", 1102+XCalib, 615+YCalib);
    ofSetColor(255);
    ofDrawBitmapString("Buron Nathan", 1150+XCalib, 760+YCalib);
    ofDrawBitmapString("Mercier Pierre", 1150+XCalib, 780+YCalib);
    /*ICI, parcours des listes pour le dessin des crŽatures*/
    
    /*test affichage 20/20*/
    ofSetColor(255);
    drawCreatures();

        
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    /*Finition du quadrillage*/
    ofSetColor(0);
    if(Quadri){
    ofRect(365+XCalib,15+YCalib,5,820);
    ofRect(720+XCalib,15+YCalib,5,820);
    ofRect(15+XCalib,415+YCalib,1075,5);
    }
    ofRect(1075+XCalib,15+YCalib,DimensionEspece+5,820+DimensionEspece+5);
    ofRect(15+XCalib,820+YCalib,1075+DimensionEspece+5,DimensionEspece+5);
    
    if(deadWorld){
        ofSetColor(150,0,0);
        endOfWorld.drawString("Fin Du Monde", 300, 400);
    }
    ofDisableBlendMode();
}

//--------------------------------------------------------------
void testApp::populate(){ /*mŽthode populate initial du tableau -> pose le contexte*/
    /*creature(x,y,pred,dep,rep,type)*/
    creature locCreature;
    int randomNumberx=0;
    int randomNumbery=0;
    
    for(int i =0; i<nbrHerbInit;i++){
        randomNumberx=rand()%(1075-15)+15;
        randomNumbery=rand()%(820-15)+15;
        locCreature = creature(randomNumberx+XCalib,randomNumbery+YCalib, 1, DeplacementHerb, Reproductionherb, 'h',7);
        herbivors.push_back(locCreature);
    }
    
    for(int i =0; i<nbrPredInit;i++){
        randomNumberx=rand()%(1075-15)+15;
        randomNumbery=rand()%(820-15)+15;
        locCreature = creature(randomNumberx+XCalib,randomNumbery+YCalib, 3, DeplacementPred, ReproductionPred, 'p',7);
        predators.push_back(locCreature);
    }
    
    for(int i =0; i<nbrVegInit;i++){
        randomNumberx=rand()%(1075-15)+15;
        randomNumbery=rand()%(820-15)+15;
        locCreature = creature(randomNumberx+XCalib,randomNumbery+YCalib, 0, 0, ReproductionVeg, 'v',10);
        vegetals.push_back(locCreature);
    }
    

}

void testApp::drawCreatures(){
    
    /*
     OF_BLENDMODE_ALPHA
     OF_BLENDMODE_ADD
     OF_BLENDMODE_DISABLED
     OF_BLENDMODE_MULTIPLY
     OF_BLENDMODE_SCREEN
     OF_BLENDMODE_SUBTRACT
     */
    
    /*Ici, la gestion des Blend pour la "clignotement" des crŽatures*/
    int randomNumber=0;
    
    std::list<creature>::iterator iteratorvege =vegetals.begin();
    if(!vegetals.empty()){
        while(iteratorvege!=vegetals.end()){
        randomNumber=rand();
        if(randomNumber%DivClign==0){
        blendMode = OF_BLENDMODE_ADD;
        }else{
        blendMode = OF_BLENDMODE_ALPHA;
        }
        ofEnableBlendMode(blendMode);
            
        vegetalImage.draw(iteratorvege->x, iteratorvege->y);
            iteratorvege++;
            }
    }
    
    std::list<creature>::iterator iteratorherbi =herbivors.begin();
    if(!herbivors.empty()){
    while(iteratorherbi!=herbivors.end()){
       randomNumber=rand();
        if(randomNumber%DivClign==0){
            blendMode =  OF_BLENDMODE_ALPHA;
        }else{
            blendMode =  OF_BLENDMODE_ADD;
        }
        ofEnableBlendMode(blendMode);
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        herbivorImage.draw(iteratorherbi->x, iteratorherbi->y);
        iteratorherbi++;
       
    }
    }
    
    std::list<creature>::iterator iteratorpreda =predators.begin();
    if(!predators.empty()){
        while(iteratorpreda!=predators.end()){
        randomNumber=rand();
        if(randomNumber%DivClign==0){
            blendMode =  OF_BLENDMODE_SUBTRACT;
        }else{
            blendMode = OF_BLENDMODE_ALPHA;
        }
        ofEnableBlendMode(blendMode);
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        predatorImage.draw(iteratorpreda->x, iteratorpreda->y);
            iteratorpreda++;
    }
    }
    
    std::list<creature>::iterator iteratorinva =invasives.begin();
    if(!invasives.empty()){
        while(iteratorinva!=invasives.end()){
            randomNumber=rand();
            if(randomNumber%DivClign==0){
                blendMode = OF_BLENDMODE_ADD;
            }else{
                blendMode = OF_BLENDMODE_ALPHA;
            }
            ofEnableBlendMode(blendMode);
            
            invasiveImage.draw(iteratorinva->x, iteratorinva->y);
            iteratorinva++;
        }
    }

}

void testApp::vieGlobal(){
    float countPredatorsGlobal=0;
    float countPredatorsA1=0;
    float countPredatorsA2=0;
    float countPredatorsA3=0;
    float countPredatorsB1=0;
    float countPredatorsB2=0;
    float countPredatorsB3=0;
    float countHerbivorsGlobal=0;
    float countHerbivorsA1=0;
    float countHerbivorsA2=0;
    float countHerbivorsA3=0;
    float countHerbivorsB1=0;
    float countHerbivorsB2=0;
    float countHerbivorsB3=0;
    float countVegetalsGlobal=0;
    float countVegetalsA1=0;
    float countVegetalsA2=0;
    float countVegetalsA3=0;
    float countVegetalsB1=0;
    float countVegetalsB2=0;
    float countVegetalsB3=0;
    float countInvasivesGlobal=0;
    float countInvasivesA1=0;
    float countInvasivesA2=0;
    float countInvasivesA3=0;
    float countInvasivesB1=0;
    float countInvasivesB2=0;
    float countInvasivesB3=0;

    
    creature locCreature;
    int randomNumberRep=0;
    int randomNumberx=0;
    int randomNumbery=0;
    int randomNumberSigne=0;
    
    /*************************************************************************************/

    
    /*Gestion des Predators*/
    std::list<creature>::iterator iteratorpred =predators.begin();
    if(!predators.empty()){
        while(iteratorpred!=predators.end()){
            
              
            //les Predators mangent les Herbivors
            
            int xBestPrey=10000; //valeur de base trs grande pour trouver plus petit = plus proche
            int yBestPrey=10000;
            if(iteratorpred->energie<8){//ne cherche ˆ manger que si Žnergie <8
            std::list<creature>::iterator iteratorherbeated =herbivors.begin();
            if(!herbivors.empty()){
                while(iteratorherbeated!=herbivors.end()){
                    
                    if(abs(iteratorherbeated->x-iteratorpred->x)<DimensionEspece+PorteeAttaquePred && abs(iteratorherbeated->y-iteratorpred->y)<DimensionEspece+PorteeAttaquePred){
                        iteratorpred->energie=10;
                        herbivors.erase(iteratorherbeated);
                        countHerb--;
                        
                    }
                    
                    //Ici on recherche des proies dans la ligne de vue et on sŽlectionne le plus proche afin d'envoyer sa position ˆ la fonction de dŽplacement
                    if(abs(iteratorherbeated->x-iteratorpred->x)<DimensionEspece+VisibilitePred && abs(iteratorherbeated->y-iteratorpred->y)<DimensionEspece+VisibilitePred){ //ˆ portŽe
                        
                        double distanceToPreyChose=pow((double)(xBestPrey-iteratorpred->x),(double)2)+pow((double)(yBestPrey-iteratorpred->y),(double)2);//hypothŽnus^2
                        double distanceToPreyTested=pow((double)(iteratorherbeated->x-iteratorpred->x),(double)2)+pow((double)(iteratorherbeated->y-iteratorpred->y),(double)2);
                        
                        if(distanceToPreyTested<distanceToPreyChose){ //plus proche
                            xBestPrey=iteratorherbeated->x;
                            yBestPrey=iteratorherbeated->y;
                        }

                        
                    }

                    iteratorherbeated++;
                }
            }
            }

        //dŽplacement
        iteratorpred->deplacementCreature(15+XCalib,1075+XCalib,15+YCalib,820+YCalib,xBestPrey,yBestPrey);
        
            //reproduction
            int randomNumberRep=0;
            randomNumberRep=rand()%(DivReprodPred);
        if(iteratorpred->energie>8 && randomNumberRep%DivReprodPred==0 && countPred<nbrPredMax){
            for(int i=0;i<iteratorpred->reproduction;i++){
                locCreature = creature(iteratorpred->x,iteratorpred->y, 3, DeplacementPred, ReproductionPred, 'p',5);
                predators.push_front(locCreature);
                countPred++;
            }
        }
        
           
        
        //rŽcupŽration des donnŽes pour calcul statistique
        if(iteratorpred->x>15+XCalib && iteratorpred->x<365+XCalib && iteratorpred->y>15+YCalib && iteratorpred->y<415+YCalib){
            countPredatorsA1++;
            countPredatorsGlobal++;
        }else if(iteratorpred->x>370+XCalib && iteratorpred->x<720+XCalib && iteratorpred->y>15+YCalib && iteratorpred->y<415+YCalib){
            countPredatorsA2++;
            countPredatorsGlobal++;
        }else if(iteratorpred->x>725+XCalib && iteratorpred->x<1075+XCalib && iteratorpred->y>15+YCalib && iteratorpred->y<415+YCalib){
            countPredatorsA3++;
            countPredatorsGlobal++;
        }else if(iteratorpred->x>15+XCalib && iteratorpred->x<365+XCalib && iteratorpred->y>420+YCalib && iteratorpred->y<820+YCalib){
            countPredatorsB1++;
            countPredatorsGlobal++;
        }else if(iteratorpred->x>370+XCalib && iteratorpred->x<720+XCalib && iteratorpred->y>420+YCalib && iteratorpred->y<820+YCalib){
            countPredatorsB2++;
            countPredatorsGlobal++;
        }else if(iteratorpred->x>725+XCalib && iteratorpred->x<1075+XCalib && iteratorpred->y>420+YCalib && iteratorpred->y<820+YCalib){
            countPredatorsB3++;
            countPredatorsGlobal++;
        }
            
            //perte d'Žnergie
            int randomNumberPerteEnergie=0;
            randomNumberPerteEnergie=rand()%(DivPerteEnergiePred);
            if(randomNumberPerteEnergie%DivPerteEnergiePred==0){
                iteratorpred->energie--;
            }
            //energie 0 = mort
            if(iteratorpred->energie<1){
                predators.erase(iteratorpred);
                countPred--;
                
            }
        
            iteratorpred++;
        }
    }
    /*Fin gestion des Predators*/
    
    /*************************************************************************************/
    
    
    /*Gestion des Invasives*/
    
    std::list<creature>::iterator iteratorinv =invasives.begin();
    if(!invasives.empty()){
        while(iteratorinv!=invasives.end()){
                        
            //les Invasives mangent les Vegetals
            int xBestPrey=10000;
            int yBestPrey=10000;
            if(iteratorinv->energie<8){// ne cherche ˆ manger que si energie <8
                std::list<creature>::iterator iteratorvegeatedbyinva =vegetals.begin();
                if(!vegetals.empty()){
                    while(iteratorvegeatedbyinva!=vegetals.end()){
                        
                        if(abs(iteratorvegeatedbyinva->x-iteratorinv->x)<DimensionEspece+PorteeAttaqueInva && abs(iteratorvegeatedbyinva->y-iteratorinv->y)<DimensionEspece+PorteeAttaqueInva){
                            iteratorinv->energie=10;
                            vegetals.erase(iteratorvegeatedbyinva);
                            countVeg--;
                        }
                        
                        //Ici on recherche des proies dans la ligne de vue et on sŽlectionne le plus proche afin d'envoyer sa position ˆ la fonction de dŽplacement
                        if(abs(iteratorvegeatedbyinva->x-iteratorinv->x)<DimensionEspece+VisibiliteInva && abs(iteratorvegeatedbyinva->y-iteratorinv->y)<DimensionEspece+VisibiliteInva){ //ˆ portŽe
                            
                            double distanceToPreyChose=pow((double)(xBestPrey-iteratorinv->x),(double)2)+pow((double)(yBestPrey-iteratorinv->y),(double)2);//hypothŽnus^2
                            double distanceToPreyTested=pow((double)(iteratorinv->x-iteratorvegeatedbyinva->x),(double)2)+pow((double)(iteratorinv->y-iteratorvegeatedbyinva->y),(double)2);
                            
                            if(distanceToPreyTested<distanceToPreyChose){ //plus proche
                                xBestPrey=iteratorvegeatedbyinva->x;
                                yBestPrey=iteratorvegeatedbyinva->y;
                            }
                        }
                        iteratorvegeatedbyinva++;
                    }
                }
            }
            
            
            //dŽplacement
            iteratorinv->deplacementCreature(15+XCalib,1075+XCalib,15+YCalib,820+YCalib,xBestPrey,yBestPrey);
            
            //reproduction
            int randomNumberRep=0;
            randomNumberRep=rand()%(DivReprodInva);
            if(iteratorinv->energie>8 && randomNumberRep%DivReprodInva==0 && countInva<nbrInvaMax){
                
                for(int i=0;i<iteratorinv->reproduction;i++){
                    locCreature = creature(iteratorinv->x,iteratorinv->y, 2, DeplacementInva, ReproductionInva, 'i',5);
                    invasives.push_front(locCreature);
                    countInva++;
                }
            }
            
           

            
            //rŽcupŽration des donnŽes pour calcul statistique
            if(iteratorinv->x>15+XCalib && iteratorinv->x<365+XCalib && iteratorinv->y>15+YCalib && iteratorinv->y<415+YCalib){
                countInvasivesA1++;
                countInvasivesGlobal++;
            }else if(iteratorinv->x>370+XCalib && iteratorinv->x<720+XCalib && iteratorinv->y>15+YCalib && iteratorinv->y<415+YCalib){
                countInvasivesA2++;
                countInvasivesGlobal++;
            }else if(iteratorinv->x>725+XCalib && iteratorinv->x<1075+XCalib && iteratorinv->y>15+YCalib && iteratorinv->y<415+YCalib){
                countInvasivesA3++;
                countInvasivesGlobal++;
            }else if(iteratorinv->x>15+XCalib && iteratorinv->x<365+XCalib && iteratorinv->y>420+YCalib && iteratorinv->y<820+YCalib){
                countInvasivesB1++;
                countInvasivesGlobal++;
            }else if(iteratorinv->x>370+XCalib && iteratorinv->x<720+XCalib && iteratorinv->y>420+YCalib && iteratorinv->y<820+YCalib){
                countInvasivesB2++;
                countInvasivesGlobal++;
            }else if(iteratorinv->x>725+XCalib && iteratorinv->x<1075+XCalib && iteratorinv->y>420+YCalib && iteratorinv->y<820+YCalib){
                countInvasivesB3++;
                countInvasivesGlobal++;
            }
            
            //perte d'Žnergie
            int randomNumberPerteEnergie=0;
            randomNumberPerteEnergie=rand()%(DivPerteEnergieInva);
            if(randomNumberPerteEnergie%DivPerteEnergieInva==0){
                iteratorinv->energie--;
            }
            if(iteratorinv->energie<1){
                invasives.erase(iteratorinv);
                countInva--;
            }
            
            iteratorinv++;
        }
    }
    

    /*Fin gestion des Invasives*/
    
    
    /*************************************************************************************/

    
    /*Gestion des herbivors*/
    std::list<creature>::iterator iteratorherb =herbivors.begin();
    if(!herbivors.empty()){
        while(iteratorherb!=herbivors.end()){
       
                       
            //les Herbivors mangent les Vegetals
            int xBestPrey=10000;
            int yBestPrey=10000;
            if(iteratorherb->energie<8){// ne cherche ˆ manger que si energie <8
            std::list<creature>::iterator iteratorvegeated =vegetals.begin();
            if(!vegetals.empty()){
                while(iteratorvegeated!=vegetals.end()){
                    
                    if(abs(iteratorvegeated->x-iteratorherb->x)<DimensionEspece+PorteeAttaqueHerb && abs(iteratorvegeated->y-iteratorherb->y)<DimensionEspece+PorteeAttaqueHerb){
                        iteratorherb->energie=10;
                        vegetals.erase(iteratorvegeated);
                        countVeg--;
                    }

                    //Ici on recherche des proies dans la ligne de vue et on sŽlectionne le plus proche afin d'envoyer sa position ˆ la fonction de dŽplacement
                    if(abs(iteratorvegeated->x-iteratorherb->x)<DimensionEspece+VisibiliteHerb && abs(iteratorvegeated->y-iteratorherb->y)<DimensionEspece+VisibiliteHerb){ //ˆ portŽe
                        
                        double distanceToPreyChose=pow((double)(xBestPrey-iteratorherb->x),(double)2)+pow((double)(yBestPrey-iteratorherb->y),(double)2);//hypothŽnus^2
                        double distanceToPreyTested=pow((double)(iteratorherb->x-iteratorvegeated->x),(double)2)+pow((double)(iteratorherb->y-iteratorvegeated->y),(double)2);
                        
                        if(distanceToPreyTested<distanceToPreyChose){ //plus proche
                            xBestPrey=iteratorvegeated->x;
                            yBestPrey=iteratorvegeated->y;
                        }
                    }
                    iteratorvegeated++;
                }
            }
            }

        
        //dŽplacement
        iteratorherb->deplacementCreature(15+XCalib,1075+XCalib,15+YCalib,820+YCalib,xBestPrey,yBestPrey);
        
        //reproduction
            int randomNumberRep=0;
            randomNumberRep=rand()%(DivReprodHerb);
        if(iteratorherb->energie>8 && randomNumberRep%DivReprodHerb==0 && countHerb<nbrHerbMax){
            
            for(int i=0;i<iteratorherb->reproduction;i++){
            locCreature = creature(iteratorherb->x,iteratorherb->y, 1, DeplacementHerb, Reproductionherb, 'h',5);
            herbivors.push_front(locCreature);
                countHerb++;
            }
        }
        
        
        
        //rŽcupŽration des donnŽes pour calcul statistique
        if(iteratorherb->x>15+XCalib && iteratorherb->x<365+XCalib && iteratorherb->y>15+YCalib && iteratorherb->y<415+YCalib){
            countHerbivorsA1++;
            countHerbivorsGlobal++;
        }else if(iteratorherb->x>370+XCalib && iteratorherb->x<720+XCalib && iteratorherb->y>15+YCalib && iteratorherb->y<415+YCalib){
            countHerbivorsA2++;
            countHerbivorsGlobal++;
        }else if(iteratorherb->x>725+XCalib && iteratorherb->x<1075+XCalib && iteratorherb->y>15+YCalib && iteratorherb->y<415+YCalib){
            countHerbivorsA3++;
            countHerbivorsGlobal++;
        }else if(iteratorherb->x>15+XCalib && iteratorherb->x<365+XCalib && iteratorherb->y>420+YCalib && iteratorherb->y<820+YCalib){
            countHerbivorsB1++;
            countHerbivorsGlobal++;
        }else if(iteratorherb->x>370+XCalib && iteratorherb->x<720+XCalib && iteratorherb->y>420+YCalib && iteratorherb->y<820+YCalib){
            countHerbivorsB2++;
            countHerbivorsGlobal++;
        }else if(iteratorherb->x>725+XCalib && iteratorherb->x<1075+XCalib && iteratorherb->y>420+YCalib && iteratorherb->y<820+YCalib){
            countHerbivorsB3++;
            countHerbivorsGlobal++;
        }
            
            //perte d'Žnergie
            int randomNumberPerteEnergie=0;
            randomNumberPerteEnergie=rand()%(DivPerteEnergieHerb);
            if(randomNumberPerteEnergie%DivPerteEnergieHerb==0){
                iteratorherb->energie--;
            }
            if(iteratorherb->energie<1){
                herbivors.erase(iteratorherb);
                countHerb--;
            }

            iteratorherb++;
            }
    }
    /*Fin gestion des herbivors*/
    
    
    
    /*************************************************************************************/

    

    
    /*Gestion des Vegetals*/
    std::list<creature>::iterator iteratorveg =vegetals.begin();
    if(!vegetals.empty()){
        while(iteratorveg!=vegetals.end()){
            
            //reproduction
            int randomNumberRep=0;
            randomNumberRep=rand()%(DivReprodVeg);
            if(randomNumberRep%DivReprodVeg==0 && countVeg<nbrVegMax){
    for(int i=0;i<iteratorveg->reproduction;i++){
            //on gŽnre des nombres compris entre -50 et +50
            randomNumberSigne=rand()%(2);
            if(randomNumberSigne==0){
                randomNumberx=(rand()%(50))*(-1);
            }else{
                randomNumberx=rand()%(50);
            }
            randomNumberSigne=rand()%(2);
            if(randomNumberSigne==0){
                randomNumbery=(rand()%(50))*(-1);
            }else{
                randomNumbery=rand()%(50);
            }
            
            if(iteratorveg->x+randomNumberx>15+XCalib && iteratorveg->x+randomNumberx<1075 && iteratorveg->y+randomNumbery>15+YCalib  && iteratorveg->y+randomNumbery<820+YCalib){
    locCreature = creature(iteratorveg->x+randomNumberx,iteratorveg->y+randomNumbery, 0, 0, ReproductionVeg, 'v',10);
    vegetals.push_front(locCreature);
            countVeg++;
            }
        }
        
    }
            //crŽation d'un vegetal de manire alŽatoire pour augmenter leur dispersion
            int randomNumberVegGeneration=0;
            randomNumberVegGeneration=rand()%(DivAleaVegGeneration);
            if(randomNumberVegGeneration%DivAleaVegGeneration==0 && !vegetals.empty() && BoolAleaVegGeneration){
                int randomNumberx=rand()%(1075-15)+15;
                int randomNumbery=rand()%(820-15)+15;
                locCreature = creature(randomNumberx+XCalib,randomNumbery+YCalib, 0, 0, ReproductionVeg, 'v',10);
                vegetals.push_front(locCreature);
                countVeg++;
            }
        
        //rŽcupŽration des donnŽes pour calcul statistique
        if(iteratorveg->x>15+XCalib && iteratorveg->x<365+XCalib && iteratorveg->y>15+YCalib && iteratorveg->y<415+YCalib){
            countVegetalsA1++;
            countVegetalsGlobal++;
        }else if(iteratorveg->x>370+XCalib && iteratorveg->x<720+XCalib && iteratorveg->y>15+YCalib && iteratorveg->y<415+YCalib){
            countVegetalsA2++;
            countVegetalsGlobal++;
        }else if(iteratorveg->x>725+XCalib && iteratorveg->x<1075+XCalib && iteratorveg->y>15+YCalib && iteratorveg->y<415+YCalib){
            countVegetalsA3++;
            countVegetalsGlobal++;
        }else if(iteratorveg->x>15+XCalib && iteratorveg->x<365+XCalib && iteratorveg->y>420+YCalib && iteratorveg->y<820+YCalib){
            countVegetalsB1++;
            countVegetalsGlobal++;
        }else if(iteratorveg->x>370+XCalib && iteratorveg->x<720+XCalib && iteratorveg->y>420+YCalib && iteratorveg->y<820+YCalib){
            countVegetalsB2++;
            countVegetalsGlobal++;
        }else if(iteratorveg->x>725+XCalib && iteratorveg->x<1075+XCalib && iteratorveg->y>420+YCalib && iteratorveg->y<820+YCalib){
            countVegetalsB3++;
            countVegetalsGlobal++;
        }
            iteratorveg++;
        }
}
    /*Fin gestion des Vegetals*/
    
    
    /*Calculs statistiques*/
    sprintf(percentHerbivorsGlobalString,"Herbivores : %.1f%%",(countHerbivorsGlobal/(countHerbivorsGlobal+countPredatorsGlobal+countVegetalsGlobal+countInvasivesGlobal))*100);
    sprintf(percentPredatorsGlobalString,"Predateurs : %.1f%%",(countPredatorsGlobal/(countHerbivorsGlobal+countPredatorsGlobal+countVegetalsGlobal+countInvasivesGlobal))*100);
    sprintf(percentVegetalsGlobalString,"Vegetaux : %.1f%%",(countVegetalsGlobal/(countHerbivorsGlobal+countPredatorsGlobal+countVegetalsGlobal+countInvasivesGlobal))*100);
    sprintf(percentInvasivesGlobalString,"%.1f%%",(countInvasivesGlobal/(countHerbivorsGlobal+countPredatorsGlobal+countVegetalsGlobal+countInvasivesGlobal))*100);
    //rŽcupŽration des donnŽes pour calcul statistique
    if(mouseX>15+XCalib && mouseX<365+XCalib && mouseY>15+YCalib && mouseY<415+YCalib){
        sprintf(percentHerbivorsZoneString,"Herbivores : %.1f%%",(countHerbivorsA1/(countHerbivorsA1+countPredatorsA1+countVegetalsA1+countInvasivesA1))*100);
        sprintf(percentPredatorsZoneString,"Predateurs : %.1f%%",(countPredatorsA1/(countHerbivorsA1+countPredatorsA1+countVegetalsA1+countInvasivesA1))*100);
        sprintf(percentVegetalsZoneString,"Vegetaux : %.1f%%",(countVegetalsA1/(countHerbivorsA1+countPredatorsA1+countVegetalsA1+countInvasivesA1))*100);
        sprintf(percentInvasivesZoneString,"%.1f%%",(countInvasivesA1/(countHerbivorsA1+countPredatorsA1+countVegetalsA1+countInvasivesA1))*100);
    }else if(mouseX>370+XCalib && mouseX<720+XCalib && mouseY>15+YCalib && mouseY<415+YCalib){
        sprintf(percentHerbivorsZoneString,"Herbivores : %.1f%%",(countHerbivorsA2/(countHerbivorsA2+countPredatorsA2+countVegetalsA2+countInvasivesA2))*100);
        sprintf(percentPredatorsZoneString,"Predateurs : %.1f%%",(countPredatorsA2/(countHerbivorsA2+countPredatorsA2+countVegetalsA2+countInvasivesA2))*100);
        sprintf(percentVegetalsZoneString,"Vegetaux : %.1f%%",(countVegetalsA2/(countHerbivorsA2+countPredatorsA2+countVegetalsA2+countInvasivesA2))*100);
        sprintf(percentInvasivesZoneString,"%.1f%%",(countInvasivesA2/(countHerbivorsA2+countPredatorsA2+countVegetalsA2+countInvasivesA2))*100);
    }else if(mouseX>725+XCalib && mouseX<1075+XCalib && mouseY>15+YCalib && mouseY<415+YCalib){
        sprintf(percentHerbivorsZoneString,"Herbivores : %.1f%%",(countHerbivorsA3/(countHerbivorsA3+countPredatorsA3+countVegetalsA3+countInvasivesA3))*100);
        sprintf(percentPredatorsZoneString,"Predateurs : %.1f%%",(countPredatorsA3/(countHerbivorsA3+countPredatorsA3+countVegetalsA3+countInvasivesA3))*100);
        sprintf(percentVegetalsZoneString,"Vegetaux : %.1f%%",(countVegetalsA3/(countHerbivorsA3+countPredatorsA3+countVegetalsA3+countInvasivesA3))*100);
        sprintf(percentInvasivesZoneString,"%.1f%%",(countInvasivesA3/(countHerbivorsA3+countPredatorsA3+countVegetalsA3+countInvasivesA3))*100);
    }else if(mouseX>15+XCalib && mouseX<365+XCalib && mouseY>420+YCalib && mouseY<820+YCalib){
        sprintf(percentHerbivorsZoneString,"Herbivores : %.1f%%",(countHerbivorsB1/(countHerbivorsB1+countPredatorsB1+countVegetalsB1+countInvasivesB1))*100);
        sprintf(percentPredatorsZoneString,"Predateurs : %.1f%%",(countPredatorsB1/(countHerbivorsB1+countPredatorsB1+countVegetalsB1+countInvasivesB1))*100);
        sprintf(percentVegetalsZoneString,"Vegetaux : %.1f%%",(countVegetalsB1/(countHerbivorsB1+countPredatorsB1+countVegetalsB1+countInvasivesB1))*100);
        sprintf(percentInvasivesZoneString,"%.1f%%",(countInvasivesB1/(countHerbivorsB1+countPredatorsB1+countVegetalsB1+countInvasivesB1))*100);
    }else if(mouseX>370+XCalib && mouseX<720+XCalib && mouseY>420+YCalib && mouseY<820+YCalib){
        sprintf(percentHerbivorsZoneString,"Herbivores : %.1f%%",(countHerbivorsB2/(countHerbivorsB2+countPredatorsB2+countVegetalsB2+countInvasivesB2))*100);
        sprintf(percentPredatorsZoneString,"Predateurs : %.1f%%",(countPredatorsB2/(countHerbivorsB2+countPredatorsB2+countVegetalsB2+countInvasivesB2))*100);
        sprintf(percentVegetalsZoneString,"Vegetaux : %.1f%%",(countVegetalsB2/(countHerbivorsB2+countPredatorsB2+countVegetalsB2+countInvasivesB2))*100);
        sprintf(percentInvasivesZoneString,"%.1f%%",(countInvasivesB2/(countHerbivorsB2+countPredatorsB2+countVegetalsB2+countInvasivesB2))*100);
    }else if(mouseX>725+XCalib && mouseX<1075+XCalib && mouseY>420+YCalib && mouseY<820+YCalib){
        sprintf(percentHerbivorsZoneString,"Herbivores : %.1f%%",(countHerbivorsB3/(countHerbivorsB3+countPredatorsB3+countVegetalsB3+countInvasivesB3))*100);
        sprintf(percentPredatorsZoneString,"Predateurs : %.1f%%",(countPredatorsB3/(countHerbivorsB3+countPredatorsB3+countVegetalsB3+countInvasivesB3))*100);
        sprintf(percentVegetalsZoneString,"Vegetaux : %.1f%%",(countVegetalsB3/(countHerbivorsB3+countPredatorsB3+countVegetalsB3+countInvasivesB3))*100);
        sprintf(percentInvasivesZoneString,"%.1f%%",(countInvasivesB3/(countHerbivorsB3+countPredatorsB3+countVegetalsB3+countInvasivesB3))*100);
    }else{
        sprintf(percentHerbivorsZoneString, "Herbivores : 0.0%%");
        sprintf(percentPredatorsZoneString, "Predateurs : 0.0%%");
        sprintf(percentVegetalsZoneString, "Vegetaux : 0.0%%");
        sprintf(percentInvasivesZoneString, "0.0%%");
    }
    
    //monde mort?
    if(countHerbivorsGlobal+countPredatorsGlobal+countVegetalsGlobal+countInvasivesGlobal==0){
        deadWorld=true;
    }else{
      deadWorld=false;
}
    /*Fin calculs statistiques*/
}

void testApp::InvaInsertion(){
    if(xForInsertion!=0 && yForInsertion!=0 && countInva<nbrInvaMax){
        creature locCreature;
    sprintf(InsertionCycle,"/ Cycle : %i",countCycle);
    sprintf(InsertionCadre, cadrePressedString);
        for(int i=0;i<=nbrInvaByInsertion ; i++){
            locCreature = creature(xForInsertion,yForInsertion, 2, DeplacementInva, ReproductionInva, 'i',5);
            invasives.push_front(locCreature);
            countInva++;
        }
    }
}

void testApp::InvaEradicationCadre(){
    if (strncmp(cadrePressedString,"A1",2)==0){
        std::list<creature>::iterator iteratorinv =invasives.begin();
        if(!invasives.empty()){
            while(iteratorinv!=invasives.end()){
                if(15<iteratorinv->x && iteratorinv->x<365 && 15<iteratorinv->y && iteratorinv->y<415){
                    invasives.erase(iteratorinv);
                    countInva--;
                    sprintf(EradicationCycle,"/ Cycle : %i",countCycle);
                    sprintf(EradicationCadre, "A1");
                }
                iteratorinv++;
            }
        }
    }else if (!strncmp(cadrePressedString,"A2",2)){
        std::list<creature>::iterator iteratorinv =invasives.begin();
        if(!invasives.empty()){
            while(iteratorinv!=invasives.end()){
                if(370<iteratorinv->x && iteratorinv->x<720 && 15<iteratorinv->y && iteratorinv->y<415){
                    invasives.erase(iteratorinv);
                    countInva--;
                    sprintf(EradicationCycle,"/ Cycle : %i",countCycle);
                    sprintf(EradicationCadre, "A2");
                }
                iteratorinv++;
            }
        }

    }else if (!strncmp(cadrePressedString,"A3",2)){
        std::list<creature>::iterator iteratorinv =invasives.begin();
        if(!invasives.empty()){
            while(iteratorinv!=invasives.end()){
                if(725<iteratorinv->x && iteratorinv->x<1075 && 15<iteratorinv->y && iteratorinv->y<415){
                    invasives.erase(iteratorinv);
                    countInva--;
                    sprintf(EradicationCycle,"/ Cycle : %i",countCycle);
                    sprintf(EradicationCadre, "A3");
                }
                iteratorinv++;
            }
        }

    }else if (!strncmp(cadrePressedString,"B1",2)){
        std::list<creature>::iterator iteratorinv =invasives.begin();
        if(!invasives.empty()){
            while(iteratorinv!=invasives.end()){
                if(15<iteratorinv->x && iteratorinv->x<365 && 420<iteratorinv->y && iteratorinv->y<820){
                    invasives.erase(iteratorinv);
                    countInva--;
                    sprintf(EradicationCycle,"/ Cycle : %i",countCycle);
                    sprintf(EradicationCadre, "B1");
                }
                iteratorinv++;
            }
        }

    }else if (!strncmp(cadrePressedString,"B2",2)){
        std::list<creature>::iterator iteratorinv =invasives.begin();
        if(!invasives.empty()){
            while(iteratorinv!=invasives.end()){
                if(370<iteratorinv->x && iteratorinv->x<720 && 420<iteratorinv->y && iteratorinv->y<820){
                    invasives.erase(iteratorinv);
                    countInva--;
                    sprintf(EradicationCycle,"/ Cycle : %i",countCycle);
                    sprintf(EradicationCadre, "B2");
                }
                iteratorinv++;
            }
        }

    }else if (!strncmp(cadrePressedString,"B3",2)){
        std::list<creature>::iterator iteratorinv =invasives.begin();
        if(!invasives.empty()){
            while(iteratorinv!=invasives.end()){
                if(725<iteratorinv->x && iteratorinv->x<1075 && 420<iteratorinv->y && iteratorinv->y<820){
                    invasives.erase(iteratorinv);
                    countInva--;
                    sprintf(EradicationCycle,"/ Cycle : %i",countCycle);
                    sprintf(EradicationCadre, "B3");
                }
                iteratorinv++;
            }
        }
    }
}

void testApp::InvaEradicationTotale(){
    if(!invasives.empty()){
    invasives.clear();
    countInva=0;
    sprintf(EradicationCycle,"/ Cycle : %i",countCycle);
    sprintf(EradicationCadre, "Totale");
    }
}

void testApp::Reset(){
    invasives.clear();
    countInva=0;
    predators.clear();
    countPred=0;
    herbivors.clear();
    countHerb=0;
    vegetals.clear();
    countVeg=0;
    countCycle=0;
    populate();
    deadWorld=false;
    
}

void testApp::ReadConfig(){
    
    configFile.open("lfConfig.xml");
    configBuffer = configFile.readToBuffer();
    if(configXml.loadFromBuffer(configBuffer.getText())){

    configXml.setTo("LifeGame");

    configXml.setTo("Setups");
    BackgroundActif=configXml.getBoolValue("Background");
    XCalib=configXml.getIntValue("Calib/XCalib");
    YCalib=configXml.getIntValue("Calib/YCalib");
    Quadri=configXml.getBoolValue("Quadrillage");
    DimensionEspece=configXml.getIntValue("DimCrea");
    DivCycle=configXml.getIntValue("DivCycle");
    endOfWorld.loadFont(configXml.getValue("Images/Font"),50);
    backgroundImage.allocate(1075, 820, OF_IMAGE_COLOR_ALPHA);
    backgroundImage.loadImage(configXml.getValue("Images/Background"));
        
    configXml.setToParent();
    
    configXml.setTo("Creatures/Global");
    DivDeplacement=configXml.getIntValue("DivMouve");
    DivClign=configXml.getIntValue("DivBend");
    
    configXml.setToParent();
        
    configXml.setTo("Creature[@type=Predator]");
    predatorImage.allocate(20, 20, OF_IMAGE_COLOR_ALPHA);
    predatorImage.loadImage(configXml.getValue("Skin"));
    nbrPredInit=configXml.getIntValue("Regulation/Init");
    nbrPredMax=configXml.getIntValue("Regulation/Max");
    DeplacementPred=configXml.getIntValue("Skills/Speed");
    VisibilitePred=configXml.getIntValue("Skills/Eyesight");
    PorteeAttaquePred=configXml.getIntValue("Skills/Range");
    DivPerteEnergiePred=configXml.getIntValue("Skills/Endurance");
    ReproductionPred=configXml.getIntValue("Skills/Reproduction/ByReprod");
    DivReprodPred=configXml.getIntValue("Skills/Reproduction/Div");
    
    configXml.setToParent();
    
    configXml.setTo("Creature[@type=Herbivor]");
    herbivorImage.allocate(20, 20, OF_IMAGE_COLOR_ALPHA);
    herbivorImage.loadImage(configXml.getValue("Skin"));
    nbrHerbInit=configXml.getIntValue("Regulation/Init");
    nbrHerbMax=configXml.getIntValue("Regulation/Max");
    DeplacementHerb=configXml.getIntValue("Skills/Speed");
    VisibiliteHerb=configXml.getIntValue("Skills/Eyesight");
    PorteeAttaqueHerb=configXml.getIntValue("Skills/Range");
    DivPerteEnergieHerb=configXml.getIntValue("Skills/Endurance");
    Reproductionherb=configXml.getIntValue("Skills/Reproduction/ByReprod");
    DivReprodHerb=configXml.getIntValue("Skills/Reproduction/Div");
     
    configXml.setToParent();
        
    configXml.setTo("Creature[@type=Vegetal]");
    vegetalImage.allocate(20, 20, OF_IMAGE_COLOR_ALPHA);
    vegetalImage.loadImage(configXml.getValue("Skin"));
    nbrVegInit=configXml.getIntValue("Regulation/Init");
    nbrVegMax=configXml.getIntValue("Regulation/Max");
    BoolAleaVegGeneration=configXml.getBoolValue("Regulation/AleaApparition/Activated");
    DivAleaVegGeneration=configXml.getIntValue("Regulation/AleaApparition/Div");
    ReproductionVeg=configXml.getIntValue("Skills/Reproduction/ByReprod");
    DivReprodVeg=configXml.getIntValue("Skills/Reproduction/Div");
    
    configXml.setToParent();
        
    configXml.setTo("Creature[@type=Invasive]");
    invasiveImage.allocate(20, 20, OF_IMAGE_COLOR_ALPHA);
    invasiveImage.loadImage(configXml.getValue("Skin"));
    nbrInvaByInsertion=configXml.getIntValue("Regulation/ByInsertion");
    nbrInvaMax=configXml.getIntValue("Regulation/Max");
    DeplacementInva=configXml.getIntValue("Skills/Speed");
    VisibiliteInva=configXml.getIntValue("Skills/Eyesight");
    PorteeAttaqueInva=configXml.getIntValue("Skills/Range");
    DivPerteEnergieInva=configXml.getIntValue("Skills/Endurance");
    ReproductionInva=configXml.getIntValue("Skills/Reproduction/ByReprod");
    DivReprodInva=configXml.getIntValue("Skills/Reproduction/Div");

     }else{
     printf("Impossible de lire le fichier");
     }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
if(key == 'l') {
    ReadConfig();
}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    sprintf (xAndyVisedString, "/ x=%i  y=%i", x, y);
    if(x>15+XCalib && x<365+XCalib && y>15+YCalib && y<415+YCalib){ //cadre A1
        sprintf(cadreVisedString, "A1");
    }else if(x>370+XCalib && x<720+XCalib && y>15+YCalib && y<415+YCalib){ //cadre A2
        sprintf(cadreVisedString, "A2");
    }else if(x>725+XCalib && x<1075+XCalib && y>15+YCalib && y<415+YCalib){ //cadre A3
        sprintf(cadreVisedString, "A3");
    }else if(x>15+XCalib && x<365+XCalib && y>420+YCalib && y<820+YCalib){ //cadre B1
        sprintf(cadreVisedString, "B1");
    }else if(x>370+XCalib && x<720+XCalib && y>420+YCalib && y<820+YCalib){ //cadre B2
        sprintf(cadreVisedString, "B2");
    }else if(x>725+XCalib && x<1075+XCalib && y>420+YCalib && y<820+YCalib){ //cadre B3
        sprintf(cadreVisedString, "B3");
    }else{
     sprintf(cadreVisedString, "");
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if(x>15+XCalib && x<365+XCalib && y>15+YCalib && y<415+YCalib){ //cadre A1
        sprintf (xAndyPressedString, "/ x=%i  y=%i", x, y);
        sprintf(cadrePressedString, "A1");
        xForInsertion=x;
        yForInsertion=y;
    }else if(x>370+XCalib && x<720+XCalib && y>15+YCalib && y<415+YCalib){ //cadre A2
        sprintf (xAndyPressedString, "/ x=%i  y=%i", x, y);
        sprintf(cadrePressedString, "A2");
        xForInsertion=x;
        yForInsertion=y;
    }else if(x>725+XCalib && x<1075+XCalib && y>15+YCalib && y<415+YCalib){ //cadre A3
        sprintf (xAndyPressedString, "/ x=%i  y=%i", x, y);
        sprintf(cadrePressedString, "A3");
        xForInsertion=x;
        yForInsertion=y;
    }else if(x>15+XCalib && x<365+XCalib && y>420+YCalib && y<820+YCalib){ //cadre B1
        sprintf (xAndyPressedString, "/ x=%i  y=%i", x, y);
        sprintf(cadrePressedString, "B1");
        xForInsertion=x;
        yForInsertion=y;
    }else if(x>370+XCalib && x<720+XCalib && y>420+YCalib && y<820+YCalib){ //cadre B2
        sprintf (xAndyPressedString, "/ x=%i  y=%i", x, y);
        sprintf(cadrePressedString, "B2");
        xForInsertion=x;
        yForInsertion=y;
    }else if(x>725+XCalib && x<1075+XCalib && y>420+YCalib && y<820+YCalib){ //cadre B3
        sprintf (xAndyPressedString, "/ x=%i  y=%i", x, y);
        sprintf(cadrePressedString, "B3");
        xForInsertion=x;
        yForInsertion=y;
    }
    
    //gestion des boutons 1 et 2
    if(x>1100+XCalib && x<1235+XCalib && y>285+YCalib && y<305+YCalib){ //insŽrer
        InvaInsertion();
        
    }
    if(x>1100+XCalib && x<1250+XCalib && y>485+YCalib && y<505+YCalib){ //Žradiquer
        InvaEradicationCadre();
    }
    if(x>1100+XCalib && x<1250+XCalib && y>566+YCalib && y<586+YCalib){ //Žradication totale
        InvaEradicationTotale();
    }
    if(x>1100+XCalib && x<1150+XCalib && y>600+YCalib && y<620+YCalib){ //Žradication totale
       Reset();
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}