#pragma once

#include "ofMain.h"
#include "videoCubes.h"
#include "ofxJSONElement.h"

/*
this is where we define our search query.
it MUST be one string, with words seperated by a + sign
*/
#define SEARCH_QUERY "neon+genesis+evangelion"

/*
this is where we define the number of boxes. 
go crazy.
*/
#define NUM_OF_BOXES 100

/*
this is where we define the number of videos we are going to use as textures for our boxes.
this can be more or less than the number of boxes, 
 because each box has a random number that it selects for its texture. 
 so basically it doesn't matter (sorry for the not so great explanation :D )
*/
#define NUM_OF_VIDEOS 5


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void drawIntoFBO();
        string createYoutubeSearchString(string ytsearchstr);
		
    ofVideoPlayer vids[NUM_OF_VIDEOS];
    
    //cam and light setup
    ofLight light; // creates a light and enables lighting
    ofEasyCam cam; // add mouse controls for camera movement

    //videocubes setup
    videoCube vidCubes[NUM_OF_BOXES];
    int numberOfCubes;
    
    string youtube_search_string;
    
    ofFbo rgbaFboFloat; // with alpha
    
    int fadeAmnt;
    
    ofShader bloomShader;

    
};
