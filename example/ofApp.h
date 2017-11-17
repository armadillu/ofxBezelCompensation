#pragma once

#include "ofMain.h"
#include "ofxBezelCompensation.h"


class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	ofxBezelCompensation bezelFbo;
	ofTexture testTexture;


};
