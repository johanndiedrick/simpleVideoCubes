//
//  videoPlayerController.cpp
//  simpleVideoCubes
//
//  Created by Johann Diedrick on 1/2/14.
//
//

#include "videoPlayerController.h"

videoPlayerController::videoPlayerController(){
    
}

void videoPlayerController::setup(){
    cout << "nothing here yet" << endl;
}

void videoPlayerController::update(){
    for(vector<ofVideoPlayer>::iterator vp = mVideoPlayers.begin(); vp != mVideoPlayers.end(); ++vp){
        vp->update();
    }
    
}

void videoPlayerController::draw(){
// we could use this function to draw our videos in a debug mode screen, might be handy later
}

void videoPlayerController::addVideoPlayer(){
    
    ofVideoPlayer videoPlayer;
    mVideoPlayers.push_back(videoPlayer);
    
}

void videoPlayerController::addVideoURL(string _videoURL){
   
    mVideoURLs.push_back(_videoURL);
    
}

void videoPlayerController::loadVideos(){

    for (int i =0; i<mVideoPlayers.size(); i++){
        mVideoPlayers[i].loadMovie(mVideoURLs[i]);
    }

}
void videoPlayerController::playVideos(){

    for(vector<ofVideoPlayer>::iterator vp = mVideoPlayers.begin(); vp != mVideoPlayers.end(); ++vp){
        vp->play();
    }
    
}

void videoPlayerController::muteVideos(){
    
    for(vector<ofVideoPlayer>::iterator vp = mVideoPlayers.begin(); vp != mVideoPlayers.end(); ++vp){
        vp->setVolume(0.0);
    }
    
}

int videoPlayerController::getNumberOfVideos(){
    
    return NUM_OF_VIDEOS;

};

