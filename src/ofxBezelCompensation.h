//
//  ofxBezelCompensation.h
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 17/11/2017.
//
//

#pragma once
#include "ofMain.h"

class ofxBezelCompensation{

public:

	void setup(ofFbo::Settings settings,
			   int numGridCellsX, //num screens X
			   int numGridCellsY, //num screens Y
			   int gridUnitW, //pixels width of each screen
			   int gridUnitH, //pixels height of each screen
			   int bezelSize //in pixels
			   );

	//use these to draw your scene into the FBO
	void begin(){ myFbo.begin();}
	void end(){ myFbo.end();}

	int getWidth(){return myFbo.getWidth();};
	int getHeight(){return myFbo.getHeight();};


	void drawWithBezelCompensation(bool debug);

	ofFbo & getFbo(){return myFbo;};

protected:

	ofFbo myFbo;
	ofFbo::Settings fboSet;

	int numX = 4;
	int numY = 3;
	int unitW = 400;
	int unitH = 300;
	int bezelSize = 10;

	int canvasW = unitW * numX;
	int canvasH = unitH * numY;

	int fboW;
	int fboH;

	void updateMesh();
	ofVboMesh mesh;


};

