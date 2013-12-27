//
//  videoCubes.cpp
//  simpleVideoCubes
//
//  Created by Johann Diedrick on 12/27/13.
//
//

#include "videoCubes.h"
#include "testApp.h"


videoCube::videoCube(){
    
    videoNumber = ofRandom(NUM_OF_VIDEOS - 1);
    
    //    // Set the initial color
    //    color.set( ofRandom(255), ofRandom(255), ofRandom(255));
    //
    //    // Initial x position of the ball
    //    x = ofRandom( ofGetWindowWidth() );
    //
    //    // Initial y position of the ball
    //    y = ofRandom( ofGetWindowHeight() );
}

