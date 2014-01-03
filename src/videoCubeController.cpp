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
    //
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