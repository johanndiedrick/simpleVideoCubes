//
//  Predator.h
//  simpleVideoCubes
//
//  Created by Johann Diedrick on 1/5/14.
//
//

#ifndef __simpleVideoCubes__Predator__
#define __simpleVideoCubes__Predator__

#include <iostream>
#include "ofMain.h"

class Predator {
    
public:
    Predator();
    Predator( ofVec3f loc, ofVec3f vel );
    
    void setup();
    void update( bool _flatten );
    void draw();
    std::vector<ofVec3f> mPos;
    float mLen;
    float mInvLen;
    void pullToCenter( ofVec3f _center );
    void limitSpeed();
    void addNeighborPos( ofVec3f pos );


    
    ofVec3f mVel;
    ofVec3f mVelNormal;
    ofVec3f mAcc;
    
    ofVec3f mNeighborPos;
    
    float mNumNeighbors;
    float mMaxSpeed;
    float mMaxSpeedSqrd;
    float mMinSpeed;
    float mMinSpeedSqrd;           
    //mColor                        = ColorA( 1.0f, 0.0f, 0.0f, 1.0f );
    
    float mDecay;
    float mRadius;
    float mLength;
    float mHunger;
    
    bool mIsDead;
    bool mIsHungry;
    
};

#endif /* defined(__simpleVideoCubes__videoCubes__) */
