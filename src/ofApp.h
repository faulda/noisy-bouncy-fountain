#pragma once

#include "ofMain.h"
#include "ofxFFTLive.h"
#include "ofxBox2d.h"
#include "ofFountain.h"
#include "ofCaret.h"

#include <vector>

class ofApp : public ofBaseApp
{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        // this is the function for contacts
        void contactStart(ofxBox2dContactArgs &e);
        void contactEnd(ofxBox2dContactArgs &e);

    private:
        ofxFFTLive fftLive;
		ofxBox2d box2d;

        std::vector<ofFountain*> fountains;
        std::vector<ofCaret*> carets;
        std::vector<std::shared_ptr<ofxBox2dCircle> > circles;

        ofSoundPlayer sound;

        float changeInCirclesPerFrame;
        float changeInVelocity;

        bool useMic;
};
