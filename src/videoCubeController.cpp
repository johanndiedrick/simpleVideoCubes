//
//  videoCubeController.cpp
//  simpleVideoCubes
//
//  Created by Johann Diedrick on 1/1/14.
//
//

#include "videoCubeController.h"

videoCubeController::videoCubeController(){
    
}

void videoCubeController::setup(){
    //create out video urls array
   // mVideoURLs = mVideoURLs[NUM_OF_VIDEOS];
    
    //create our video cubes
    for(int i=0; i<NUM_OF_VIDEOCUBES; i++){
        addCube();
    }
 
}

void videoCubeController::update(){

    
    for(list<videoCube>::iterator vc = mVideoCubes.begin(); vc != mVideoCubes.end(); ++vc){
        vc->update();
    }
}

void videoCubeController::draw(){
    for(list<videoCube>::iterator vc = mVideoCubes.begin(); vc != mVideoCubes.end(); ++vc){
        vc->draw();
    }
}

#pragma mark Adding and Removing Video Cubes

void videoCubeController::addCube(){
    mVideoCubes.push_back(videoCube());
}

void videoCubeController::removeCube(){
    mVideoCubes.pop_back();
}

#pragma mark Managing Video URLs for Video Cubes

int videoCubeController::getNumberOfVideos(){
    return NUM_OF_VIDEOS;
}
void videoCubeController::addVideoURL(string _videoURL){
 //   mVideoURLs[i] = _videoURL;
}

void videoCubeController::addVideoPlayer(){
    ofVideoPlayer player;
    mVideoPlayers.push_back(player);
}

void videoCubeController::setVideoURLs(){
    //set the value for each video player
    
    for(vector<ofVideoPlayer>::iterator vp = mVideoPlayers.begin(); vp != mVideoPlayers.end(); ++vp){
        for(int i=0; i<NUM_OF_VIDEOS; i++){
            vp->loadMovie(mVideoURLs[i]);
        }
        cout << vp->isLoaded() << endl;
    }
    
//    for(int i=0; i<NUM_OF_VIDEOS; i++){
//        mVideoPlayers[i].loadMovie(mVideoURLs[i]);
//    }
}

#pragma mark Playback controllers for video players
void videoCubeController::playVideos(){
    for(vector<ofVideoPlayer>::iterator vp = mVideoPlayers.begin(); vp != mVideoPlayers.end(); ++vp){
        vp->play();
    }
}
void videoCubeController::stopVideos(){
    //
}
void videoCubeController::pauseVideos(){
    //
}

void videoCubeController::muteVideos(){
    for(vector<ofVideoPlayer>::iterator vp = mVideoPlayers.begin(); vp != mVideoPlayers.end(); ++vp){
        vp->setVolume(1.0);
    }
  
}