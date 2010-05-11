#include "VaseScene.h"
#include "ObjReader.h"
#include "Shapes.h"
#include "Curve.h"

#include <vector>
#include <math.h>

using namespace RE330;

void VaseScene::init() {
    // Prepare the shader
    Shader *shader = new Shader("src/Shaders/texture_shading.vert",
                               "src/Shaders/texture_shading.frag");
    shader->use();

    everything = new TransformGroup();
    tableScene = new TransformGroup();
    
    vector<Vector3> donutPoints = vector<Vector3> ();
    donutPoints.push_back(Vector3(.125, .0, 1));
    donutPoints.push_back(Vector3(.2, .0, 1));
    donutPoints.push_back(Vector3(.2, .1, 1));
    donutPoints.push_back(Vector3(.125, .1, 1));
    donutPoints.push_back(Vector3(.05, .1, 1));
    donutPoints.push_back(Vector3(.05, .0, 1));
    donutPoints.push_back(Vector3(.125, .0, 1));

    PiecewiseCurve donutCurve = PiecewiseCurve(donutPoints);

    Object *obj;
    obj = new RevolutionSurface(donutCurve, 20, 20);
    //obj = new ObjectBox(.45f, .1f, .12f);
    QImage *texImg = new QImage("donut.png", "PNG");
    Texture *donuttexture;
    donuttexture = new Texture(texImg);
    Material *donutmat;
    donutmat = new Material();
    donutmat->setSpecular(Vector3(.2, .2, .2));
    donutmat->setShininess(10.f);
    donutmat->setDiffuse(Vector3(.8, .8, .8));
    donutmat->setAmbient(Vector3(.2, .2, .2));
    donutmat->setTexture(donuttexture);
    donut = new Shape3D(obj, donutmat);
    donut->applyTransformation(Matrix4::translate(.4,0,0));
    tableScene->addChild(donut);

    vector<Vector3> applePoints = vector<Vector3> ();
    applePoints.push_back(Vector3(.0, .1, 1));
    applePoints.push_back(Vector3(.175, .0, 1));
    applePoints.push_back(Vector3(.2, .4, 1));
    applePoints.push_back(Vector3(.0, .3, 1));

    PiecewiseCurve appleCurve = PiecewiseCurve(applePoints);

    obj = new RevolutionSurface(appleCurve, 20, 20);
    //obj = new ObjectBox(.45f, .1f, .12f);
    texImg = new QImage("apple.jpg", "JPG");
    Texture *appletexture;
    appletexture = new Texture(texImg);
    Material *applemat;
    applemat = new Material();
    applemat->setSpecular(Vector3(.2, .2, .2));
    applemat->setShininess(10.f);
    applemat->setDiffuse(Vector3(.8, .8, .8));
    applemat->setAmbient(Vector3(.2, .2, .2));
    applemat->setTexture(appletexture);
    apple = new Shape3D(obj, applemat);
    apple->applyTransformation(Matrix4::translate(-.4,-.1,0));
    tableScene->addChild(apple);

    vector<Vector3> tablePoints = vector<Vector3> ();
    tablePoints.push_back(Vector3(0, 0, 1));
    tablePoints.push_back(Vector3(0.8, 0, 1));
    tablePoints.push_back(Vector3(0.8, 0, 1));
    tablePoints.push_back(Vector3(.82, -0.04, 1));
    tablePoints.push_back(Vector3(.8, -0.08, 1));
    tablePoints.push_back(Vector3(0.1, -0.08, 1));
    tablePoints.push_back(Vector3(0.1, -0.08, 1));
    tablePoints.push_back(Vector3(0.07, -0.4, 1));
    tablePoints.push_back(Vector3(0.1, -0.8, 1));
    tablePoints.push_back(Vector3(0.1, -0.8, 1));
    tablePoints.push_back(Vector3(0.3, -0.8, 1));
    tablePoints.push_back(Vector3(0.32, -0.82, 1));
    tablePoints.push_back(Vector3(0.34, -0.84, 1));
    tablePoints.push_back(Vector3(0.34, -0.84, 1));
    tablePoints.push_back(Vector3(0.36, -0.84, 1));
    tablePoints.push_back(Vector3(0.38, -0.86, 1));
    tablePoints.push_back(Vector3(0.38, -0.86, 1));
    tablePoints.push_back(Vector3(0, -0.86, 1));
    tablePoints.push_back(Vector3(0, -0.86, 1));


    PiecewiseCurve tableCurve = PiecewiseCurve(tablePoints);

    obj = new RevolutionSurface(tableCurve, 20, 20);
    texImg = new QImage("wood.jpg", "JPG");
    Texture *tableTexture;
    tableTexture = new Texture(texImg);
    Material *tablemat;
    tablemat = new Material();
    tablemat->setSpecular(Vector3(.1, .1, .1));
    tablemat->setShininess(1.0f);
    tablemat->setDiffuse(Vector3(.8, .8, .8));
    tablemat->setAmbient(Vector3(.2, .2, .2));
    tablemat->setTexture(tableTexture);
    table = new Shape3D(obj, tablemat);
    tableScene->addChild(table);
    
    vector<Vector3> cokePoints = vector<Vector3> ();
    cokePoints.push_back(Vector3(0, .02, 1));
    cokePoints.push_back(Vector3(.1, .02, 1));
    cokePoints.push_back(Vector3(.1, .00, 1));
    cokePoints.push_back(Vector3(.12, .0, 1));
    cokePoints.push_back(Vector3(.12, .01, 1));
    cokePoints.push_back(Vector3(.14, .02, 1));
    cokePoints.push_back(Vector3(.15, .02, 1));
    cokePoints.push_back(Vector3(.15, .17, 1));
    cokePoints.push_back(Vector3(.15, .32, 1));
    cokePoints.push_back(Vector3(.15, .47, 1));
    cokePoints.push_back(Vector3(.14, .47, 1));
    cokePoints.push_back(Vector3(.12, .49, 1));
    cokePoints.push_back(Vector3(.12, .5, 1));
    cokePoints.push_back(Vector3(.1, .5, 1));
    cokePoints.push_back(Vector3(.1, .48, 1));
    cokePoints.push_back(Vector3(0, .48, 1));


    PiecewiseCurve cokeCurve = PiecewiseCurve(cokePoints);

    obj = new RevolutionSurface(cokeCurve, 30, 30);
    //obj = new ObjectBox(.45f, .1f, .12f);
    texImg = new QImage("coke-label.jpg", "JPG");
    Texture *coketexture;
    coketexture = new Texture(texImg);
    Material *cokemat;
    cokemat = new Material();
    cokemat->setSpecular(Vector3(.2, .2, .2));
    cokemat->setShininess(10.f);
    cokemat->setDiffuse(Vector3(.8, .8, .8));
    cokemat->setAmbient(Vector3(.2, .2, .2));
    cokemat->setTexture(coketexture);
    coke = new Shape3D(obj, cokemat);
    coke->applyTransformation(Matrix4::translate(0, 0, 0));
    tableScene->addChild(coke);
    
    tableScene->applyTransformation(Matrix4::translate(0, 0.2, 0));
    tableScene->applyTransformation(Matrix4::scale(0.8, 0.8, 0.8));
    everything->addChild(tableScene);


    

}

void VaseScene::nextFrame() {

}
