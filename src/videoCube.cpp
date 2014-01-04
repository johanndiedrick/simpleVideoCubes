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
    
   // mVel = 1.0;
    mVel = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
    mLoc.set(ofRandom(50), ofRandom(50), ofRandom(50));
    mMass = 1.0;

    
}

videoCube::videoCube( ofVec3f loc ){
    
    videoNumber = ofRandom(NUM_OF_VIDEOS);
    
    mAcc.set(0.0);
    mVel = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
    mLoc.set(loc);
    mMass = 1.0;
    
}

videoCube::videoCube( ofVec3f loc, ofVec3f vel ){
    
    videoNumber = ofRandom(NUM_OF_VIDEOS);
    mMass = 1.0;
    mAcc.set(0.0);
    mLoc.set(loc);
    mVel.set(vel);
    
    
}

void videoCube::setup(){
    //
}

void videoCube::update(){
    
    mVel += mAcc;
    mLoc += mVel;
    //decay
    mAcc.set(0.0);
    
    //float t = (ofGetElapsedTimef() + boxNumber * spacing) * mVel;
    //		//ofVec3f pos(
    //                    ofSignedNoise(t, 0, 0),
    //                    ofSignedNoise(0, t, 0),
    //                    ofSignedNoise(0, 0, t));
    
    //float boxSize = NUM_OF_VIDEOCUBES * ofNoise(pos.x, pos.y, pos.z);
    
    //pos *= cloudSize;
	//ofTranslate(pos);
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

void videoCube::pullToCenter(ofVec3f _center ){
    
    /*
    ofVec3f dirToCenter = mLoc - ofVec3f(ofGetWindowWidth()/2,ofGetWindowHeight()/2, 0);
    mVel -= dirToCenter * mMass * 0.025f;
    */
    
    ofVec3f dirToCenter     =   mLoc - _center;
    float distToCenter    =   dirToCenter.length();
    float   maxDistance     =   200.0f;
    
    if(distToCenter > maxDistance){
        dirToCenter.normalize();
        
        float pullStrength = 0.001f; // this keeps our video cubes in closer
        mVel -= dirToCenter * ( (distToCenter - maxDistance) * pullStrength );
    }
    
    
}


