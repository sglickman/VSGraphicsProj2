#include "TransformGroup.h"

using namespace std;
using namespace RE330;

void TransformGroup::light(RenderContext *r, Matrix4 *C) {
    Group::light(r, &((*C)*(*t)));
}

void TransformGroup::draw(RenderContext *r, Matrix4 *C) {
    Group::draw(r, &((*C)*(*t)));
}
