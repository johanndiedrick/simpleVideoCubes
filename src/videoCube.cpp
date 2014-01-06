//
//  videoCubes.cpp
//  simpleVideoCubes
//
//  Created by Johann Diedrick on 12/27/13.
//
//

#include "videoCube.h"
#include "testApp.h"


//not maintained
videoCube::videoCube(){
    
    videoNumber = ofRandom(NUM_OF_VIDEOS);
    
   // mVel = 1.0;
    mVel = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
    mLoc.set(ofRandom(50), ofRandom(50), ofRandom(50));
    mMass = 1.0;
    mRadius			= 12.0f;
	mDecay			= 0.99f;

    
}

//not maintained
videoCube::videoCube( ofVec3f loc ){
    
    videoNumber = ofRandom(NUM_OF_VIDEOS);
    
    mAcc.set(0.0);
    mVel = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
    mLoc.set(loc);
    mMass = 1.0;
    
}

videoCube::videoCube( ofVec3f loc, ofVec3f vel ){
    
    videoNumber = ofRandom(NUM_OF_VIDEOS);
 	mLoc			= loc;
	mVel			= vel;
	mAcc.set(0.0);
    
	mRadius			= 15.0f;
	mDecay			= 0.99f;
    
    mMaxSpeed = ofRandom(2.0f, 3.0f);
    mMaxSpeedSqrd = mMaxSpeed * mMaxSpeed;
    mMinSpeed = ofRandom(0.0f);//, 0.9f); // some videocubes can have a min speed of 0.0f
    mMinSpeedSqrd = mMinSpeed * mMinSpeed;
    
    mVelNormal = ofVec3f(0, 1, 0); //y-axis
    mDeacc = 1.0f;
    
    //predator stuff
    mFear = 1.0f;
    mIsDead = false;
    mCrowdFactor = 1.0;
    followed = 1.0;
    mNumNeighbors = 0;
    mNeighborPos = ofVec3f(0);
    
}

void videoCube::setup(){
    //
}

//not maintained
void videoCube::update(){
    
    mVel += mAcc;
    mVelNormal = mVel.normalize();
    limitSpeed();
	mLoc += mVel;
	mVel *= mDecay;
    mAcc.set(0.0);
    
}

void videoCube::update( bool _flatten ){
    
    //predator stuff
    mCrowdFactor -= ( mCrowdFactor - ( 1.0f - mNumNeighbors * 0.02f ) ) * 0.1f;
    mCrowdFactor = ofClamp( mCrowdFactor, 0.5f, 1.0f );
    
    mFear -= ( mFear - 0.0f ) * 0.2f;
    //end predator stuff
    
    if( _flatten ) mAcc.z = 0.0f;
    mVel += mAcc; // increase velocity by acceleration
    mVelNormal = mVel.normalize(); // get a normalized velocity
    limitSpeed(); // make sure the speed isn't over our min/max
    mVel *= mDeacc; //decelerate (slow down)
	mLoc += mVel; // move our video cube by velocity vector
    if( _flatten ) mLoc.z = 0.0f;
	mVel *= mDecay;
    mAcc.set(0.0);
    mNeighborPos.set(0);
    mNumNeighbors = 0;
    
}

void videoCube::draw(videoPlayerController _vpc){
    
		ofPushMatrix();
		//ofEnableDepthTest();
        ofEnableNormalizedTexCoords();
        
        _vpc.mVideoPlayers[videoNumber].getTextureReference().bind();
		ofFill();
        //ofPushMatrix();
        ofEnableDepthTest();
        ofDrawBox(mLoc.x, mLoc.y, mLoc.z, mRadius);
    
        //draw circle to see radius
        //ofDrawSphere(mLoc.x, mLoc.y, mRadius);
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
    
    /*
    ofVec3f dirToCenter     =   mLoc - _center;
    float distToCenter    =   dirToCenter.length();
    float   maxDistance     =   200.0f;
    
    if(distToCenter > maxDistance){
        dirToCenter.normalize();
        
        float pullStrength = 0.001f; // this keeps our video cubes in closer
        mVel -= dirToCenter * ( (distToCenter - maxDistance) * pullStrength );
    }
    */
    
    ofVec3f dirToCenter	= mLoc - _center;
	float distToCenter	= dirToCenter.length();
	float maxDistance	= 300.0f;
	
	if( distToCenter > maxDistance ){
		dirToCenter.normalize();
		float pullStrength = 0.0001f;
		mVel -= dirToCenter * ( ( distToCenter - maxDistance ) * pullStrength );
	}
    
}

void videoCube::limitSpeed(){
    
    //predator stuff
    
    float maxSpeed = mMaxSpeed + mCrowdFactor;
    float maxSpeedSqrd = maxSpeed * maxSpeed;
    
    float vLengthSqrd = mVel.lengthSquared();
    if( vLengthSqrd > maxSpeedSqrd ){
        mVel = mVelNormal * maxSpeed;
        
    } else if( vLengthSqrd < mMinSpeedSqrd ){
        mVel = mVelNormal * mMinSpeed;
    }
    mVel *= (1.0 + mFear );
    
    /*
    
    float vLengthSqrd = mVel.lengthSquared();
    
    if (vLengthSqrd > mMaxSpeedSqrd) {
        mVel = mVelNormal * mMaxSpeed;
    } else if(vLengthSqrd < mMinSpeedSqrd){
        mVel = mVelNormal * mMinSpeed;
    }
     */
    
}

void videoCube::setSpeed(float _speed){
    mDeacc = _speed;
}

void videoCube::addNeighborPos( ofVec3f pos )
{
    mNeighborPos += pos;
    mNumNeighbors ++;
}
