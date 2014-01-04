#pragma once

#include "ofMain.h"
#include "videoCubeController.h"
#include "videoPlayerController.h"
#include "ofxJSONElement.h"
#include "ofxGameCamera.h"
#include "ofxUI.h"

/*
this is where we define our search query.
if the query is multple words, it MUST be one string, 
with words seperated by a + sign
*/

#define SEARCH_QUERY "neon+genesis+evangelion"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
    
        //controllers
        videoCubeController mVideoCubeController;
        videoPlayerController mVideoPlayerController;
    
        //cam and light setup
        ofLight light; // creates a light and enables lighting
        ofxGameCamera cam; // add mouse controls for camera movement
        ofVec3f mCenter;
    
        //fbo
        ofFbo rgbaFboFloat; // with alpha
        void drawIntoFBO();
        int fadeAmnt;
    
        //shader
        ofShader bloomShader;
    
        //youtube scraping
        string youtube_search_string;
        string createYoutubeSearchString(string ytsearchstr);
    
        //gui
        ofxUICanvas *gui;
        void setupUI();
        void exit();
        void guiEvent(ofxUIEventArgs &e);
    
};
