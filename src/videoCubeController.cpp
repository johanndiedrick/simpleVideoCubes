//
//  videoCubeController.cpp
//  simpleVideoCubes
//
//  Created by Johann Diedrick on 1/1/14.
//
//

#include "videoCubeController.h"

videoCubeController::videoCubeController(){
    
//    noise = ofNoise(4);
    
}

void videoCubeController::setup(){
    addVideoCubes(NUM_OF_VIDEOCUBES);
    addPredators(NUM_OF_PREDATORS);
    
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

void videoCubeController::update( bool _flatten ){
    
    for(list<videoCube>::iterator vc = mVideoCubes.begin(); vc != mVideoCubes.end(); ++vc){
        vc->update( _flatten );
    }
    for( list<Predator>::iterator p = mPredators.begin(); p != mPredators.end(); ++p ){
        p->update( _flatten );
    }
    //end predator stuffs
    
}

void videoCubeController::draw(videoPlayerController _vpc){
    
    for(list<videoCube>::iterator vc = mVideoCubes.begin(); vc != mVideoCubes.end(); ++vc){
        vc->draw(_vpc);
    }
    
    //predator stuff
    for( list<Predator>::iterator p = mPredators.begin(); p != mPredators.end(); ++p ){
        //float hungerColor = 1.0f - p->mHunger;
       // gl::color( ColorA( 1.0f, hungerColor, hungerColor, 1.0f ) );
        p->draw();
    }
    //end predator stuff
    
}

#pragma mark Add Video Cubes

void videoCubeController::addVideoCubes(int amount, int _x, int _y, int _z){
    
    float x = (_x + 5.0f) * VIDEOCUBE_SPACING;
    float y = (_y + 5.0f) * VIDEOCUBE_SPACING;
    float z = 0.0;
    
    for (int i = 0; i<amount; i++){
        mVideoCubes.push_back(videoCube( ofVec3f(x, y, z) ));
    }
    
}



void videoCubeController::addVideoCubes(int amount){
    
	for( int i=0; i<amount; i++ ) {
		ofVec3f randVec = randVec3f();
		ofVec3f loc = randVec * ofRandom( 50.0f );
		ofVec3f vel = randVec * ofRandom( 5.0f );
		mVideoCubes.push_back( videoCube( loc, vel ) );
	}
    
}

void videoCubeController::addVideoCube(int _x, int _y, int _z){
    
    float x = _x;
    float y = _y;
    float z = 0.0;
    
    mVideoCubes.push_back(videoCube( ofVec3f(x, y, z) ));
    
    
}

#pragma mark Add Predators

void videoCubeController::addPredators(int amount){
    for( int i=0; i<amount; i++ )
    {
        ofVec3f pos = randVec3f() * ofRandom( 500.0f, 750.0f );
        ofVec3f vel = randVec3f();
        mPredators.push_back( Predator( pos, vel ) );
    }
    
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

void videoCubeController::setSpeed( float _speed ){
    for(list<videoCube>::iterator vc = mVideoCubes.begin(); vc != mVideoCubes.end(); ++vc){
        vc->setSpeed( _speed );
    }
}

void videoCubeController::pullToCenter( ofVec3f _center ){
    for(list<videoCube>::iterator vc = mVideoCubes.begin(); vc != mVideoCubes.end(); ++vc){
        vc->pullToCenter( _center );
    }
    
    //PREDATOR STUFFS
    for( list<Predator>::iterator p = mPredators.begin(); p != mPredators.end(); ++p ){
        p->pullToCenter( _center );
    }
    //END OF PREDATOR STUFFS
}

/*
void videoCubeController::applyForce(float _zoneRadiusSqrd, float thresh){
    
    for(list<videoCube>::iterator vc1 = mVideoCubes.begin(); vc1 != mVideoCubes.end(); ++vc1){
        
        list<videoCube>::iterator vc2 = vc1;
        for (++vc2; vc2 != mVideoCubes.end(); ++vc2) {
            
            ofVec3f dir = vc1->mLoc - vc2->mLoc;
            float distSqrd = dir.lengthSquared();
            
            if (distSqrd <= _zoneRadiusSqrd) { //if our neighbor is within zone radius
                
                float percent = distSqrd/_zoneRadiusSqrd;
                
                if(percent < thresh){ // if we're within the thresh, seperate
                    
                    float F = (_zoneRadiusSqrd/distSqrd - 1.0) * 0.01;
                    dir = dir.normalize();
                    dir *= F;
                    
                    vc1->mAcc += dir;
                    vc2->mAcc -= dir;
                    
 
                     float F = (_zoneRadiusSqrd/distSqrd - 1.0) * 0.01;
                     dir.normalize();
                     dir *= F;
                     
                     vc1->mAcc += dir;
                     vc2->mAcc -= dir;
 
                    
                }else{
                    
                    float threshDelta = 1.0f - thresh;
                    float adjustedPercent = ( percent - thresh)/threshDelta;
                    float F = (1.0f - ( cos( adjustedPercent * M_PI*2.0f) * - 0.5 + 0.5f)) * 0.04f;
                    dir = dir.normalize();
                    dir *= F;
                    vc1->mAcc += dir;
                    vc2->mAcc -= dir;
                }
                

            }
            
        }
    }
}
*/

void videoCubeController::applyForceToVideoCubes( float _zoneRadiusSqrd, float _lowThresh, float _highThresh, float _attractStrength, float _repelStrength, float _orientStrength){
    
    float twoPI = M_PI * 2.0f;
    mParticleCentroid = ofVec3f(0);
    mNumParticles = mVideoCubes.size();
    
    for( list<videoCube>::iterator vc1 = mVideoCubes.begin(); vc1 != mVideoCubes.end(); ++vc1 ){
        
        list<videoCube>::iterator vc2 = vc1;
        for( ++vc2; vc2 != mVideoCubes.end(); ++vc2 ) {
            ofVec3f dir = vc1->mLoc - vc2->mLoc;
            float distSqrd = dir.lengthSquared();
            //float zoneRadiusSqrd = zoneRadius * zoneRadius;
            
            if( distSqrd < _zoneRadiusSqrd ){ // Neighbor is in the zone
                float percent = distSqrd/_zoneRadiusSqrd;
                
                //predator stuff
                vc1->addNeighborPos(vc2->mLoc);
                vc2->addNeighborPos(vc1->mLoc);
                //end predator stuff
                
                if( percent < _lowThresh ){ // Separation
                    float F = ( _lowThresh/percent - 1.0f ) * _repelStrength;
                    dir = dir.normalized() * F;
                    
                    vc1->mAcc += dir;
                    vc2->mAcc -= dir;
                } else if( percent < _highThresh ){ // Alignment
                    float threshDelta = _highThresh - _lowThresh;
                    float adjustedPercent = ( percent - _lowThresh )/threshDelta;
                float F = ( 1.0f - ( cos( adjustedPercent * twoPI ) * -0.5f + 0.5f ) ) * _orientStrength;
                    
                    vc1->mAcc += vc2->mVelNormal * F;
                    vc2->mAcc += vc1->mVelNormal * F;
                    
                } else { // Cohesion
                    float threshDelta = 1.0f - _highThresh;
                    float adjustedPercent = ( percent - _highThresh )/threshDelta;
                    float F = ( 1.0f - ( cos( adjustedPercent * twoPI ) * -0.5f + 0.5f ) ) * _attractStrength;
                    
                    dir.normalize();
                    dir *= F;
                    
                    vc1->mAcc -= dir;
                    vc2->mAcc += dir;
                }
            }
        }
        
        mParticleCentroid += vc1->mLoc;
        
        ///PREDATOR STUFFS
        // ADD PERLIN NOISE INFLUENCE
       // float scale = 0.002f;
       // float multi = 0.01f;
       // Vec3f perlin = mPerlin.dfBm( p1->mPos * scale ) * multi;
       // p1->mAcc += perlin;
        
        
        // CHECK WHETHER THERE IS ANY PARTICLE/PREDATOR INTERACTION
        float eatDistSqrd = 50.0f;
        float predatorZoneRadiusSqrd = _zoneRadiusSqrd * 5.0f;
        for( list<Predator>::iterator predator = mPredators.begin(); predator != mPredators.end(); ++predator ) {
            
            ofVec3f dir = vc1->mLoc - predator->mPos[0];
            float distSqrd = dir.lengthSquared();
            
            if( distSqrd < predatorZoneRadiusSqrd ){
                if( distSqrd > eatDistSqrd ){
                    float F = ( predatorZoneRadiusSqrd/distSqrd - 1.0f ) * 0.1f;
                    vc1->mFear += F * 0.1f;
                    dir = dir.normalized() * F;
                    vc1->mAcc += dir;
                    if( predator->mIsHungry )
                        predator->mAcc += dir * 0.04f * predator->mHunger;
                } else {
                    vc1->mIsDead = true;
                    predator->mHunger = 0.0f;
                    predator->mIsHungry = false;
                }
            }
        }
        
    }
    
    ///END OF PREDATOR STUFFS
    
    mParticleCentroid /= (float)mNumParticles;

}

void videoCubeController::applyForceToPredators( float zoneRadius, float lowerThresh, float higherThresh )
{
    float twoPI = M_PI * 2.0f;
    for( list<Predator>::iterator P1 = mPredators.begin(); P1 != mPredators.end(); ++P1 ){
        
        list<Predator>::iterator P2 = P1;
        for( ++P2; P2 != mPredators.end(); ++P2 ) {
            ofVec3f dir = P1->mPos[0] - P2->mPos[0];
            float distSqrd = dir.lengthSquared();
            float zoneRadiusSqrd = zoneRadius * zoneRadius * 4.0f;
            
            if( distSqrd < zoneRadiusSqrd ){                // Neighbor is in the zone
                float per = distSqrd/zoneRadiusSqrd;
                if( per < lowerThresh ){                        // Separation
                    float F = ( lowerThresh/per - 1.0f ) * 0.01f;
                    dir.normalize();
                    dir *= F;
                    
                    P1->mAcc += dir;
                    P2->mAcc -= dir;
                } else if( per < higherThresh ){        // Alignment
                    float threshDelta        = higherThresh - lowerThresh;
                    float adjPer                = ( per - lowerThresh )/threshDelta;
                    float F                                = ( 1.0f - cos( adjPer * twoPI ) * -0.5f + 0.5f ) * 0.3f;
                    
                    P1->mAcc += P2->mVelNormal * F;
                    P2->mAcc += P1->mVelNormal * F;
                    
                } else {                                                        // Cohesion
                    float threshDelta        = 1.0f - higherThresh;
                    float adjPer                = ( per - higherThresh )/threshDelta;
                    float F                                = ( 1.0f - ( cos( adjPer * twoPI ) * -0.5f + 0.5f ) ) * 0.1f;
                    
                    dir.normalize();
                    dir *= F;
                    
                    P1->mAcc -= dir;
                    P2->mAcc += dir;
                }
            }
        }
    }
}



void videoCubeController::applyForce( float _zoneRadiusSqrd,float _mHighThresh){
    
	float twoPI = M_PI * 2.0f;
	for( list<videoCube>::iterator vc1 = mVideoCubes.begin(); vc1 != mVideoCubes.end(); ++vc1 ){
        
		list<videoCube>::iterator vc2 = vc1;
		for( ++vc2; vc2 != mVideoCubes.end(); ++vc2 ) {
			ofVec3f dir = vc1->mLoc - vc2->mLoc;
			float distSqrd = dir.lengthSquared();
			
			if( distSqrd < _zoneRadiusSqrd ){	// Neighbor is in the zone
				float percent = distSqrd/_zoneRadiusSqrd;
				
				if( percent < _mHighThresh ){			// Separation
					float F = ( _mHighThresh/percent - 1.0f ) * 0.01f;
					dir.normalize();
					dir *= F;
                    
					vc1->mAcc += dir;
					vc2->mAcc -= dir;
					
				} else {						// Cohesion
					float threshDelta = 1.0f - _mHighThresh;
					float adjustedPercent = ( percent - _mHighThresh )/threshDelta;
					float F = ( 1.0 - ( cos( adjustedPercent * twoPI ) * -0.5f + 0.5f ) ) * 0.05f;
					
					// INTERESTING BUG
					// Use this F instead and lower the thresh to 0.2 after flattening the scene ('f' key)
					// float F = ( 0.5f - ( cos( adjustedPercent * twoPI ) * 0.5f + 0.5f ) ) * 0.15f;
                    
					dir.normalize();
					dir *= F;
                    
					vc1->mAcc -= dir;
					vc2->mAcc += dir;
					
				}
			}
		}
	}
}


#pragma mark Special Maths

ofVec3f  videoCubeController::randVec3f()
{
    float phi = ofRandom((float)M_PI * 2.0f);
    float costheta = ofRandom( -1.0f, 1.0f );

    //float costheta = randFloat( -1.0f, 1.0f );
    
    float rho = sqrt( 1.0f - costheta * costheta );
    float x = rho * cos( phi );
    float y = rho * sin( phi );
    float z = costheta;
    
    return ofVec3f( x, y, z );
}