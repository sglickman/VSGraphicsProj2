#include "BuddhaScene.h"

void BuddhaScene::init() {
        // Prepare the shader
    Shader *shader = new Shader("src/Shaders/diffuse_shading.vert",
                                "src/Shaders/diffuse_shading.frag");
    shader->use();

    booDahRay = new TransformGroup();

    int nVerts;
    float *vertices;
    float *normals;
    float *texcoords;
    int nIndices;
    int *indices;
    float radius;
    Vector3 center;

    // Read in the teapot object
    ObjReader::readObj("teapot.obj", nVerts, &vertices, &normals,
                       &texcoords, nIndices, &indices);
    ObjReader::normalize(vertices, nVerts, center, radius);
    
    printf("Center of object: (%f, %f, %f); radius: %f\n", center[0], center[1], center[2], radius);

    Object *buddha = new Object();
    VertexData& vertexData = buddha->vertexData;
    vertexData.vertexDeclaration.addElement(0, 0, 3, 3*sizeof(float),
                                            RE330::VES_POSITION);
    vertexData.createVertexBuffer(0, nVerts*3*sizeof(float), 
                                  (unsigned char*)vertices);
    if(normals)
    {
        vertexData.vertexDeclaration.addElement(1, 0, 3, 3*sizeof(float),
                                                RE330::VES_NORMAL);		
        vertexData.createVertexBuffer(1, nVerts*3*sizeof(float), 
                                      (unsigned char*)normals);
    }

    vertexData.createIndexBuffer(nIndices, indices);

    Material* booMaterial = new Material();
    // buddha_material->setTexture(t);
    booMaterial->setSpecular(Vector3(1, 1, 1));
    booMaterial->setShininess(40.f);
    booMaterial->setDiffuse(Vector3(.5, .7, 1.f));
    booMaterial->setAmbient(Vector3(.1, .2, .4));

    daBooDahs = new Shape3D*[144];
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            daBooDahs[i*12 + j] = new Shape3D(buddha, booMaterial);
            daBooDahs[i*12 + j]->applyTransformation(
                Matrix4::translate(i-6, 0, j-6));
            booDahRay->addChild(daBooDahs[i*12 + j]);
        }
    }
    sceneManager->addChildToWorld(booDahRay);

}

void BuddhaScene::nextFrame() {
    
}
