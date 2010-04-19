#include "Shape3D.h"
#include <iostream>

using namespace std;
using namespace RE330;

void Shape3D::draw(RenderContext *r, const Matrix4 &C) {
    r->setModelViewMatrix(C * t);

    if (_mat) {
        r->setMaterial(_mat);
    } else {
        r->setMaterial(&Material());
    }
    r->render(_obj);
}
