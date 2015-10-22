#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableAntiAliasing();
    ofSetFrameRate(60);

    box2d.init();
    box2d.enableEvents();
    box2d.setGravity(0, 30);

    // physics frame rate
    box2d.setFPS(60);
    box2d.registerGrabbing();

    fftLive.setMirrorData(false);
    fftLive.setup();

	// register the listener so that we get the events
	ofAddListener(box2d.contactStartEvents, this, &ofApp::contactStart);
	ofAddListener(box2d.contactEndEvents, this, &ofApp::contactEnd);

    // Create 3 fountains spaced across the screen. The middle one has slightly higher/larger circles.
    fountains.push_back(
                        new ofFountain(
                                       &box2d,                      // box2d
                                       ofGetWidth() * 1.0f / 6.0f,  // horizontal position
                                       ofGetHeight() / 4.0f,        // vertical position
                                       2.0f,                        // circles per frame
                                       60.0f                        // frame rate
                                       )
                        );

    fountains.push_back(
                        new ofFountain(
                                       &box2d,                      // box2d
                                       ofGetWidth() * 1.0f / 2.0f,  // horizontal position
                                       ofGetHeight() / 4.0f,        // vertical position
                                       2.5f,                        // circles per frame
                                       60.0f                        // frame rate
                                       )
                        );

    fountains[1]->setCircleRadius(4);
    fountains[1]->setInitialVelocity(18);

    fountains.push_back(
                        new ofFountain(
                                       &box2d,                      // box2d
                                       ofGetWidth() * 5.0f / 6.0f,  // horizontal position
                                       ofGetHeight() / 4.0f,        // vertical position
                                       2.0f,                        // circles per frame
                                       60.0f                        // frame rate
                                       )
                        );

    // Make row of carets
    int width = 30;
    int height = 10;
    int start_height = 400;
    int width_spacing = 150;
    int height_spacing = 100;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 7; ++j)
        {
            carets.push_back(
                             new ofCaret(
                                         &box2d,
                                         ofVec2f(j * width_spacing + 75, i * height_spacing + start_height),
                                         width,
                                         height
                                         )
                             );
        }
        ++i;
        for(int j = 0; j < 6; ++j)
        {
            carets.push_back(
                             new ofCaret(
                                         &box2d,
                                         ofVec2f(j * width_spacing + 150, i * height_spacing + start_height),
                                         width,
                                         height
                                         )
                             );
        }
    }

    // Load the sounds
    sound.loadSound("sfx/2.mp3");
    sound.setMultiPlay(true);
    sound.setLoop(false);


    this->changeInCirclesPerFrame = 0.0f;
    this->changeInVelocity = 0.0f;

    this->useMic = true;
}

//--------------------------------------------------------------
void ofApp::update()
{
    box2d.update();

    // Get peak data from mic and use to set fountain velocity
    float * audioData = new float[8];
    fftLive.getFftPeakData(audioData, 8);
    float maxData = 0.0f;
    for(int i = 0; i < 8; ++i)
    {
        maxData = std::max(maxData, audioData[i]);
    }

    delete [] audioData;
    audioData = NULL;

    fftLive.update();


    for(ofFountain *f : fountains)
    {
        if(useMic)
        {
            // Set fountain velocity based on max data
            f->setInitialVelocity(20 * maxData);
        }
        else
        {
            // Update fountain circle frequency and velocity based on user input.
            f->increaseCirclesPerFrame(this->changeInCirclesPerFrame);
            f->increaseInitialVelocity(this->changeInVelocity);
        }


        f->update();
    }

    this->changeInCirclesPerFrame = 0.0f;
    this->changeInVelocity = 0.0f;
}

//--------------------------------------------------------------
void ofApp::draw()
{
    box2d.drawGround();
    //fftLive.draw();

    for(ofCaret *c : carets)
    {
        c->draw();
    }

    for(ofFountain *f : fountains)
    {
        f->draw();
    }
}

//--------------------------------------------------------------
void ofApp::contactStart(ofxBox2dContactArgs &e)
{
    if(e.a != NULL && e.b != NULL)
    {
        // edge = 1
        // circle = 0
        // Only play a sound 30% of the time, otherwise the sound of so many circles is too overwhelming.
		if((e.a->GetType() != b2Shape::e_circle || e.b->GetType() != b2Shape::e_circle)
            && (ofRandom(1.0f) < 0.3f))
        {
            sound.play();
		}
	}
}

//--------------------------------------------------------------
void ofApp::contactEnd(ofxBox2dContactArgs &e)
{

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    // Up increases circles and velocity
    if(key == OF_KEY_UP)
    {
        this->changeInCirclesPerFrame = 0.1f;
        this->changeInVelocity = 1.0f;
    }
    // Down decreases circles and velocity
    else if(key == OF_KEY_DOWN)
    {
        this->changeInCirclesPerFrame = -0.1f;
        this->changeInVelocity = -1.0f;
    }
    else if(key == 'm')
    {
        useMic = !useMic;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
