#pragma once

#include "ofMain.h"
#include "ofxBezelCompensation.h"


class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int k){ bezelCompensation ^= true; }

	ofxBezelCompensation bezelFbo;
	ofTexture testTexture;

	bool bezelCompensation = false;

};
