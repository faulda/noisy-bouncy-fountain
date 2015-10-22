#include "ofCaret.h"

ofCaret::ofCaret()
{
    edge = NULL;
}

ofCaret::ofCaret(ofxBox2d *world, const ofVec2f & center, float width, float height)
{
    edge = new ofxBox2dEdge();

    // caret is centered at a rectangle with center "center"
    // Goes from bottom left part of rectangle, to top center, to bottom right
    edge->addVertex(center.x - (width / 2.0), center.y + (height / 2.0));
    edge->addVertex(center.x, center.y - (height / 2.0));
    edge->addVertex(center.x + (width / 2.0), center.y + (height / 2.0));

	edge->create(world->getWorld());
}

ofCaret::~ofCaret()
{
    delete edge;
}

void ofCaret::draw()
{
    edge->draw();
}

void ofCaret::update()
{
    edge->update();
}
