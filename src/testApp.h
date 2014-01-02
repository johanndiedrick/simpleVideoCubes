#pragma once

#include "ofMain.h"
#include "videoCubeController.h"
#include "videoPlayerController.h"
#include "ofxJSONElement.h"

/*
this is where we define our search query.
it MUST be one string, with words seperated by a + sign
*/
#define SEARCH_QUERY "neon+genesis+evangelion"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void drawIntoFBO();
        string createYoutubeSearchString(string ytsearchstr);
    
        videoCubeController mVideoCubeController;
        videoPlayerController mVideoPlayerController;
    
        //cam and light setup
        ofLight light; // creates a light and enables lighting
        ofEasyCam cam; // add mouse controls for camera movement
    
        ofFbo rgbaFboFloat; // with alpha
    
        int fadeAmnt;
    
        ofShader bloomShader;
    
        //youtube scraping
        string youtube_search_string;
    
};
