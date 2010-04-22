#include "Group.h"

#include <iostream>

using namespace std;
using namespace RE330;

Group::~Group() {
    delete nodeList;
}

void Group::light(RenderContext *r, const Matrix4 &C) {
    list<Node*>::const_iterator iter;
    for (iter = nodeList->begin(); iter != nodeList->end(); iter++) {
        Node *n = (*iter);
        n->light(r, C);
    }
}

void Group::draw(RenderContext *r, const Matrix4 &C, const Matrix4 &P) {
    list<Node*>::const_iterator iter;

    for (iter = nodeList->begin(); iter != nodeList->end(); iter++) {
        Node *n = (*iter);
        n->draw(r, C, P);
    }
}

void Group::addChild(Node *child) {
    nodeList->push_back(child);
}

void Group::removeChild(Node *child) {
}
