#include "Shape3D.h"
#include <iostream>

using namespace std;
using namespace RE330;

void Shape3D::draw(RenderContext *r, Matrix4 *C) {

    cout << "Draw!" << endl;

    Matrix4 mView = (*C) * (*t);
    r->setModelViewMatrix(mView);

    if (_mat) {
        r->setMaterial(_mat);
    } else {
        r->setMaterial(&Material());
    }
    r->render(_obj);
}
