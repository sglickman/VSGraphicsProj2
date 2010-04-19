#include "TeapotScene.h"
#include "ObjReader.h"

// TeapotScene::~TeapotScene() {

// }

void TeapotScene::init() {
    // Prepare the shader
    Shader *shader = new Shader("src/Shaders/diffuse_shading.vert",
                                "src/Shaders/diffuse_shading.frag");
    shader->use();

    teaDragon = new TransformGroup();

    int nVerts;
    float *vertices;
    float *normals;
    float *texcoords;
    int nIndices;
    int *indices;

    // Read in the teapot object
    ObjReader::readObj("teapot.obj", nVerts, &vertices, &normals,
                       &texcoords, nIndices, &indices);
    ObjReader::normalize(vertices, nVerts);

    Object *teapot = new Object();
    VertexData& vertexData = teapot->vertexData;
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
    // QImage *texImg = new QImage("stone.png", "PNG");
    // Texture *t = new Texture(texImg);
  
    Material* teaMaterial = new Material();
    // teapot_material->setTexture(t);
    teaMaterial->setSpecular(Vector3(1, 1, 1));
    teaMaterial->setShininess(40.f);
    teaMaterial->setDiffuse(Vector3(.5, .7, 1.f));
    teaMaterial->setAmbient(Vector3(.1, .2, .4));

    float *texcoords2;
    teaShape = new Shape3D(teapot, teaMaterial);
    teaDragon->addChild(teaShape);

    ObjReader::readObj("dragon_smooth.obj", nVerts, &vertices, &normals,
                       &texcoords2, nIndices, &indices);
    ObjReader::normalize(vertices, nVerts);
    Object *dragon = new Object();
    VertexData& vertexData2 = dragon->vertexData;
    vertexData2.vertexDeclaration.addElement(0, 0, 3, 3*sizeof(float),
                                             RE330::VES_POSITION);
    vertexData2.createVertexBuffer(0, nVerts*3*sizeof(float), 
                                   (unsigned char*)vertices);
    if(normals)
    {
        vertexData2.vertexDeclaration.addElement(1, 0, 3, 3*sizeof(float),
                                                 RE330::VES_NORMAL);   
        vertexData2.createVertexBuffer(1, nVerts*3*sizeof(float), 
                                       (unsigned char*)normals);
    }
  
    vertexData2.createIndexBuffer(nIndices, indices);
  
    Material* dragMaterial = new Material();
    // teapot_material->setTexture(t);
    dragMaterial->setShininess(10.f);
    dragMaterial->setSpecular(Vector3(.5, .5, .5));
    dragMaterial->setDiffuse(Vector3(.3, .9, .1));
    dragMaterial->setAmbient(Vector3(.1, .2, .1));

    dragShape = new Shape3D(dragon, dragMaterial);
    teaDragon->addChild(dragShape);
  
    dragShape->setTransformation(dragShape->getTransformation() *
                                 Matrix4::translate(-.5, 0, 0));

    teaShape->setTransformation(teaShape->getTransformation() * 
                                Matrix4::translate(.5, 0, 0));

    sceneManager->addChild(teaDragon);
}

void TeapotScene::nextFrame() {
    dragShape->setTransformation(dragShape->getTransformation() * Matrix4::rotateY(0.03));
    teaShape->setTransformation(teaShape->getTransformation() * Matrix4::rotateY(-0.03));
}
