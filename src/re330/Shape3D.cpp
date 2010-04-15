#include "Shape3D.h"
#include <iostream>

using namespace std;
using namespace RE330;

void Shape3D::draw(RenderContext *r, Matrix4 *C) {

    cout << "Draw!" << endl;

    Matrix4 mView = (*C) * (*t);
    r->setModelViewMatrix(mView);

    r->setMaterial(_mat);
    r->render(_obj);
}
