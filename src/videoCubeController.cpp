//
//  videoCubeController.cpp
//  simpleVideoCubes
//
//  Created by Johann Diedrick on 1/1/14.
//
//

#include "videoCubeController.h"

videoCubeController::videoCubeController(){
    
}

void videoCubeController::setup(){
    addVideoCubes(50, ofRandom(50), ofRandom(50), ofRandom(50));
}

void videoCubeController::setupWithGrid(){
 
    int res = NUM_OF_VIDEOCUBES / sqrt(NUM_OF_VIDEOCUBES);
    //int mXRes = ofGetWindowWidth()/res;
    //int mYRes = ofGetWindowHeight()/res;
    
    
    for( int y=0; y<5; y++ ){
        for( int x=0; x<5; x++ ){
                addVideoCubes(res, x, y, 0.0);

        }
    }
    
}

void videoCubeController::update(){
    
    for(list<videoCube>::iterator vc = mVideoCubes.begin(); vc != mVideoCubes.end(); ++vc){
        vc->update();
    }
    
}

void videoCubeController::draw(videoPlayerController _vpc){
    
    for(list<videoCube>::iterator vc = mVideoCubes.begin(); vc != mVideoCubes.end(); ++vc){
        vc->draw(_vpc);
    }
    
}

void videoCubeController::addVideoCubes(int amount, int _x, int _y, int _z){
    
    float x = (_x + 5.0f) * VIDEOCUBE_SPACING;
    float y = (_y + 5.0f) * VIDEOCUBE_SPACING;
    float z = 0.0;
    
    for (int i = 0; i<amount; i++){
        mVideoCubes.push_back(videoCube( ofVec3f(x, y, z) ));
    }
    
}

void videoCubeController::addVideoCube(int _x, int _y, int _z){
    
    float x = _x;
    float y = _y;
    float z = 0.0;
    
    mVideoCubes.push_back(videoCube( ofVec3f(x, y, z) ));
    
    
}

#pragma mark Particle System Functions

void videoCubeController::repulseVideoCubes(){
    
    for(list<videoCube>::iterator vc1 = mVideoCubes.begin(); vc1 != mVideoCubes.end(); ++vc1){
        list<videoCube>::iterator vc2 = vc1;
        for (++vc2; vc2 != mVideoCubes.end(); ++vc2) {
         
            ofVec3f dir = vc1->mLoc - vc2->mLoc;
            float distSqrd = dir.lengthSquared();
            
            if (distSqrd>0.0f) {
                dir.normalize();
                float F = 1.0f/distSqrd;
                vc1->mAcc += dir * ( F / vc1->mMass);
                vc2->mAcc -= dir * ( F / vc2->mMass);
            }
        }
    }
    
}

void videoCubeController::pullToCenter( ofVec3f _center ){
    for(list<videoCube>::iterator vc = mVideoCubes.begin(); vc != mVideoCubes.end(); ++vc){
        vc->pullToCenter( _center );
    }
}