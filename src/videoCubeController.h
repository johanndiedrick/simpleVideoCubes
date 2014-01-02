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


/*
 this is where we define the number of boxes.
 go crazy.
 */
#define NUM_OF_VIDEOCUBES 100

/*
 this is where we define the number of videos we are going to use as textures for our boxes.
 this can be more or less than the number of boxes,
 because each box has a random number that it selects for its texture.
 so basically it doesn't matter (sorry for the not so great explanation :D )
 */
#define NUM_OF_VIDEOS 5

#endif /* defined(__simpleVideoCubes__videoCubeController__) */
class videoCubeController {
    
public:
    videoCubeController();
    void setup();
    void update();
    void draw();
    
    void addCube();
    void removeCube();
    
    void addVideoPlayer();
    
    int getNumberOfVideos();
    void addVideoURL(string _videoURL);
    void setVideoURLs();
    
    void playVideos();
    void stopVideos();
    void pauseVideos(); //i don't know if there is a difference between stop and play but anyways...
    void muteVideos();

    
    std::list<videoCube> mVideoCubes;
    string mVideoURLs[NUM_OF_VIDEOS];
    //ofVideoPlayer mVideoPlayers[NUM_OF_VIDEOS];
    vector<ofVideoPlayer> mVideoPlayers;
};