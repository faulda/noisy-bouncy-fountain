#ifndef OFFOUNTAIN_H
#define OFFOUNTAIN_H

#include "ofMain.h"
#include "ofxBox2d.h"

#include <vector>

class ofFountain
{
    public:
        ofFountain();
        ofFountain(ofxBox2d *box2d, float x, float y, float circlesPerFrame, float frameRate);
        virtual ~ofFountain();
        void draw();
        void update();
        void increaseCirclesPerFrame(float increment);
        void setCirclesPerFrame(float circlesPerFrame);
        void setInitialVelocity(float velocity);
        void increaseInitialVelocity(float increment);
        void setSecondsBetweenCleanups(float seconds);
        void setCircleRadius(float radius);

    private:
        void cleanupExtraCircles();
        void addCircle();

        float circlesPerFrame;
        float xPosition;
        float yPosition;
        float frameRate;
        float circlesToDraw;
        float secondsBetweenCleanups;
        float initialVelocity;
        float circleRadius;

        ofxBox2d *box2d;
        std::vector<ofxBox2dCircle* > circles;
};

#endif // OFFOUNTAIN_H
