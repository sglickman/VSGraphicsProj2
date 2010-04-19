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

    // Temporary object, materials
    Object *obj;
    Material *mat;
    
    // Set up the robot scene tree hierarchy
    theRobot = new TransformGroup();

    // Create the Robot's head.
    obj = Shapes::createSphere(.2f, 10, 10);
    mat = new Material();
    mat->setSpecular(Vector3(1, 1, 1));
    mat->setShininess(40.f);
    mat->setDiffuse(Vector3(.5, .7, 1.f));
    mat->setAmbient(Vector3(.1, .2, .4));

    head = new Shape3D(obj, mat);
    theRobot->addChild(head);

    // Create the rest of the Robot.
    robotBody = new TransformGroup();
    
    // Create the Robot's left arm.
    leftArm = new TransformGroup();

    // Create the Robot's left shoulder.
    obj = Shapes::createSphere(.1f, 10, 10);
    mat = new Material();
    mat->setSpecular(Vector3(0, 1, 1));
    mat->setShininess(40.f);
    mat->setDiffuse(Vector3(.5, 1.f, .7f));
    mat->setAmbient(Vector3(.5, .2, .0));
    
    leftShoulder = new Shape3D(obj, mat);
    leftShoulder->applyTransformation(Matrix4::translate(0, 0, 0));
    leftArm->addChild(leftShoulder);

    // Create the Robot's left hand.
    obj = Shapes::createSphere(.1f, 10, 10);
    mat = new Material();
    mat->setSpecular(Vector3(0, 1, 1));
    mat->setShininess(40.f);
    mat->setDiffuse(Vector3(.5, 1.f, .1f));
    mat->setAmbient(Vector3(.5, .5, .0));
    
    leftHand = new Shape3D(obj, mat);
    leftHand->applyTransformation(Matrix4::translate(0, -.5, 0));
    leftArm->addChild(leftHand);

    leftArm->applyTransformation(Matrix4::translate(-.4, -.2, 0));
    robotBody->addChild(leftArm);

    // Create the Robot's right arm.
    rightArm = new TransformGroup();

    // Create the Robot's right shoulder.
    obj = Shapes::createSphere(.1f, 10, 10);
    mat = new Material();
    mat->setSpecular(Vector3(0, 1, 1));
    mat->setShininess(40.f);
    mat->setDiffuse(Vector3(.5, 1.f, .7f));
    mat->setAmbient(Vector3(.5, .2, .0));
    
    rightShoulder = new Shape3D(obj, mat);
    rightShoulder->applyTransformation(Matrix4::translate(0, 0, 0));
    rightArm->addChild(rightShoulder);

    // Create the Robot's right hand.
    obj = Shapes::createSphere(.1f, 10, 10);
    mat = new Material();
    mat->setSpecular(Vector3(0, 1, 1));
    mat->setShininess(40.f);
    mat->setDiffuse(Vector3(.5, 1.f, .1f));
    mat->setAmbient(Vector3(.5, .5, .0));
    
    rightHand = new Shape3D(obj, mat);
    rightHand->applyTransformation(Matrix4::translate(0, -.5, 0));
    rightArm->addChild(rightHand);

    rightArm->applyTransformation(Matrix4::translate(.4, -.2, 0));
    robotBody->addChild(rightArm);

    theRobot->addChild(robotBody);

    sceneManager->addChild(theRobot);
    

}

void RobotScene::nextFrame() {
    rightArm->applyTransformation(Matrix4::rotateX(0.04f));
    theRobot->applyTransformation(Matrix4::rotateY(-0.01f));
}
