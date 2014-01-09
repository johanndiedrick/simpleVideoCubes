//
//  videoCubeController.h
//  simpleVideoCubes
//
//  Created by Johann Diedrick on 1/1/14.
//
//

#ifndef __simpleVideoCubes__videoCubeController__
#define __simpleVideoCubes__videoCubeController__

#include <iostream>
#import "ofMain.h"
#include "videoCube.h"
#include "Predator.h"
#include "videoPlayerController.h"


/*
this is where we define the number of video cubes.
*/

#define NUM_OF_VIDEOCUBES 20
#define NUM_OF_PREDATORS 5
#define VIDEOCUBE_SPACING 20.0

#endif /* defined(__simpleVideoCubes__videoCubeController__) */
class videoCubeController {
    
public:
    videoCubeController();
    void setup();
    void setupWithGrid();
    void update();
    void update( bool _flatten );
    void draw(videoPlayerController _vpc);
    
    void addVideoCube(int _x, int _y, int _z);
    void addVideoCubes(int amount);
    void addVideoCubes(int amount, int _x, int _y, int _z);
    void removeVideoCubes(int amount);
    std::list<videoCube> mVideoCubes;
    
    //add predators to break up flocking
    std::list<Predator> mPredators;
    void addPredators(int amount);
    
    
    int mBoxNumber;
    
    //particle system
    void repulseVideoCubes();
    void pullToCenter( ofVec3f _center );
    void applyForce( float _zoneRadiusSqrd, float _mHighThresh);
    void applyForceToVideoCubes( float _zoneRadiusSqrd, float _lowThresh, float _highThresh, float _attractStrength, float _repelStrength, float _orientStrength);
    
    void applyForceToPredators(float _zoneRadiusSqrd, float _mHighThresh, float _mLowThresh);
    
    float mNumParticles;
    ofVec3f mParticleCentroid;
    
    void setSpeed( float _speed );
    
    //special maths stolen from cinder :)
    ofVec3f randVec3f();
  //  ofNoise noise;


    
};