#pragma once

#include "ofMain.h"
#include "videoCubes.h"
#include "ofxJSONElement.h"


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
    ofVideoPlayer vids[4];
    
    //cam and light setup
    ofLight light; // creates a light and enables lighting
    ofEasyCam cam; // add mouse controls for camera movement

    //videocubes setup
    videoCube vidCubes[100];
    int numberOfCubes;
    
    string search_query;
};
