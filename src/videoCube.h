//
//  videoCubes.h
//  simpleVideoCubes
//
//  Created by Johann Diedrick on 12/27/13.
//
//

#ifndef __simpleVideoCubes__videoCubes__
#define __simpleVideoCubes__videoCubes__

#include <iostream>
#include "ofMain.h"
#include "videoPlayerController.h"

class videoCube {
    
public:
    videoCube();
    videoCube( ofVec3f loc );
    void setup();
    void update();
    void draw(videoPlayerController _vpc);
    
    int boxNumber;
    
    int videoNumber;

    ofVec3f mLoc;
    ofVec3f mDir;
    float mVel;
    float mSize;
    
};

#endif /* defined(__simpleVideoCubes__videoCubes__) */
