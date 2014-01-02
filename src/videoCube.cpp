//
//  videoCubes.cpp
//  simpleVideoCubes
//
//  Created by Johann Diedrick on 12/27/13.
//
//

#include "videoCube.h"
#include "testApp.h"


videoCube::videoCube(){
    
    videoNumber = ofRandom(NUM_OF_VIDEOS);
    
    mVel = 0.1;
    
    
    mLoc.set(ofRandom(50), ofRandom(50), ofRandom(10));
    //    // Set the initial color
    //    color.set( ofRandom(255), ofRandom(255), ofRandom(255));
    //
    //    // Initial x position of the ball
    //    x = ofRandom( ofGetWindowWidth() );
    //
    //    // Initial y position of the ball
    //    y = ofRandom( ofGetWindowHeight() );
    
}

void videoCube::setup(){
    //
}

void videoCube::update(){
    //
}

void videoCube::draw(){
    
        float cloudSize = ofGetWidth() / 2;
        float spacing = 1;
    
		ofPushMatrix();
		
		//float t = (ofGetElapsedTimef() + boxNumber * spacing) * mVel;
//		//ofVec3f pos(
//                    ofSignedNoise(t, 0, 0),
//                    ofSignedNoise(0, t, 0),
//                    ofSignedNoise(0, 0, t));
		
		//float boxSize = NUM_OF_VIDEOCUBES * ofNoise(pos.x, pos.y, pos.z);
		
		//pos *= cloudSize;
	//	ofTranslate(pos);
		//ofRotateX(pos.x);
		//ofRotateY(pos.y);
		//ofRotateZ(pos.z);
		//ofEnableDepthTest();
        ofEnableNormalizedTexCoords();
        
        //vids[number].getTextureReference().bind();
		ofFill();
        //ofPushMatrix();
        ofEnableDepthTest();
        ofDrawBox(mLoc.x, mLoc.y, mLoc.z, 10);
        ofDisableDepthTest();
        //ofPopStyle();
       // vids[number].getTextureReference().unbind();
        
        ofDisableNormalizedTexCoords();
		
		//ofNoFill();
		//ofSetColor(ofColor::fromHsb(sinf(t) * 128 + 128, 255, 255));
		//ofDrawBox(boxSize);
		
		ofPopMatrix();

    
}


