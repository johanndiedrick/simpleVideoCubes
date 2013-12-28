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

    ofBackground(0,0,0);
	ofSetFrameRate(60);

    string youtube_dl = ofToDataPath("youtube-dl", true);
    
    //create our youtube search string
    youtube_search_string = createYoutubeSearchString(SEARCH_QUERY);
    
    ofxJSONElement youtube;
    youtube.open(youtube_search_string);
    
    //you can also just open a playlist
    youtube.open("http://gdata.youtube.com/feeds/api/playlists/PL3ngyh53O02CnHBb69HMZNwdvWo8w3MKW?&alt=json");
    
    // Loop through all of the feed->entry items in the feed
    int numVideos = min(NUM_OF_VIDEOS, (int)youtube["feed"]["entry"].size());
    for(int i=0; i<numVideos; i++)
    {
        // use ofToDataPath to get the complete path to the youtube-dl program
        // https://github.com/rg3/youtube-dl
        // In each one, there will be a "link" item that contains multiple "href" strings
        // We want the first href string inside the link item
        string youtube_url = youtube["feed"]["entry"][i]["link"][UInt(0)]["href"].asString();
        //cout << youtube_url << endl;
        
        // Assemble a command just like the one you would use on the command line
        // Format 18 = H264  (see http://en.wikipedia.org/wiki/YouTube#Quality_and_codecs)
        string command = youtube_dl+" --get-url --format 18 "+youtube_url;
        //cout << command << endl;
        
        // Get the full (nasty) URL of the raw video
        string vid_url = ofSystemCall(command);
        cout << vid_url << endl;
        
        // Load the video (from a url!) and start playing it
        vids[i].loadMovie(vid_url);
        vids[i].play();
        vids[i].setVolume(0.0); //mute all the videos if you like, otherwise its hella annoying
    }
    
    
    //gl setup for our boxes
    ofSetVerticalSync(true);
	//ofEnableDepthTest();
    //ofEnableNormalizedTexCoords();

    rgbaFboFloat.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F_ARB);
	rgbaFboFloat.begin();
	ofClear(255,255,255, 0);
    rgbaFboFloat.end();

    bloomShader.load("shaders/bloom.vert", "shaders/bloom.frag");


}

//--------------------------------------------------------------
void testApp::update(){
    
    ofEnableAlphaBlending();
    
    for(int i=0; i<NUM_OF_VIDEOS; i++)
    {
        vids[i].update();
    }

    rgbaFboFloat.begin();
    drawIntoFBO();
	rgbaFboFloat.end();
    rgbaFboFloat.getTextureReference(0);


    
}

//--------------------------------------------------------------
void testApp::draw(){
    bloomShader.begin();
    bloomShader.setUniformTexture("texture", rgbaFboFloat.getTextureReference(), 1);
    rgbaFboFloat.draw(0,0);
    bloomShader.end();

}


//--------------------------------------------------------------
void testApp::drawIntoFBO(){
    //we clear the fbo if c is pressed.
	//this completely clears the buffer so you won't see any trails
	if( ofGetKeyPressed('c') ){
		ofClear(255,255,255, 0);
	}
	
	//some different alpha values for fading the fbo
	//the lower the number, the longer the trails will take to fade away.
	fadeAmnt = 50;
	if(ofGetKeyPressed('1')){
		fadeAmnt = 1;
	}else if(ofGetKeyPressed('2')){
		fadeAmnt = 5;
	}else if(ofGetKeyPressed('3')){
		fadeAmnt = 15;
	}
    
    //for now, we'll clear the fbo because ofGetDepthTest doesn't seem to work with the boxes..looking into it
    ofClear(255,255,255, 0);

	//1 - Fade Fbo
	
	//this is where we fade the fbo
	//by drawing a rectangle the size of the fbo with a small alpha value, we can slowly fade the current contents of the fbo.
    /*
    ofPushStyle();
	ofFill();
	ofSetColor(0,0,0, fadeAmnt);
	ofRect(0,0,ofGetWindowWidth(),ofGetWindowHeight());
    ofPopStyle();
     */
    
	//2 - Draw graphics
	
	//ofNoFill();
	//ofSetColor(255,255,255);
	
    float movementSpeed = .1;
	float cloudSize = ofGetWidth() / 2;
	float maxBoxSize = NUM_OF_BOXES;
	float spacing = 1;
	
    	cam.begin();
	
	for(int i = 0; i < NUM_OF_BOXES; i++) {
        
        int number = vidCubes[i].videoNumber;
        
		ofPushMatrix();
		
		float t = (ofGetElapsedTimef() + i * spacing) * movementSpeed;
		ofVec3f pos(
                    ofSignedNoise(t, 0, 0),
                    ofSignedNoise(0, t, 0),
                    ofSignedNoise(0, 0, t));
		
		float boxSize = maxBoxSize * ofNoise(pos.x, pos.y, pos.z);
		
		pos *= cloudSize;
		ofTranslate(pos);
		//ofRotateX(pos.x);
		//ofRotateY(pos.y);
		//ofRotateZ(pos.z);
		//ofEnableDepthTest();
        ofEnableNormalizedTexCoords();

        vids[number].getTextureReference().bind();
		ofFill();
        //ofPushMatrix();
        ofEnableDepthTest();
		ofDrawBox(boxSize);
        ofDisableDepthTest();
        //ofPopStyle();
        vids[number].getTextureReference().unbind();
        
        ofDisableNormalizedTexCoords();
		
		//ofNoFill();
		//ofSetColor(ofColor::fromHsb(sinf(t) * 128 + 128, 255, 255));
		//ofDrawBox(boxSize);
		
		ofPopMatrix();
    }
    cam.end();
    
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
