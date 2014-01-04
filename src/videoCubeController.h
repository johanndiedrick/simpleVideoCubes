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
#include "videoCube.h"
#include "videoPlayerController.h"


/*
this is where we define the number of video cubes.
*/

#define NUM_OF_VIDEOCUBES 100
#define VIDEOCUBE_SPACING 20.0;

#endif /* defined(__simpleVideoCubes__videoCubeController__) */
class videoCubeController {
    
public:
    videoCubeController();
    void setup();
    void setupWithGrid();
    void update();
    void draw(videoPlayerController _vpc);
    
    void addVideoCube(int _x, int _y, int _z);
    void addVideoCubes(int amount, int _x, int _y, int _z);
    void removeVideoCubes(int amount);

    std::list<videoCube> mVideoCubes;
    
    int mBoxNumber;
    
    //particle system
    void repulseVideoCubes();
    void pullToCenter( ofVec3f _center );

};