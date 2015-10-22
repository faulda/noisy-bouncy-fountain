#ifndef OFCARET_H
#define OFCARET_H

#include "ofMain.h"
#include "ofxBox2d.h"

// Represents a caret-shaped bump- ^ - made out of edges
class ofCaret
{
    public:
        ofCaret();
        ofCaret(ofxBox2d *world, const ofVec2f & center, float width, float height);
        virtual ~ofCaret();
        void draw();
        void update();

    private:

        ofxBox2dEdge *edge;

};

#endif // OFCARET_H
