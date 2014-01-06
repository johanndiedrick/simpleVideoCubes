//
//  Predator.cpp
//  simpleVideoCubes
//
//  Created by Johann Diedrick on 1/5/14.
//
//

#include "Predator.h"
#include "testApp.h"



Predator::Predator(){
//
}



Predator::Predator( ofVec3f loc, ofVec3f vel ){
    
    mLen = 5;
    mInvLen = 1.0f/(float)mLen;
    
    for( int i=0; i<mLen; ++i ) {
        mPos.push_back( loc );
    }
    
    mVel = vel;
    mVelNormal = ofVec3f(0,1,0);
    mAcc = ofVec3f(0);
    
    mNeighborPos = ofVec3f(0);
    mNumNeighbors = 0;
    mMaxSpeed = ofRandom( 4.0f, 4.5f );
    mMaxSpeedSqrd = mMaxSpeed * mMaxSpeed;
    mMinSpeed = ofRandom( 1.0f, 1.5f );
    mMinSpeedSqrd = mMinSpeed * mMinSpeed;
    
    mDecay = 0.99f;
    mRadius = 25.0f;
    mLength = 25.0f;
    mHunger = 1.0f;
    
    mIsDead = false;
    mIsHungry = true;

    
}

void videoCube::setup(){
    //
}


void Predator::pullToCenter( ofVec3f center )
{
    ofVec3f dirToCenter        = mPos[0] - center;
    float distToCenter        = dirToCenter.length();
    float maxDistance        = 600.0f;
    
    if( distToCenter > maxDistance ){
        float pullStrength = 0.00025f;
        mVel -= dirToCenter.normalized() * ( ( distToCenter - maxDistance ) * pullStrength );
    }
}

void Predator::update( bool flatten )
{
    mVel += mAcc;
    
    if( flatten ) mAcc.z = 0.0f;
    mVel += mAcc;
    mVelNormal = mVel.normalized();
    
    limitSpeed();
    
    
    for( int i=mLen-1; i>0; i-- ){
        mPos[i] = mPos[i-1];
    }
    mPos[0] += mVel;
    
    if( flatten )
        mPos[0].z = 0.0f;
    
    mVel *= mDecay;
    
    mAcc = ofVec3f(0);
    mNeighborPos = ofVec3f(0);
    mNumNeighbors = 0;
    
    mHunger += 0.001f;
    mHunger = ofClamp( mHunger, 0.0f, 1.0f );
    
    if( mHunger > 0.5f ) mIsHungry = true;
}

void Predator::limitSpeed()
{
    float maxSpeed = mMaxSpeed + mHunger * 3.0f;
    float maxSpeedSqrd = maxSpeed * maxSpeed;
    float vLengthSqrd = mVel.lengthSquared();
    if( vLengthSqrd > maxSpeedSqrd ){
        mVel = mVelNormal * maxSpeed;
        
    } else if( vLengthSqrd < mMinSpeedSqrd ){
        mVel = mVelNormal * mMinSpeed;
    }
}

void Predator::draw()
{
    ofPushStyle();
    ofColor(255, 255 ,255);
    //ttogle drawing of predators
    //ofDrawSphere(mPos[0].x, mPos[0].y, mPos[0].z, mRadius);
    ofPopStyle();

}



void Predator::addNeighborPos( ofVec3f pos )
{
    mNeighborPos += pos;
    mNumNeighbors ++;
}


