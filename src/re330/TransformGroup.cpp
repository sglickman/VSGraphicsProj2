#include "TransformGroup.h"

using namespace std;
using namespace RE330;

void TransformGroup::light(RenderContext *r, const Matrix4 &C) {
    Group::light(r, C*t);
}

void TransformGroup::draw(RenderContext *r, const Matrix4 &C, const Matrix4 &P, bool culling) {
    Group::draw(r, C*t, P, culling);
}
