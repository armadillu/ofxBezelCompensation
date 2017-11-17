#include "ofApp.h"

void ofApp::setup(){

	//load some test content
	ofLoadImage(testTexture, "fboTest2.psd");

	//chose your FBO settings (you will have to draw all your scene into an FBO for ofxBezelCompensation to work)
	ofFbo::Settings fboSet;
	fboSet.useDepth = false;
	fboSet.useStencil = false;
	fboSet.textureTarget = GL_TEXTURE_2D; //GL_TEXTURE_2D or GL_TEXTURE_RECTANGLE_ARB
	fboSet.internalformat = GL_RGB;
	fboSet.numSamples = 0;

	//setup your wall / monitor grid
	int numX = 4;
	int numY = 3;
	int unitW = 400;
	int unitH = 300;
	int bezelSize = 10;

	//setup the ofxBezelCompensation object;
	//this will allocate an fbo slightly larger than your canvas to include the bezels betwen each grid unit
	bezelFbo.setup(
				   fboSet,
				   numX,
				   numY,
				   unitW,
				   unitH,
				   bezelSize
				   );

}


void ofApp::update(){
	
}


void ofApp::draw(){


	bezelFbo.begin();
		//draw your raw contents into the ofxBezelCompensation
		testTexture.draw(0,0, bezelFbo.getWidth(), bezelFbo.getHeight());
	bezelFbo.end();

	//draw actual content to screen
	if(bezelCompensation){
		bezelFbo.drawWithBezelCompensation(false);
	}else{
		bezelFbo.getFbo().draw(0,0);
	}

	ofDrawBitmapStringHighlight("Press any key to toggle bezel compensation\nBezel Compensation: " + string(bezelCompensation?"yes":"no"), 20, 20);
}
