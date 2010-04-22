#include "Shape3D.h"
#include <iostream>

using namespace std;
using namespace RE330;

void Shape3D::draw(RenderContext *r, const Matrix4 &C, const Matrix4 &P, bool culling) {
    Matrix4 modelView = C * t;
    Matrix4 canonical = P * modelView;
    r->setModelViewMatrix(modelView);
    
    if (culling) {
        Vector4 x = canonical * Vector4(1, 0, 0, 1);
        Vector4 y = canonical * Vector4(0, 1, 0, 1);
        Vector4 z = canonical * Vector4(0, 0, 1, 1);
        Vector4 o = canonical * Vector4(0, 0, 0, 1);
        // double radius = 1.f;
        // printf("z - o: %f \n", (z - o)[3]);
        double radius = _obj->getRadius() * max(
           max((x.hdiv() - o.hdiv()).len(), (y.hdiv() - o.hdiv()).len())
           , (z.hdiv() - o.hdiv()).len());
        // printf("C\n");
        // C.print();
        // printf("P\n");
        // P.print();
        // printf("modelView\n");
        // modelView.print();
        // printf("canonical\n");
        // canonical.print();
        // printf("image of z: (%f, %f, %f, %f)\n", z[0], z[1], z[2], z[3]);
        // printf("radius: %f\n", radius);
        // printf("---------------------------------------------\n");
        Vector3 center = (canonical * Vector4(_obj->getCenter(), 1)).hdiv();
        for (int i = 0; i < 6; i++) {
            int coord = i/2;
            int posneg = (i%2)*2-1;

            // cout << "Radius " << radius << ", Center[c] " << center[coord] << endl;
        
            // Check for sphere intersection
            if (center[coord] + radius > posneg && center[coord] - radius < posneg) {

            } else if (posneg * center[coord] > 1) {
                // We are outside of the cube, so die.
                // cout << "Cull something as outside of " << coord << " " << posneg << endl;
                return;
            }
        }
    }
    
    if (_mat) {
        r->setMaterial(_mat);
    } else {
        r->setMaterial(&Material());
    }
    
    r->render(_obj);
}
