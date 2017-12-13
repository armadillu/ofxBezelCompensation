//
//  ofxBezelCompensation.cpp
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 17/11/2017.
//
//

#include "ofxBezelCompensation.h"

void ofxBezelCompensation::setup(	ofFbo::Settings settings,
								 	int numGridCellsX,
									int numGridCellsY,
									int gridUnitW,
									int gridUnitH,
									int bezelSize){

	numX = numGridCellsX;
	numY = numGridCellsY;
	unitW = gridUnitW;
	unitH = gridUnitH;
	this->canvasW = numGridCellsX * gridUnitW;
	this->canvasH = numGridCellsY * gridUnitH;
	this->bezelSize = bezelSize;

	fboW = (numX - 1) * bezelSize + numX * unitW;
	fboH = (numY - 1) * bezelSize + numY * unitH;

	settings.width = fboW;
	settings.height = fboH;
	myFbo.allocate(settings);

	fboSet = settings;

	ofLogNotice("ofxBezelCompensation") << "Allocating ofFbo of size: " << fboW << " x " << fboH;

	updateMesh();
}

void ofxBezelCompensation::updateMesh(){

	mesh.clear();

	int vtxIndex = 0;

	ofVec3f tl; //0 vertices
	ofVec3f tr; //1
	ofVec3f bl; //2
	ofVec3f br; //3

	ofVec2f tcl; //0 tex coords
	ofVec2f tcr; //1
	ofVec2f bcl; //2
	ofVec2f bcr; //3

	float texUnitW = unitW / float(fboW);
	float texUnitH = unitH / float(fboH);
	float bezelSizeXnormalized = float(bezelSize) / float(fboW);
	float bezelSizeYnormalized = float(bezelSize) / float(fboH);

	for(int j = 0; j < numY; j++){
		for(int i = 0; i < numX; i++){

			//calc vtx coords
			tl.x = i * unitW;
			tl.y = j * unitH;
			tr.x = (i + 1) * unitW;
			tr.y = j * unitH;
			bl.x = i * unitW;
			bl.y = (j + 1) * unitH;
			br.x = (i + 1) * unitW;
			br.y = (j + 1) * unitH;

			// calc X tex coords
			if (i == 0){ 						//leftmost
				tcl.x = 0.0f;
				bcl.x = 0.0f;
				tcr.x = texUnitW;
				bcr.x = texUnitW;
			}else if ( i == numX - 1){ 			//rightmost
				tcl.x = 1.0f - texUnitW;
				bcl.x = 1.0f - texUnitW;
				bcr.x = 1.0f;
				tcr.x = 1.0f;
			}else{ 								//middle
				tcl.x = i * texUnitW + (i) * bezelSizeXnormalized;
				bcl.x = i * texUnitW + (i) * bezelSizeXnormalized;
				tcr.x = (i+1) * texUnitW + (i) * bezelSizeXnormalized;
				bcr.x = (i+1) * texUnitW + (i) * bezelSizeXnormalized;
			}

			// calc Y tex coords
			if (j == 0){ 						//topmost
				tcl.y = 0.0f;
				tcr.y = 0.0f;
				bcl.y = texUnitH;
				bcr.y = texUnitH;
			}else if ( j == numY - 1){ 			//bottomMost
				bcl.y = 1.0f;
				bcr.y = 1.0f;
				tcl.y = 1.0f - texUnitH;
				tcr.y = 1.0f - texUnitH;
			}else{ 								//middle
				tcl.y = j * texUnitH + (j) * bezelSizeYnormalized;
				tcr.y = j * texUnitH + (j) * bezelSizeYnormalized;
				bcl.y = (j+1) * texUnitH + (j) * bezelSizeYnormalized;
				bcr.y = (j+1) * texUnitH + (j) * bezelSizeYnormalized;
			}

			mesh.addVertex(tl); mesh.addVertex(tr); mesh.addVertex(bl); mesh.addVertex(br);
			if(fboSet.textureTarget == GL_TEXTURE_RECTANGLE_ARB){
				tcl.x *= fboW; tcl.y *= fboH;
				tcr.x *= fboW; tcr.y *= fboH;
				bcl.x *= fboW; bcl.y *= fboH;
				bcr.x *= fboW; bcr.y *= fboH;
			}
			mesh.addTexCoord(tcl); mesh.addTexCoord(tcr); mesh.addTexCoord(bcl); mesh.addTexCoord(bcr);

			//top left triangle
			mesh.addIndex(vtxIndex + 0);
			mesh.addIndex(vtxIndex + 1);
			mesh.addIndex(vtxIndex + 2);

			//bottom right triangle
			mesh.addIndex(vtxIndex + 2);
			mesh.addIndex(vtxIndex + 1);
			mesh.addIndex(vtxIndex + 3);

			vtxIndex += 4;
		}
	}
}

void ofxBezelCompensation::drawWithBezelCompensation(bool debug){

	myFbo.getTexture().bind();
	
	ofNotifyEvent(eventBeforeDraw, myFbo, this);
	mesh.draw();
	ofNotifyEvent(eventAfterDraw, myFbo, this);
	
	myFbo.getTexture().unbind();

	if(debug){
		ofPushStyle();
		ofSetColor(0,66);
		mesh.drawWireframe();
		ofPopStyle();
	}
}