//
//  videoPlayerController.h
//  simpleVideoCubes
//
//  Created by Johann Diedrick on 1/2/14.
//
//

#ifndef __simpleVideoCubes__videoPlayerController__
#define __simpleVideoCubes__videoPlayerController__

#include <iostream>
#include "ofMain.h"

#define NUM_OF_VIDEOS 5

class videoPlayerController {
    
public:
    videoPlayerController();
    void setup();
    void update();
    void draw();
    
    void addVideoPlayer();
    void addVideoURL(string _videoURL);
    void loadVideos();
    void playVideos();
    void muteVideos();
    void pauseVideos();
    
    int getNumberOfVideos();

    
    vector<ofVideoPlayer> mVideoPlayers;
    vector<string> mVideoURLs;
    
};


#endif /* defined(__simpleVideoCubes__videoPlayerController__) */
