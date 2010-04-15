#include "Shape3D.h"

using namespace RE330;

void Shape3D::draw(RenderContext *r, Matrix4 *C) {
    Matrix4 mView = (*C) * (*t);
    r->setModelViewMatrix(mView);
}
