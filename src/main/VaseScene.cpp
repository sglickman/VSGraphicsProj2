#include "VaseScene.h"
#include "ObjReader.h"
#include "Shapes.h"
#include "Curve.h"

#include <vector>
#include <math.h>

using namespace RE330;

void VaseScene::init() {
    // Prepare the shader
    Shader *shader = new Shader("src/Shaders/diffuse_shading.vert",
                               "src/Shaders/diffuse_shading.frag");
    shader->use();

    everything = new TransformGroup();
    
    vector<Vector3> vasePoints = vector<Vector3> ();
    vasePoints.push_back(Vector3(.7,.0,1));
    vasePoints.push_back(Vector3(.6,.1,1));
    vasePoints.push_back(Vector3(.5,.2,1));
    vasePoints.push_back(Vector3(.4,.3,1));
    vasePoints.push_back(Vector3(.3,.4,1));
    vasePoints.push_back(Vector3(.2,.5,1));
    vasePoints.push_back(Vector3(.1,.6,1));

    PiecewiseCurve vaseCurve = PiecewiseCurve(vasePoints);

    Object *obj;
    obj = new RevolutionSurface(vaseCurve, 5, 5);
    //obj = new ObjectBox(.45f, .1f, .12f);
    Material *vasemat;
    vasemat = new Material();
    vasemat->setSpecular(Vector3(1, 1, 1));
    vasemat->setShininess(40.f);
    vasemat->setDiffuse(Vector3(0, .5, 1));
    vasemat->setAmbient(Vector3(.1, .1, .1));

    theVase = new Shape3D(obj, vasemat);
    everything->addChild(theVase);

}

void VaseScene::nextFrame() {

}
