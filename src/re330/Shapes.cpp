#include "Shapes.h"

using namespace RE330;

Object* Shapes::createSphere(float height, int slices, int points) {
    Object *sphere = new Object();

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
    setupObject(sphere, nVerts, nIndices, sphere_v, sphere_n, sphere_i);	
    return sphere;    
}

// Object* Shapes::createCone(float height, float base_radius, int base_points, const int num_colors, float color_list[][3], bool random_colors) {
//     Object *cone = new Object();
//     float* cone_v = coneVertices(height, base_radius, base_points, num_colors);
//     float* cone_c = coneColors(base_points, num_colors, color_list);
//     int* cone_i = coneIndices(base_points, num_colors, random_colors);
//     int nVerts = (1 + base_points) * num_colors;
//     int nIndices = 3 * base_points;
//     setupObject(cone, nVerts, nIndices, cone_v, cone_c, cone_i);
//     return cone;
// }

Object* Shapes::createBox(float height, float width, float depth) {
    Object *box = new Object();
    // float* box_v = boxVertices(height, width, depth, num_colors);
    // float* box_c = boxColors(num_colors, color_list);
    // int* box_i = boxIndices(num_colors, random_colors);
    // int nVerts = 8 * num_colors;
    // int nIndices = 3 * 12;
    // setupObject(box, nVerts, nIndices, box_v, box_c, box_i);
    return box;
}

float* Shapes::coneVertices(float height, float base_radius, int base_points, const int num_colors) {
    float* array = new float[3 * num_colors * (1 + base_points)];
    // first make two top vertices for the
    int index = 0;
    for (int i = 0; i < num_colors; i++) {
        array[index++] = 0;
        array[index++] = height;
        array[index++] = 0;
    }
    // now do the base
    float theta;
    for (int i = 0; i < base_points; i++) {
        theta = 2 * M_PI / base_points * i;
        for (int j = 0; j < num_colors; j++) {
            array[index++] = base_radius * cos(theta);
            array[index++] = -height;
            array[index++] = base_radius * sin(theta);
        }
    }
    return array;
}
float* Shapes::coneColors(int base_points, const int num_colors, float color_list[][3]) {
    float* array = new float[3 * num_colors * (1 + base_points)];
    int index = 0;
    // for the top point(s)
    for (int i = 0; i < num_colors; i++) {
        array[index++] = color_list[i][0];
        array[index++] = color_list[i][1];
        array[index++] = color_list[i][2];
    }
    for (int i = 0; i < base_points; i++) {
        for (int j = 0; j < num_colors; j++) {
            array[index++] = color_list[j][0];
            array[index++] = color_list[j][1];
            array[index++] = color_list[j][2];
        }
    }
    return array;    
}
int* Shapes::coneIndices(int base_points, const int num_colors, bool random_colors) {
    srand(time(NULL));
    // connect the top point to adjacent base points.
    int* array = new int[3 * base_points];
    // color_index keeps track of the color of the current triangle
    int color_index = 0;
    if (random_colors) {
        color_index = rand() % num_colors;
    }
    int index = 0;
    int i;
    for (i = 0; i < base_points - 1; i++) {
        // top point
        array[index++] = color_index;
        // base points
        array[index++] = num_colors + color_index + num_colors * i;
        array[index++] = 2 * num_colors + color_index + num_colors * i;
        if (random_colors) {
            color_index = rand() % num_colors;
        } else {
            color_index++;
            color_index %= num_colors;
        }
    }
    // finally connect the last base point to the first base point.
    array[index++] = color_index;
    array[index++] = num_colors + color_index + num_colors * i;
    array[index++] = num_colors + color_index;
    return array;
}
float* Shapes::sphereVertices(float height, int slices, int points) {
    float* array = new float[(slices + 1) * points * 3];
    int index = 0;
    float theta, phi;
    for(int s = 0; s <= slices; s++) {
        for(int p = 0; p < points; p++) {
            theta = 2*M_PI/points*p;
            phi = M_PI/slices*s;
            array[index++] = height * cos(theta) * sin(phi);
            array[index++] = height * sin(theta) * sin(phi);
            array[index++] = height * cos(phi);
        }
    }
    return array;
}

int* Shapes::sphereIndices(int slices, int points) {
    srand(time(NULL));
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
float* Shapes::boxVertices(float height, float width, float depth, const int num_colors) {
    float* array = new float[3 * 8 * num_colors];
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
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < num_colors; j++) {
            for (int k = 0; k < 3; k++) {
                array[3 * num_colors * i + 3 * j + k] = coords[3 * i + k];
            }
        }
    }
    return array;
}
float* Shapes::boxColors(const int num_colors, float color_list[][3]) {
    float* array = new float[num_colors * 3 * 8];
    int index = 0;
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < num_colors; i++) {
            array[index++] = color_list[i][0];
            array[index++] = color_list[i][1];
            array[index++] = color_list[i][2];
        }
    }
    return array;
}
int* Shapes::boxIndices(const int num_colors, bool random_colors) {
    srand(time(NULL));
    int* array = new int[12 * 3];
    int index = 0;
    int color_index = 0;
    if (random_colors) {
        color_index = rand() % num_colors;
    }
    array[index++] = 0 * num_colors + color_index;
    array[index++] = 1 * num_colors + color_index;
    array[index++] = 2 * num_colors + color_index;
    if (random_colors) {
        color_index = rand() % num_colors;
    } else {
        color_index++;
        color_index %= num_colors;
    }
    array[index++] = 2 * num_colors + color_index;
    array[index++] = 3 * num_colors + color_index;
    array[index++] = 0 * num_colors + color_index;
    if (random_colors) {
        color_index = rand() % num_colors;
    } else {
        color_index++;
        color_index %= num_colors;
    }
    array[index++] = 1 * num_colors + color_index;
    array[index++] = 5 * num_colors + color_index;
    array[index++] = 6 * num_colors + color_index;
    if (random_colors) {
        color_index = rand() % num_colors;
    } else {
        color_index++;
        color_index %= num_colors;
    }
    array[index++] = 6 * num_colors + color_index;
    array[index++] = 2 * num_colors + color_index;
    array[index++] = 1 * num_colors + color_index;
    if (random_colors) {
        color_index = rand() % num_colors;
    } else {
        color_index++;
        color_index %= num_colors;
    }
    array[index++] = 0 * num_colors + color_index;
    array[index++] = 4 * num_colors + color_index;
    array[index++] = 5 * num_colors + color_index;
    if (random_colors) {
        color_index = rand() % num_colors;
    } else {
        color_index++;
        color_index %= num_colors;
    }
    array[index++] = 5 * num_colors + color_index;
    array[index++] = 1 * num_colors + color_index;
    array[index++] = 0 * num_colors + color_index;
    if (random_colors) {
        color_index = rand() % num_colors;
    } else {
        color_index++;
        color_index %= num_colors;
    }
    array[index++] = 3 * num_colors + color_index;
    array[index++] = 2 * num_colors + color_index;
    array[index++] = 6 * num_colors + color_index;
    if (random_colors) {
        color_index = rand() % num_colors;
    } else {
        color_index++;
        color_index %= num_colors;
    }
    array[index++] = 6 * num_colors + color_index;
    array[index++] = 7 * num_colors + color_index;
    array[index++] = 3 * num_colors + color_index;
    if (random_colors) {
        color_index = rand() % num_colors;
    } else {
        color_index++;
        color_index %= num_colors;
    }
    array[index++] = 0 * num_colors + color_index;
    array[index++] = 3 * num_colors + color_index;
    array[index++] = 7 * num_colors + color_index;
    if (random_colors) {
        color_index = rand() % num_colors;
    } else {
        color_index++;
        color_index %= num_colors;
    }
    array[index++] = 7 * num_colors + color_index;
    array[index++] = 4 * num_colors + color_index;
    array[index++] = 0 * num_colors + color_index;
    if (random_colors) {
        color_index = rand() % num_colors;
    } else {
        color_index++;
        color_index %= num_colors;
    }
    array[index++] = 4 * num_colors + color_index;
    array[index++] = 7 * num_colors + color_index;
    array[index++] = 6 * num_colors + color_index;
    if (random_colors) {
        color_index = rand() % num_colors;
    } else {
        color_index++;
        color_index %= num_colors;
    }
    array[index++] = 6 * num_colors + color_index;
    array[index++] = 5 * num_colors + color_index;
    array[index++] = 4 * num_colors + color_index;
    return array;
}

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
