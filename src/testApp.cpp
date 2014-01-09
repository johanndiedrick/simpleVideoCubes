#include "testApp.h"

string ofSystemCall(string command)
{
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    result.erase(remove(result.begin(), result.end(), '\n'), result.end());
    return result;
}

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    //setup background
    ofSetBackgroundAuto(false);
    ofBackground(0, 0, 0);
    
    red = 255;
    green, blue = 0;
    
    //set up some params for our particle system, this should all be in the ui
    //we should also load this in from the ui! to do...
    mZoneRadius = 80.0f;
    mLowThresh = 0.5f;
    mHighThresh = 0.8f;
    mAttractStrength = 0.005f;
    mRepelStrength = 0.01f;
    mOrientStrength = 0.01f;
    mFlatten = false;

    //setup ui
    setupUI();
    
    //setup camera
    cam.setup();
    mCenter = ofVec3f(0);

    string youtube_dl = ofToDataPath("youtube-dl", true);
    
    //create our youtube search string
    //youtube_search_string = createYoutubeSearchString(SEARCH_QUERY);
    
    ofxJSONElement youtube;
    //youtube.open(youtube_search_string);
    
    //you can also just open a playlist
    youtube.open("http://gdata.youtube.com/feeds/api/playlists/PL3ngyh53O02CnHBb69HMZNwdvWo8w3MKW?&alt=json");
    
    //setup our video player and video cube controllers
    mVideoCubeController.setup();

    mVideoPlayerController.setup();
    // Loop through all of the feed->entry items in the feed
    int numVideos = min(mVideoPlayerController.getNumberOfVideos(), (int)youtube["feed"]["entry"].size());
    for(int i=0; i<numVideos; i++)
    {
        // use ofToDataPath to get the complete path to the youtube-dl program
        // https://github.com/rg3/youtube-dl
        // In each one, there will be a "link" item that contains multiple "href" strings
        // We want the first href string inside the link item
        string youtube_url = youtube["feed"]["entry"][i]["link"][UInt(0)]["href"].asString();
        cout << youtube_url << endl;
        
        // Assemble a command just like the one you would use on the command line
        // Format 18 = H264  (see http://en.wikipedia.org/wiki/YouTube#Quality_and_codecs)
        string command = youtube_dl+" --get-url --format 18 "+youtube_url;
        ///cout << command << endl;
        
        // Get the full (nasty) URL of the raw video
        string vid_url = ofSystemCall(command);
        //cout << vid_url << endl;
        
        //create a new video player and add it to our video player vector
        mVideoPlayerController.addVideoPlayer();
        mVideoPlayerController.addVideoURL(vid_url);
    }
    
    mVideoPlayerController.loadVideos();
    mVideoPlayerController.playVideos();
    mVideoPlayerController.muteVideos();
    

    rgbaFboFloat.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F_ARB);
	rgbaFboFloat.begin();
	ofClear(255,255,255, 0);
    rgbaFboFloat.end();

    //load shaders
    bloomShader.load("shaders/bloom.vert", "shaders/bloom.frag");

}

//--------------------------------------------------------------
void testApp::update(){
    
    if (mLowThresh > mHighThresh) mLowThresh = mHighThresh;
    //update our videos
    mVideoPlayerController.update();
    
    //apply our forces to our video cubes
    mVideoCubeController.applyForceToVideoCubes( mZoneRadius * mZoneRadius, mLowThresh, mHighThresh, mAttractStrength, mRepelStrength, mOrientStrength );
    mVideoCubeController.applyForceToPredators(mZoneRadius, 0.4f, 0.7f);
    //pull our video cube to the center
    mVideoCubeController.pullToCenter( mCenter );
    
    //update our video cubes
    mVideoCubeController.update( mFlatten );
    
    //gl stuff
    ofEnableAlphaBlending();
    rgbaFboFloat.begin();
    drawIntoFBO();
	rgbaFboFloat.end();
    rgbaFboFloat.getTextureReference(0);
}

//--------------------------------------------------------------
void testApp::draw(){
    //changeBackgroundColor();

    ofPushStyle();
	ofFill();
	ofSetColor(0,0,0, fadeAmnt);
	ofRect(0,0,ofGetWindowWidth(),ofGetWindowHeight());
    ofPopStyle();
    
    //draw our fbo with some cute shaders on top xoxo
    bloomShader.begin();
    bloomShader.setUniformTexture("texture", rgbaFboFloat.getTextureReference(), 1);
    rgbaFboFloat.draw(0,0);
    bloomShader.end();

}


//--------------------------------------------------------------
void testApp::drawIntoFBO(){

    ofClear(0,0,0, 0);
    cam.begin();
    mVideoCubeController.draw(mVideoPlayerController);
    cam.end();
    //changeBackgroundColor();
    
}

//--------------------------------------------------------------
string testApp::createYoutubeSearchString(string ytsearchstr){
    
    string yt_search_str;
    
    //construct our string for our youtube query
    yt_search_str = "http://gdata.youtube.com/feeds/api/videos?q=";
    yt_search_str += ytsearchstr;
    yt_search_str += "&alt=json";
    
    return yt_search_str;
    
}

#pragma mark Mouse Interactions

void testApp::mousePressed(int x, int y, int button){
   // mVideoCubeController.addVideoCube( x, y ,0 );
}
void testApp::mouseReleased(int x, int y, int button){
    //
}

#pragma mark GUI

void testApp::setupUI(){
    
    gui = new ofxUICanvas(0, 0, 320, 400);
    
    //add our widgets
    gui->addWidgetDown(new ofxUILabel("Video Cubes", OFX_UI_FONT_LARGE));
    gui->addWidgetDown(new ofxUISlider(304,16,0.0,100.0,100.0,"FADE AMOUNT"));
    gui->addWidgetDown(new ofxUIToggle(32, 32, false, "FULLSCREEN"));
    gui->addWidgetDown(new ofxUIToggle(32, 32, false, "TOGGLE PLAYBACK"));
    gui->addWidgetDown(new ofxUIToggle(32, 32, false, "TOGGLE FLATTEN"));
    gui->addWidgetDown(new ofxUISlider(304,16,0.0,1.0,100.0,"HIGH THRESHOLD"));
    gui->addWidgetDown(new ofxUISlider(304,16,0.0,1.0,100.0,"LOW THRESHOLD"));
    gui->addWidgetDown(new ofxUISlider(304,16,0.0,1.0,100.0,"ATTRACT STRENGTH"));
    gui->addWidgetDown(new ofxUISlider(304,16,0.0,1.0,100.0,"REPEL STRENGTH"));
    gui->addWidgetDown(new ofxUISlider(304,16,0.0,1.0,100.0,"ORIENTATION STRENGTH"));
    gui->addWidgetDown(new ofxUISlider(304,16,0.0,1.0,100.0,"VIDEOCUBE DECELERATION"));





    
    //boilerplate callback listener
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent);
    gui->loadSettings("GUI/guiSettings.xml");
    
}

void testApp::exit(){
    gui->saveSettings("GUI/guiSettings.xml");
    delete gui;
}

void testApp::guiEvent(ofxUIEventArgs &e){
    
    if(e.widget->getName() == "FADE AMOUNT")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        fadeAmnt = (int)slider->getScaledValue();
        cout << "changing fade amount: " << fadeAmnt<< endl;
    }
    
    else if(e.widget->getName() == "FULLSCREEN")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ofSetFullscreen(toggle->getValue());
    }
    
    else if(e.widget->getName() == "TOGGLE PLAYBACK")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        if (toggle->getValue() == true){
            mVideoPlayerController.playVideos();
        }
        if (toggle->getValue() == false){
            mVideoPlayerController.pauseVideos();
        }
    }
    else if(e.widget->getName() == "TOGGLE FLATTEN")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        mFlatten = toggle->getValue();
    }
    
    else if(e.widget->getName() == "HIGH THRESHOLD")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        mHighThresh = slider->getScaledValue();
    }
    
    else if(e.widget->getName() == "LOW THRESHOLD")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        mLowThresh = slider->getScaledValue();
    }
    
    else if(e.widget->getName() == "ATTRACT THRESHOLD")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        mAttractStrength = slider->getScaledValue();
    }
    
    else if(e.widget->getName() == "REPEL THRESHOLD")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        mRepelStrength = slider->getScaledValue();
    }
    
    else if(e.widget->getName() == "ORIENTATION THRESHOLD")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        mOrientStrength = slider->getScaledValue();
    }
    
    else if(e.widget->getName() == "VIDEOCUBE DECELERATION")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        mVideoCubeController.setSpeed(slider->getScaledValue());
    }
    
}

void testApp::keyPressed(int key){
    if(key == 'l'){
        gui->toggleVisible();
    }
}

void testApp::changeBackgroundColor(){
    if (red == 255 && blue == 0) {
        green++;
    }
    if(green == 255 && red > 0){
        red--;
    }
    if(red == 0 && green == 255){
        blue++;
    }
    if (blue == 255 && green > 0){
        green--;
    }
    if (green == 0 && blue == 255){
        red++;
    }
    if(red == 255 && blue > 0){
        blue--;
    }
    ofBackground(red, green, blue);
}
