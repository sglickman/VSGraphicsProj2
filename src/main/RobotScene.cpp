#include "RobotScene.h"
#include "ObjReader.h"
#include "Shapes.h"

#include <math.h>

// RobotScene::~RobotScene() {

// }

void RobotScene::init() {
    // Prepare the shader
    Shader *shader = new Shader("src/Shaders/diffuse_shading.vert",
                                "src/Shaders/diffuse_shading.frag");
    shader->use();

    // Temporary object, materials
    Object *obj;
    Material *robomat, *mat;
    robomat = new Material();
    robomat->setSpecular(Vector3(1, 1, 1));
    robomat->setShininess(40.f);
    robomat->setDiffuse(Vector3(.5, .7, 1.f));
    robomat->setAmbient(Vector3(.1, .1, .1));
    
    // Set up the robot scene tree hierarchy
    theRobot = new TransformGroup();

    // Create the Robot's head.
    obj = Shapes::createSphere(.2f, 10, 10);
    mat = new Material(*robomat);

    head = new Shape3D(obj, mat);
    head->applyTransformation(Matrix4::translate(0, .5, 0));
    theRobot->addChild(head);

    // Create the rest of the Robot.
    robotBody = new TransformGroup();

    // Create the Robot's torso. Change to some other shape later.
    obj = Shapes::createBox(.5, .4, .2);
    mat = new Material(*robomat);
    
    torso = new Shape3D(obj, mat);    
    robotBody->addChild(torso);
    
    // Create the Robot's left arm.
    leftArm = new TransformGroup();

    // Create the Robot's left shoulder.
    obj = Shapes::createSphere(.1f, 10, 10);
    mat = new Material(*robomat);
    
    leftShoulder = new Shape3D(obj, mat);
    leftShoulder->applyTransformation(Matrix4::translate(0, 0, 0));
    leftArm->addChild(leftShoulder);

    // Create the Robot's left arm meat.
    obj = Shapes::createBox(.45f, .1f, .12f);
    mat = new Material(*robomat);
    
    leftArmPart = new Shape3D(obj, mat);
    leftArmPart->applyTransformation(Matrix4::translate(0, -.25f, 0));
    leftArm->addChild(leftArmPart);

    // Create the Robot's left hand.
    obj = Shapes::createSphere(.07f, 10, 10);
    mat = new Material(*robomat);
    
    leftHand = new Shape3D(obj, mat);
    leftHand->applyTransformation(Matrix4::translate(0, -.5, 0));
    leftArm->addChild(leftHand);

    // Create the Robot's flashlight.
    flashlight = new Light();

    flashlight->setAllColors(Vector3(1.0, 0.0, 0.0),
                             Vector3(1., 0.2, 0.2),
                             Vector3(0.1, 0.1, 0.1));
    flashlight->makeSpot(Vector3(0.0, -.5, 0.0),
                         Vector3(0.0, -1, 0.3),
                         120.0, 7.0);

    leftArm->addChild(flashlight);

    leftArm->applyTransformation(Matrix4::translate(-.3, .3, 0));
    robotBody->addChild(leftArm);

    // Create the Robot's right arm.
    rightArm = new TransformGroup();

    // Create the Robot's right shoulder.
    obj = Shapes::createSphere(.1f, 10, 10);
    mat = new Material(*robomat);
    
    rightShoulder = new Shape3D(obj, mat);
    rightShoulder->applyTransformation(Matrix4::translate(0, 0, 0));
    rightArm->addChild(rightShoulder);

    // Create the Robot's right arm meat.
    obj = Shapes::createBox(.45f, .1f, .12f);
    mat = new Material(*robomat);
    
    rightArmPart = new Shape3D(obj, mat);
    rightArmPart->applyTransformation(Matrix4::translate(0, -.25f, 0));
    rightArm->addChild(rightArmPart);

    // Create the Robot's right hand.
    obj = Shapes::createSphere(.07f, 10, 10);
    mat = new Material(*robomat);

    rightHand = new Shape3D(obj, mat);
    rightHand->applyTransformation(Matrix4::translate(0, -.5, 0));
    rightArm->addChild(rightHand);

    rightArm->applyTransformation(Matrix4::translate(.3, .3, 0));
    robotBody->addChild(rightArm);

    // Create the Robot's left leg.
    leftLeg = new TransformGroup();

    // Create the Robot's lower left leg.
    leftLowerLeg = new TransformGroup();

    // Create the Robot's left thigh
    obj = Shapes::createBox(.45f, .1f, .12f);
    mat = new Material(*robomat);
    
    leftThigh = new Shape3D(obj, mat);
    leftThigh->applyTransformation(Matrix4::translate(0, -.25f, 0));
    leftLeg->addChild(leftThigh);   

    // Create the Robot's left knee.
    obj = Shapes::createSphere(.1f, 10, 10);
    mat = new Material(*robomat);

    leftKnee = new Shape3D(obj, mat);
    leftLowerLeg->addChild(leftKnee);

    // Create the Robot's lower left leg meat.
    obj = Shapes::createBox(.45f, .1f, .12f);
    mat = new Material(*robomat);
    
    leftLegPart = new Shape3D(obj, mat);
    leftLegPart->applyTransformation(Matrix4::translate(0, -.25f, 0));
    leftLowerLeg->addChild(leftLegPart);  

    // Create the Robot's left foot.
    obj = Shapes::createBox(.08f, .2f, .3f);
    mat = new Material(*robomat);
    
    leftFoot = new Shape3D(obj, mat);
    leftFoot->applyTransformation(Matrix4::translate(0, -.5f, .07f));
    leftLowerLeg->addChild(leftFoot);  
    
    leftLowerLeg->applyTransformation(Matrix4::translate(0, -.5, 0));
    leftLeg->addChild(leftLowerLeg);

    leftLeg->applyTransformation(Matrix4::translate(-.2, -.2, 0));
    robotBody->addChild(leftLeg);

    // Create the Robot's right leg.
    rightLeg = new TransformGroup();

    // Create the Robot's lower right leg.
    rightLowerLeg = new TransformGroup();

    // Create the Robot's right thigh
    obj = Shapes::createBox(.45f, .1f, .12f);
    mat = new Material(*robomat);
    
    rightThigh = new Shape3D(obj, mat);
    rightThigh->applyTransformation(Matrix4::translate(0, -.25f, 0));
    rightLeg->addChild(rightThigh);  

    // Create the Robot's right knee.
    obj = Shapes::createSphere(.1f, 10, 10);
    mat = new Material(*robomat);

    rightKnee = new Shape3D(obj, mat);
    rightLowerLeg->addChild(rightKnee);

    // Create the Robot's lower right leg meat.
    obj = Shapes::createBox(.45f, .1f, .12f);
    mat = new Material(*robomat);
    
    rightLegPart = new Shape3D(obj, mat);
    rightLegPart->applyTransformation(Matrix4::translate(0, -.25f, 0));
    rightLowerLeg->addChild(rightLegPart);  

    // Create the Robot's right foot.
    obj = Shapes::createBox(.08f, .2f, .3f);
    mat = new Material(*robomat);
    
    rightFoot = new Shape3D(obj, mat);
    rightFoot->applyTransformation(Matrix4::translate(0, -.5f, .07f));
    rightLowerLeg->addChild(rightFoot);  
    
    rightLowerLeg->applyTransformation(Matrix4::translate(0, -.5, 0));
    rightLeg->addChild(rightLowerLeg);

    rightLeg->applyTransformation(Matrix4::translate(.2, -.2, 0));
    robotBody->addChild(rightLeg);

    theRobot->addChild(robotBody);

    theRobot->applyTransformation(Matrix4::translate(0, .3, 0));
    sceneManager->addChild(theRobot);

    obj = Shapes::createRect(10, 10);
    mat = new Material(*robomat);

    theGround = new Shape3D(obj, mat);
    theGround->applyTransformation(Matrix4::translate(0, -1, 0));    
    theGround->applyTransformation(Matrix4::rotateX(-M_PI/2.f));

    sceneManager->addChildToWorld(theGround);
    

}

void RobotScene::nextFrame() {
    // Handle with care. This is probably the worst way to animate the guy.
    static int f = 1;

    rightArm->applyTransformation(Matrix4::rotateX(-0.04f * cos(f/20.0)));
    leftArm->applyTransformation(Matrix4::rotateX(0.04f * cos(f/20.0)));
    rightLeg->applyTransformation(Matrix4::rotateX(0.03f * cos(f/20.0)));
    rightLowerLeg->applyTransformation(Matrix4::rotateX(0.03f * cos(f/20.0)));
    leftLeg->applyTransformation(Matrix4::rotateX(-0.03f * cos(f/20.0)));
    leftLowerLeg->applyTransformation(Matrix4::rotateX(-0.03f * cos(f/20.0)));
    f++;
    //theRobot->applyTransformation(Matrix4::rotateY(-0.01f));
}
