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
    
    //mLoc.set(ofRandom(50), ofRandom(50), ofRandom(50));

    
}

videoCube::videoCube( ofVec3f loc ){
    
    videoNumber = ofRandom(NUM_OF_VIDEOS);
    
    mVel = 0.1;
    
    //mLoc.set(ofRandom(50), ofRandom(50), ofRandom(50));
    
    mLoc.set(loc);

}

void videoCube::setup(){
    //
}

void videoCube::update(){
    //mLoc = mLoc+mVel;
    
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
    
    
}

void videoCube::draw(videoPlayerController _vpc){
    
  
    
		ofPushMatrix();
		//ofEnableDepthTest();
        ofEnableNormalizedTexCoords();
        
        _vpc.mVideoPlayers[videoNumber].getTextureReference().bind();
		ofFill();
        //ofPushMatrix();
        ofEnableDepthTest();
        ofDrawBox(mLoc.x, mLoc.y, mLoc.z, 10);
        ofDisableDepthTest();
        //ofPopStyle();
        _vpc.mVideoPlayers[videoNumber].getTextureReference().unbind();
        
        ofDisableNormalizedTexCoords();
		
		//ofNoFill();
		//ofSetColor(ofColor::fromHsb(sinf(t) * 128 + 128, 255, 255));
		//ofDrawBox(boxSize);
		
		ofPopMatrix();

    
}


