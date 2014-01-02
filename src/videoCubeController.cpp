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
 
    for (int i = 0; i<NUM_OF_VIDEOCUBES; i++){
        mVideoCubes.push_back(videoCube());
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