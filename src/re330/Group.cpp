#include "Group.h"

using namespace std;
using namespace RE330;

Group::~Group() {
    while (nodeList && !nodeList->empty()) {
        Node *n = nodeList->front();
        nodeList->pop_front();
        delete n;
    }
    delete nodeList;
}

void Group::light(RenderContext *r, Matrix4 *C) {
    list<Node*>::const_iterator iter;
    for (iter = nodeList->begin(); iter != nodeList->end(); iter++) {
        Node *n = (*iter);
        n->light(r, C);
    }
}

void Group::draw(RenderContext *r, Matrix4 *C) {
    list<Node*>::const_iterator iter;
    for (iter = nodeList->begin(); iter != nodeList->end(); iter++) {
        Node *n = (*iter);
        n->draw(r, C);
    }
}

void Group::addChild(Node *child) {
    nodeList->push_back(child);
}

void Group::removeChild(Node *child) {
}
