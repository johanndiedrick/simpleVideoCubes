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

#endif /* defined(__simpleVideoCubes__videoCubeController__) */
class videoCubeController {
    
public:
    videoCubeController();
    void setup();
    void update();
    void draw(videoPlayerController _vpc);

    std::list<videoCube> mVideoCubes;
    
    int mBoxNumber;

};