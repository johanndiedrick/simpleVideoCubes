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
    videoCube( ofVec3f loc, ofVec3f vel );
    void setup();
    void update();
    void update( bool _flatten );
    void draw(videoPlayerController _vpc);
    
    //particle system
    void pullToCenter( ofVec3f _center );
    void limitSpeed();
    
    int boxNumber;
    
    int videoNumber;

    ofVec3f mLoc;
    ofVec3f mVel;
    ofVec3f mAcc;
    
    float mMass;
    
    //float mVel;
    float mSize;
    
    float mRadius;
    float mDecay;
    
    float mMaxSpeed;
    float mMaxSpeedSqrd;
    float mMinSpeed;
    float mMinSpeedSqrd;
    
    ofVec3f mVelNormal;
    
};

#endif /* defined(__simpleVideoCubes__videoCubes__) */
