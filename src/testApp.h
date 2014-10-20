#pragma once

#include "ofMain.h"
#include "creature.h"
#include <iostream>
#include <list>


class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
    
    void populate();
    void drawCreatures();
    void vieGlobal();
    void InvaInsertion();
    void InvaEradicationCadre();
    void InvaEradicationTotale();
    void Reset();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    int counterDivCycle; 
    int countCycle;
    float countPred;
    float countHerb;
    float countVeg;
    float countInva;
    
    int xForInsertion;
    int yForInsertion;
    
    bool deadWorld;
        
    std::list<creature> vegetals;
    std::list<creature> herbivors;
    std::list<creature> predators;
    std::list<creature> invasives;
    
    ofBlendMode blendMode;
    
    char xAndyVisedString[255];
    char cadreVisedString[255];
    char xAndyPressedString[255];
    char cadrePressedString[255];
    char actualCycleString[255];
    char percentPredatorsGlobalString[255];
    char percentHerbivorsGlobalString[255];
    char percentVegetalsGlobalString[255];
    char percentInvasivesGlobalString[255];
    char percentPredatorsZoneString[255];
    char percentHerbivorsZoneString[255];
    char percentVegetalsZoneString[255];
    char percentInvasivesZoneString[255];
    char InsertionCycle[255];
    char InsertionCadre[255];
    char EradicationCadre[255];
    char EradicationCycle[255];
    
    
    /****************/
    /*à lire dans lfConfig.xml*/
    void ReadConfig();
    ofFile configFile;
    ofBuffer configBuffer;
    ofXml configXml;
    
    ofImage vegetalImage;
    ofImage herbivorImage;
    ofImage predatorImage;
    ofImage invasiveImage;
    ofImage backgroundImage;
    ofTrueTypeFont 	endOfWorld;
    
    int XCalib; // valeurs en x et y pour calibrer le dessin par rapport à l'écran (centrer) (entier)
    int YCalib; // (entier)
    bool Quadri; //quadrillage noir?
    bool BackgroundActif; //si faux -> écran brun
    
    int nbrPredInit; //nombre de créatures de chaque catégorie au lancement de l'appli (entier)
    int nbrHerbInit;
    int nbrVegInit;
    int nbrVegMax; //nombre de créatures maximum (entier)
    int nbrHerbMax;
    int nbrPredMax;
    int nbrInvaMax;
    
    int DivDeplacement; //diviseur de vitesse de déplacement (entier >0) !Inutilisable pour l'instant
    int DivClign; //diviseur de clignotement bender (entier > 1)
    int DivCycle; //diviseur de vitesse d'incrémentation de cycle (entier >0)
    
    int DivReprodVeg; //diviseur de vitesse de reproduction (entier)
    int DivReprodHerb;
    int DivReprodPred;
    int DivReprodInva;
    
    bool BoolAleaVegGeneration; //activer la génération aléatoire de végétaux?
    int DivAleaVegGeneration; //diviseur de vitesse d'apparition aléatoire de vegetal
    //REMARQUE : pour l'instant aucune limite maximum n'est imposée à l'apparition de ces "vegetals" de manière alétoire
    
    int DimensionEspece; //ici les dimensions du carré l'image des espèces (identique pour tous) !!
    
    int DivPerteEnergiePred; //diviseur de vistesse de perte d'énergie (entier > 1)
    int DivPerteEnergieHerb; //
    int DivPerteEnergieInva; //1 = perte à tous les tours / 2 = 1 tour sur 2 / etc
    
    int PorteeAttaquePred; //portée des créatures leur permettant de manger
    int PorteeAttaqueHerb;
    int PorteeAttaqueInva;
    int VisibilitePred; //ligne de vue des créatures en recherche de proies
    int VisibiliteHerb;
    int VisibiliteInva;
    
    int DeplacementInva; // caractéristiques de l'espèce invasive
    int ReproductionInva;
    int nbrInvaByInsertion;
    
    int DeplacementPred; // caractéristiques de Predator
    int ReproductionPred;
    
    int DeplacementHerb; // caractéristiques de Herbivor
    int Reproductionherb;
    
    int ReproductionVeg; // caractéristiques de Vegetal

        };
