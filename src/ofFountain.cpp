#include "ofFountain.h"

#include <algorithm>
#include <iostream>

ofFountain::ofFountain() { }

ofFountain::ofFountain(ofxBox2d *box2d, float x, float y, float circlesPerFrame, float frameRate)
{
    this->box2d = box2d;
    this->xPosition = x;
    this->yPosition = y;
    this->circlesPerFrame = circlesPerFrame;
    this->frameRate = frameRate;
    this->circlesToDraw = 0;
    this->secondsBetweenCleanups = 0.5f;
    this->circleRadius = 2.0f;
    this->initialVelocity = 10.0f;
}

ofFountain::~ofFountain()
{
    // Draw all the circles
    for(ofxBox2dCircle* c : circles)
    {
        delete c;
    }
    box2d = NULL;
}

void ofFountain::draw()
{
    // Draw all the circles
    for(ofxBox2dCircle* c : circles)
    {
        c->draw();
    }
}

void ofFountain::update()
{
    // Cleanup old circles every once in a while. Because of the inefficiencies
    // of performing many small delete operations from a vector, we instead do
    // a sweep of the whole vector every so often and delete all necessary circles
    // in that pass. The deletion is done in a manner that avoids excessive looping
    // over the vector, meaning that during each deletion sweep the vector is
    // iterated over only once and at the end only contains those circles which do
    // not need to be deleted.
    if(ofGetFrameNum() % ((int)(frameRate * secondsBetweenCleanups) + 1) == 0)
    {
        cleanupExtraCircles();
    }

    // Add new circles
    circlesToDraw += circlesPerFrame;
    while(circlesToDraw > 1.0)
    {
        addCircle();
        --circlesToDraw;
    }

    // Update all the circles
    for(ofxBox2dCircle *c : circles)
    {
        c->update();
    }
}

// Modified version of a ofxBox2dBaseShape.h function that uses a normal pointer
bool shouldRemoveOffScreen(ofxBox2dBaseShape* shape) {
    return !ofRectangle(0, 0, ofGetWidth(), ofGetHeight()).inside(shape->getPosition());
}

// Cleans up extra circles that are off the screen by deleting them and
// removing them from the vector. Makes 1 pass over the vector, deleting
// unneeded items and shifting the rest over towards the beginning, resizing
// the vector at the end.
void ofFountain::cleanupExtraCircles()
{
    int last = 0;
    for(int i=0; i<circles.size(); ++i, ++last)
    {
        // Create a shared_ptr that doesn't delete the Circle, since the ofxBox2dBaseShape
        // function shouldRemoveOffScreen requires one.
        while(i < circles.size() && shouldRemoveOffScreen(circles[i]))
        {
            // While at a circle we need to remove, delete it and move on
            circles[i]->destroy();
            delete circles[i];
            circles[i] = NULL;
            ++i;
        }

       if(i >= circles.size()) break;

       circles[last] = circles[i];
    }

    circles.resize(last);
}

void ofFountain::setCirclesPerFrame(float circlesPerFrame)
{
    this->circlesPerFrame = circlesPerFrame;
}

void ofFountain::increaseCirclesPerFrame(float increment)
{
    this->circlesPerFrame += increment;
}

void ofFountain::addCircle()
{
    circles.push_back(new ofxBox2dCircle);
    circles.back()->setPhysics(3.0, 0.3, 0.1);
    circles.back()->enableGravity(true);
    circles.back()->setMassFromShape = true;
    circles.back()->setup(box2d->getWorld(), xPosition + ofRandomf() * 3, yPosition + ofRandomf(), circleRadius);
    circles.back()->setVelocity(ofRandomf(), -1 * initialVelocity);
}

void ofFountain::setSecondsBetweenCleanups(float seconds)
{
    this->secondsBetweenCleanups = seconds;
}

void ofFountain::setInitialVelocity(float velocity)
{
    this->initialVelocity = velocity;
}

void ofFountain::increaseInitialVelocity(float increment)
{
    this->initialVelocity += increment;
}

void ofFountain::setCircleRadius(float radius)
{
    this->circleRadius = radius;
}
