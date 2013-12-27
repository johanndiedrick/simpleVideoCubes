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
    
    string youtube_dl = ofToDataPath("youtube-dl", true);
    
    
    // Open a Youtube video feed
    // http://code.google.com/apis/youtube/2.0/developers_guide_protocol_video_feeds.html
    // http://gdata.youtube.com/feeds/api/standardfeeds/most_popular?v=2&alt=json
    // http://gdata.youtube.com/feeds/api/videos?q=skateboarding+dog&alt=json
    ofxJSONElement youtube;
    youtube.open("http://gdata.youtube.com/feeds/api/videos?q=slow+loris&alt=json");
    
    // Loop through all of the feed->entry items in the feed
    int numVideos = min(4, (int)youtube["feed"]["entry"].size());
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
        //cout << command << endl;
        
        // Get the full (nasty) URL of the raw video
        string vid_url = ofSystemCall(command);
        //cout << vid_url << endl;
        
        // Load the video (from a url!) and start playing it
        vids[i].loadMovie(vid_url);
        vids[i].play();
    }

    
    //gl setup for our boxes
    ofSetVerticalSync(true);
	ofEnableDepthTest();
    ofEnableNormalizedTexCoords();
    //randomBox = 0;

    

}

//--------------------------------------------------------------
void testApp::update(){
    
    for(int i=0; i<4; i++)
    {
        vids[i].update();
    }

}

//--------------------------------------------------------------
void testApp::draw(){

    /*
     We're not gonna draw all of the videos, but we could if we wanted to...
     
    vids[0].draw(0, 0, 320, 240);
    vids[1].draw(320, 0, 320, 240);
    vids[2].draw(0, 240, 320, 240);
    vids[3].draw(320, 240, 320, 240);
    
    */
    
    ofBackground(0, 0, 0);
	
	float movementSpeed = .1;
	float cloudSize = ofGetWidth() / 2;
	float maxBoxSize = 100;
	float spacing = 1;
	//int boxCount = 4;
	
	cam.begin();
	
	for(int i = 0; i < 100; i++) {
        
        int number = vidCubes[i].videoNumber;
        //grab a random number
        
        //randomBox = ofRandom(3);
        
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
		
		//ofLogo.bind();
        vids[number].getTextureReference().bind();
		ofFill();
		//ofSetColor(255);
		ofDrawBox(boxSize);
        //		ofLogo.unbind();
         vids[number].getTextureReference().unbind();
		
		ofNoFill();
		//ofSetColor(ofColor::fromHsb(sinf(t) * 128 + 128, 255, 255));
		//ofDrawBox(boxSize);
		
		ofPopMatrix();
	}
	
	cam.end();

    
    
}
