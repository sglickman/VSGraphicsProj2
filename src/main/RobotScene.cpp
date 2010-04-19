#include "RobotScene.h"
#include "ObjReader.h"
#include "Shapes.h"

// RobotScene::~RobotScene() {

// }

void RobotScene::init() {
    // Prepare the shader
    Shader *shader = new Shader("src/Shaders/diffuse_shading.vert",
                                "src/Shaders/diffuse_shading.frag");
    shader->use();
    
    // Set up the robot scene tree hierarchy
    theRobot = new TransformGroup();

    // Create the Robot's head.
    Object *headObj = Shapes::createSphere(.2f, 10, 10);
    Material *headMat = new Material();
    headMat->setSpecular(Vector3(1, 1, 1));
    headMat->setShininess(40.f);
    headMat->setDiffuse(Vector3(.5, .7, 1.f));
    headMat->setAmbient(Vector3(.1, .2, .4));

    head = new Shape3D(headObj, headMat);

    theRobot->addChild(head);

    sceneManager->addChild(theRobot);
    

}

void RobotScene::nextFrame() {
}
