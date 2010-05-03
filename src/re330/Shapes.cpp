#include "Shapes.h"
#include <iostream>

using namespace std;

using namespace RE330;



void Shapes::setupObject(Object* obj, int nVerts, int nIndices, 
                         float* v, float* n, int* i) {
    VertexData& vd = obj->vertexData;
	// Specify the elements of the vertex data:
	// - one element for vertex positions
	vd.vertexDeclaration.addElement(0, 0, 3, 3*sizeof(float), 
                                    RE330::VES_POSITION);

    vd.vertexDeclaration.addElement(1, 0, 3, 3*sizeof(float), 
                                    RE330::VES_NORMAL);
	
	// Create the buffers and load the data
	vd.createVertexBuffer(0, nVerts*3*sizeof(float), (unsigned char*)v);
    vd.createVertexBuffer(1, nVerts*3*sizeof(float), (unsigned char*)n);
    vd.createIndexBuffer(nIndices, i);
}

ObjectSphere::ObjectSphere(float height, int slices, int points) 
    : ObjectShape(), center(Vector3(0, 0, 0)), radius(height / 2)
{
    float* sphere_v = new float[(slices + 1) * points * 3];
    float* sphere_n = new float[(slices + 1) * points * 3];

    // Loop through, create the sphere.
    int index = 0;
    float theta, phi;
    for(int s = 0; s <= slices; s++) {
        for(int p = 0; p < points; p++) {
            theta = 2*M_PI/points*p;
            phi = M_PI/slices*s;

            sphere_v[index] = height * cos(theta) * sin(phi);
            sphere_n[index++] = height * cos(theta) * sin(phi);

            sphere_v[index] = height * sin(theta) * sin(phi);
            sphere_n[index++] = height * sin(theta) * sin(phi);

            sphere_v[index] = height * cos(phi);
            sphere_n[index++] = height * cos(phi);         
        }
    }
    int* sphere_i = sphereIndices(slices, points);
    int nVerts = (slices + 1) * points;
    int nIndices = slices * points * 2 * 3;
    setupObject(nVerts, nIndices, sphere_v, sphere_n, sphere_i);

    delete sphere_v;
    delete sphere_n;
}

ObjectBox::ObjectBox(const float height, const float width, const float depth) 
    : ObjectShape(), center(Vector3(0, 0, 0)), 
      radius(Vector3(height, width, depth).len() / 2)
{
    float* box_v = new float[3 * 8 * 3];
    float* box_n = new float[3 * 8 * 3];
    float coords[3 * 8] = {
        -width / 2, height / 2, -depth / 2,
        -width / 2, height / 2, depth / 2,
        width / 2, height / 2, depth / 2,
        width / 2, height / 2, -depth / 2,
        -width / 2, -height / 2, -depth / 2,
        -width / 2, -height / 2, depth / 2,
        width / 2, -height / 2, depth / 2,
        width / 2, -height / 2, -depth / 2
    };

    // Loop through each corner of the box
    for (char i = 0; i < 8; i++) {
        // Loop through each normal of the vertex
        for (int j = 0; j < 3; j++) {
            // Loop through the x,y,z coordinates.
            for (int k = 0; k < 3; k++) {
                box_v[3*3*i + 3*j + k] =
                    (k == 0 ? (i & 1)*width - width/2 :
                     (k == 1 ? (i & 2)/2.0*height - height/2 :
                      (k == 2 ? (i & 4)/4.0*depth - depth/2 : 0)));
                box_n[3*3*i + 3*j + k] =
                    (j == k && j == 0 ? (i & 1)*2 - 1 :
                     (j == k && j == 1 ? (i & 2) - 1 :
                      (j == k && j == 2 ? (i & 4)/2 - 1 : 0)));
            }
        }
    }

    int box_i [3 * 12] = {
        // First, the faces with x normals.
        4*3, 2*3, 0*3,
        2*3, 4*3, 6*3,

        1*3, 3*3, 5*3,
        7*3, 5*3, 3*3,

        // Next, those with y normals.
        0*3+1, 1*3+1, 4*3+1,
        5*3+1, 4*3+1, 1*3+1,

        7*3+1, 3*3+1, 2*3+1,
        2*3+1, 6*3+1, 7*3+1,

        // Finally, those with z normals.
        4*3+2, 5*3+2, 6*3+2,
        7*3+2, 6*3+2, 5*3+2,

        2*3+2, 1*3+2, 0*3+2,
        1*3+2, 2*3+2, 3*3+2
    };
    int nVerts = 8 * 3;
    int nIndices = 3 * 12;

    setupObject(nVerts, nIndices, box_v, box_n, box_i);
    delete box_n;
    delete box_v;
}

/* Create a new RevolutionSurface from a Curve */
RevoultionSurface::RevolutionSurface(const Curve &c, const int ncuts) :
    curve(c) 
{
    // Use the convex hull property of the curve to determine the
    // approximate y center of the revolved surface.

    // Generate the actual surface
}
