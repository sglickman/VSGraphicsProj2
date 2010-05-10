#include "Shapes.h"
#include <iostream>

using namespace std;

using namespace RE330;


void ObjectShape::setupObject(int nVerts, int nIndices, 
                         float* v, float* n, float* t, int* i) {
    VertexData& vd = vertexData;
	// Specify the elements of the vertex data:
	// - one element for vertex positions
	vd.vertexDeclaration.addElement(0, 0, 3, 3*sizeof(float), 
                                    RE330::VES_POSITION);

    vd.vertexDeclaration.addElement(1, 0, 3, 3*sizeof(float), 
                                    RE330::VES_NORMAL);
    vd.vertexDeclaration.addElement(2, 0, 2, 2*sizeof(float),
                                    RE330::VES_TEXTURE_COORDINATES);

	// Create the buffers and load the data
	vd.createVertexBuffer(0, nVerts*3*sizeof(float), (unsigned char*)v);
    vd.createVertexBuffer(1, nVerts*3*sizeof(float), (unsigned char*)n);
    vd.createVertexBuffer(2, nVerts*2*sizeof(float), (unsigned char*)t);
    vd.createIndexBuffer(nIndices, i);
}



void ObjectShape::setupObject(int nVerts, int nIndices, 
                         float* v, float* n, int* i) {
    VertexData& vd = vertexData;
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
    : ObjectShape(Vector3(0, 0, 0), height / 2)
{
    float* sphere_v = new float[(slices + 1) * points * 3];
    float* sphere_n = new float[(slices + 1) * points * 3];

    // Loop through, create the sphere.
    int index = 0;
    float theta, phi;
    for(int s = 0; s <= slices; s++) {
        phi = M_PI/slices*s;

        for(int p = 0; p < points; p++) {
            theta = 2*M_PI/points*p;

            sphere_v[index] = height * cos(theta) * sin(phi);
            sphere_n[index++] = height * cos(theta) * sin(phi);

            sphere_v[index] = height * sin(theta) * sin(phi);
            sphere_n[index++] = height * sin(theta) * sin(phi);

            sphere_v[index] = height * cos(phi);
            sphere_n[index++] = height * cos(phi);         
        }
    }
    int* sphere_i = indices(slices, points);
    int nVerts = (slices + 1) * points;
    int nIndices = slices * points * 2 * 3;
    setupObject(nVerts, nIndices, sphere_v, sphere_n, sphere_i);

    delete sphere_v;
    delete sphere_n;
}

int* ObjectSphere::indices(const int slices, const int points) const {
    int* array = new int[2 * (slices) * points * 3];
    int index = 0;
    int color_index = 0;
    for (int s = 0; s < slices; s++) {
        for (int p = 0; p < points; p++) {
            array[index++] = (s * points + p + 1);
            array[index++] = (s * points + p);
            array[index++] = ((s + 1) * points + p);

            array[index++] = ((s + 1) * points + p);
            array[index++] = ((s + 1) * points + p + 1);
            array[index++] = (s * points + p + 1);
        }
    }
    return array;
}

ObjectBox::ObjectBox(const float height, const float width, const float depth) 
    : ObjectShape(Vector3(0, 0, 0), Vector3(height, width, depth).len() / 2)
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
RevolutionSurface::RevolutionSurface(const Curve &c, const int slices,
                                     const int points) :
    ObjectShape(), 
    curve(c) 
{
    // Use the convex hull property of the curve to determine the
    // approximate y center of the revolved surface.
    const int VERTICES_PER_SIDE = (slices + 1) * (points + 1);

    // Generate the actual surface
    float* surf_v = new float[VERTICES_PER_SIDE * 3 * 2];
    float* surf_n = new float[VERTICES_PER_SIDE * 3 * 2];
    float* surf_t = new float[VERTICES_PER_SIDE * 2 * 2];

    float *cur_in_v, *cur_out_v;
    float *cur_in_n, *cur_out_n;
    float *cur_in_t, *cur_out_t;

    // Loop through, create the surface.
    int index = 0;
    float theta, t;
    Vector3 u, udt; // The current point on the curve, its deriv.
    Vector4 x, n; // The current point in 3space, its normal
    for(int s = 0; s <= slices; s++) {
        t = (1.f/slices) * s;
        u = curve.interpolatePoint(t);
        udt = curve.interpolateDeriv(t);
        u /= u[2]; // Make the homogeneous coordinate 1 again.
        // udt /= udt[2]; // udt = udt.normalize();
        // cout << udt[0] << "," << udt[1] << endl;
        
        for(int p = 0; p < points+1; p++) {
            theta = 2*M_PI/points * p;

            // Set up pointers to spots in the array for legibility
            cur_out_v = &(surf_v[index*3]);
            cur_in_v = &(surf_v[(index+VERTICES_PER_SIDE)*3]);
            cur_out_n = &(surf_n[index*3]);
            cur_in_n = &(surf_n[(index+VERTICES_PER_SIDE)*3]);
            cur_out_t = &(surf_t[index*2]);
            cur_in_t = &(surf_t[(index+VERTICES_PER_SIDE)*2]);

            // x coordinate
            // Outside
            cur_out_v[0] = u[0] * sin(theta);
            cur_out_n[0] = -udt[1] * sin(theta);
            cur_out_t[0] = p / (float) points;
            // Inside
            cur_in_v[0] = u[0] * sin(theta);
            cur_in_n[0] = udt[1] * sin(theta);
            cur_in_t[0] = p / (float) points;

            // y coordinate
            // Outside
            cur_out_v[1] = u[1];
            cur_out_n[1] = udt[0];
            cur_out_t[1] = s / (float) slices;
            // Inside
            cur_in_v[1] = u[1];
            cur_in_n[1] = -udt[0];
            cur_in_t[1] = s / (float) slices;

            // z coordinate
            // Outisde
            cur_out_v[2] = u[0] * cos(theta);
            cur_out_n[2] = -udt[1] * cos(theta);   
            // Inside
            cur_in_v[2] = u[0] * cos(theta);
            cur_in_n[2] = udt[1] * cos(theta);   
            index++;

            //cout << surf_v[index-1] << endl;
        }
    }
    int* surf_i = indices(slices, points);
    int nVerts = VERTICES_PER_SIDE * 2;
    int nIndices = (slices) * (points) * 2 * 3 * 2;
    setupObject(nVerts, nIndices, surf_v, surf_n, surf_t, surf_i);

    delete surf_v;
    delete surf_n;
    delete surf_t;
}

int* RevolutionSurface::indices(const int slices, const int points) const {
    int* array = new int[2 * slices * points * 3 * 2];
    int index = 0;
    int color_index = 0;
    for (int s = 0; s < slices; s++) {
        for (int p = 0; p < points; p++) {
            array[index++] = (s*(points+1) + p);
            array[index++] = ((s+1)*(points+1) + p);
            array[index++] = ((s+1)*(points+1) + ((p+1)%(points+1)));

            array[index++] = (s*(points+1) + p);
            array[index++] = ((s+1)*(points+1) + ((p+1)%(points+1)));
            array[index++] = (s*(points+1) + ((p+1)%(points+1)));
        }
    }
    for (int s = 0; s < slices; s++) {
        for (int p = 0; p < points; p++) {
            array[index++] = (points+1)*(slices+1) + (s*(points+1) + p);
            array[index++] = (points+1)*(slices+1) + ((s+1)*(points+1) + ((p+1)%(points+1)));
            array[index++] = (points+1)*(slices+1) + ((s+1)*(points+1) + p);

            array[index++] = (points+1)*(slices+1) + (s*(points+1) + p);
            array[index++] = (points+1)*(slices+1) + (s*(points+1) + ((p+1)%(points+1)));
            array[index++] = (points+1)*(slices+1) + ((s+1)*(points+1) + ((p+1)%(points+1)));
        }
    }
    return array;
}
