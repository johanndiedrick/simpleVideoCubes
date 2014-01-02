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

class videoCube {
    
public:
    videoCube();
    void setup();
    void update();
    void draw();
    
    int boxNumber;
    
    int videoNumber;
    string videoURL;
    //should a video cube also have a cube? might want to flesh this out on a lower level...
    //void playVideo();
    //void muteVideo();
    
    ofVec3f mLoc;
    ofVec3f mDir;
    float mVel;
    float mSize;
    
    vector<ofVideoPlayer>* mVideoPlayers;
    
    
    
    
};

#endif /* defined(__simpleVideoCubes__videoCubes__) */
