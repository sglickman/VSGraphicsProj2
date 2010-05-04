#include "RenderWidget0.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Camera.h"
#include "SWWidget.h"
#include "SWRenderContext.h"
#include "GLWidget.h"
#include "GLRenderContext.h"
#include "ObjReader.h"
#include "VertexData.h"
#include "PGMLoader.cpp"
#include "Shapes.h"
#include "Shape3D.h"
#include "TransformGroup.h"
#include "VaseScene.h"
#include "TeapotScene.h"
#include "BuddhaScene.h"
#include <QTime>

#include <stdio.h>
#include <iostream>

#include <QtOpenGL>

using namespace std;

RenderWidget0::RenderWidget0()
{
	RenderContext *rs = new GLRenderContext();
    // rs->init();
	sceneManager = 0;
    scene = 0;
    mars_theta = 0.2;
}

RenderWidget0::~RenderWidget0()
{
	if(sceneManager)
	{
        delete sceneManager;
	}
    if(scene)
    {
        // delete scene;
    }
}

/*
** Convenience method which scales an old range of values to a new range.
** Scales level from the range [actual_min, actual_max] to the range
** [new_min, new_max].
*/
float scale(float level, float actual_min, float actual_max, 
            float new_min, float new_max) {
  
    if (new_min == new_max) {
        return new_min;
    }
    return ((level - actual_min) / 
            (actual_max - actual_min) * (new_max - new_min)) + 
        new_min;
}

void RenderWidget0::initSceneEvent() 
{
    setFocus();
    hyperbolic_rectangle = false;
    colorful_geometry = false;
    solarsystem = false;
    shadingmode = true;
    texturemode = false;
    testcamera = 0;
    heightmap = false;
    counter = 0;
    airplanemode = true;
    turning_angle = 0.1;
    airplane_speed = 0;
	sceneManager = new SceneManager();
    terrain_x_scale = 2;
    terrain_y_scale = 1;
    terrain_z_scale = 2;
  
	// Camera
	camera = sceneManager->createCamera();
	if (airplanemode) {
        camera->setCenterOfProjection(Vector3(0, 10, 10));
	}
    airplane_direction = Vector3(0, 0, -1);
	
    setupTeapotAndDragon();
    camera->testCase1();
  
    initial_cop = camera->getCenterOfProjection();
	// Trigger timer event every 5ms.
	timerId = startTimer(5);
}

/*
** Sets up the teapot, which has normals.
*/
void RenderWidget0::setupTeapotAndDragon() {
    //scene = new BuddhaScene(sceneManager);
    //scene->init();
//    sceneManager->setScene(scene->getRoot());
//    buddha_scene = true;

    scene2 = new VaseScene(sceneManager);
    scene2->init();
    sceneManager->setScene(scene2->getRoot());
    buddha_scene = false;
}

/*
** Convenience method, converts an RGB whose values are from 0-255
** to a color list whose values are between 0 and 1
*/
void RenderWidget0::toDecimal(int num_colors, float color_list[][3]) {
    for (int i = 0; i < num_colors; i++) {
        color_list[i][0] = color_list[i][0] / 255;
        color_list[i][1] = color_list[i][1] / 255;
        color_list[i][2] = color_list[i][2] / 255;
    }
}

void RenderWidget0::renderSceneEvent()
{
    float framerate;
    QTime t;
    t.start();
	sceneManager->renderScene();
    int elapsed = t.restart();
    framerate = 1000 / (elapsed ? elapsed : 1);
    char winTitle[100];
    sprintf(winTitle, "%f fps", framerate);
    this->parentWidget()->setWindowTitle(winTitle);
}

void RenderWidget0::resizeRenderWidgetEvent(const QSize &s)
{
}

void RenderWidget0::keyPressEvent(QKeyEvent *e) {
    if (e->text() == "n") {
        sceneManager->culling = false;
        printf("Turning culling off.\n");
    } else if (e->text() == "c") {
        sceneManager->culling = true;
        printf("Turning culling on.\n");
    } else if (e->text() == "s") {
        if (buddha_scene) {
            sceneManager->setScene(scene2->getRoot());
        } else {
            sceneManager->setScene(scene->getRoot());
        }
        buddha_scene = !buddha_scene;
    }
    e->ignore();
}

/*
** Takes care of turning, zooming in, and airplane movement
** as well as object animation.
*/ 
void RenderWidget0::timerEvent(QTimerEvent *t)
{
    if (scene) {
        scene->nextFrame();
    } if (scene2) {
        scene2->nextFrame();
    }
    // if (shadingmode) {
    //     
    // }
    // if (airplanemode) {
    //     Vector3 cop3 = camera->getCenterOfProjection();
    //     Matrix4 translation = 
    //         Matrix4::translate(airplane_direction * airplane_speed);
    //     Vector3 lap3 = camera->getLookAtPoint();
    //     Vector4 cop4 = Vector4(cop3[0], cop3[1], cop3[2], 1);
    //     Vector4 lap4 = Vector4(lap3[0], lap3[1], lap3[2], 1);
    //     lap4 = translation * lap4;
    //     cop4 = translation * cop4;
    
    //     camera->setCenterOfProjection(
    //         Vector3(cop4[0], cop4[1], cop4[2])
    //         );
    //     camera->setLookAtPoint(
    //         Vector3(lap4[0], lap4[1], lap4[2])
    //         );
    //     if (turning) {
    //         lap3 = camera->getLookAtPoint() - camera->getCenterOfProjection();
    //         lap4 = Vector4(lap3[0], lap3[1], lap3[2], 1);
    //         Vector3 crossplap = lap3 * camera->getUpVector();
    //         Vector3 dir3 = airplane_direction;
    //         Vector3 crosspdir = dir3 * camera->getUpVector();
    //         Vector4 dir = Vector4(dir3[0], dir3[1], dir3[2], 1);
    //         Vector3 cam3 = camera->getUpVector();
    //         Vector4 cam4 = Vector4(cam3[0], cam3[1], cam3[2], 1);
    //         turn_frames++;
    //         if (turningleft) {
    //             lap4 = Matrix4::rotateA(camera->getUpVector(), 
    //                                     turning_angle / max_turn_frames) * lap4;
    //             dir = Matrix4::rotateA(camera->getUpVector(), 
    //                                    turning_angle / max_turn_frames) * dir;
    //         } else if (turningright) {
    //             lap4 = Matrix4::rotateA(camera->getUpVector(), 
    //                                     -turning_angle / max_turn_frames) * lap4;
    //             dir = Matrix4::rotateA(camera->getUpVector(), 
    //                                    -turning_angle / max_turn_frames) * dir;
    //         } else if (turningup) {
    //             lap4 = Matrix4::rotateA(crossplap, 
    //                                     turning_angle / max_turn_frames) * lap4;
    //             dir = Matrix4::rotateA(crosspdir, 
    //                                    turning_angle / max_turn_frames) * dir;
    //             cam4 = Matrix4::rotateA(crosspdir, 
    //                                     turning_angle / max_turn_frames) * cam4;        
    //         } else if (turningdown) {
    //             lap4 = Matrix4::rotateA(crossplap, 
    //                                     -turning_angle / max_turn_frames) * lap4;
    //             dir = Matrix4::rotateA(crosspdir, 
    //                                    -turning_angle / max_turn_frames) * dir;
    //             cam4 = Matrix4::rotateA(crosspdir, 
    //                                     -turning_angle / max_turn_frames) * cam4;
    //         }
    //         if (turn_frames == max_turn_frames) {
    //             turning = false;
    //             turningdown = turningup = turningleft = turningright = false;
    //             turn_frames = 0;
    //         }
    //         camera->setLookAtPoint(
    //             Vector3(lap4[0], lap4[1], lap4[2]) +
    //             camera->getCenterOfProjection()
    //             );
    //         camera->setUpVector(
    //             Vector3(cam4[0], cam4[1], cam4[2])
    //             );
    //         airplane_direction = Vector3(dir[0], dir[1], dir[2]);
    //     }
    // }
    // if (zooming) {
    //     Vector3 cop = camera->getCenterOfProjection();
    //     camera->setCenterOfProjection(cop - zoomvector);
    //     frames++;
    //     if (frames == max_frames) {
    //         zooming = false;
    //     }
    // }
    // if (solarsystem) {
    //     Matrix4 m = Matrix4::rotateY(0.001);
    //     Matrix4 m2 = Matrix4::rotateZ(0.002);
    //     Matrix4 m3 = Matrix4::rotateY(-0.01);
    //     Matrix4 earth_back = Matrix4::translate(-4, 0, 0);
    //     Matrix4 earth_final = Matrix4::translate(4, 0, 0);
    //     Matrix4 tr = Matrix4::translate(0, 0, 0.05);
    //     Matrix4 tr2 = Matrix4::translate(0, 0, -0.05);
    //     Vector3 mars_axis = Vector3(0.2, 1, 0.1);
    //     Vector3 mars_offset = Vector3(-0.1, 0, 0.2);
    //     mars_offset.normalize();
    //     mars_offset *= 5 * (1 + abs(sin(mars_theta))/2);
    //     Matrix4 jupiter_final = Matrix4::translate(8, 0, 0);

    //     earth_theta += 0.007;
    //     earth_axis_theta += 0.005;
    //     moon_theta += 0.01;
    //     mars_theta += 0.0035;
    //     jupiter_theta += 0.0015;
    //     jupiter_z_theta += 0.005;

    //     sun->setTransformation(sun->getTransformation() * m * m2);
    //     earth->setTransformation(Matrix4::rotateY(earth_theta) * 
    //                              earth_final *
    //                              Matrix4::rotateA(Vector3(1, 1.73, 0), earth_axis_theta));
    //     moon->setTransformation(
    //         Matrix4::translate(cos(earth_theta) * 4, 0, 
    //                            -sin(earth_theta) * 4) * 
    //         Matrix4::rotateA(Vector3(0, 1, 1), moon_theta) *
    //         Matrix4::translate(0.75, 0, 0));
    //     satellite->setTransformation(
    //         Matrix4::translate(cos(earth_theta) * 4, 0, 
    //                            -sin(earth_theta) * 4) *
    //         Matrix4::rotateX(moon_theta) *
    //         Matrix4::translate(0, 0.75, 0)
    //         );
    //     mars->setTransformation(
    //         Matrix4::rotateA(mars_axis, mars_theta) *
    //         Matrix4::translate(mars_offset)
    //         );
    //     jupiter->setTransformation(
    //         Matrix4::rotateY(jupiter_theta) * jupiter_final *
    //         Matrix4::rotateX(jupiter_z_theta)
    //         );
    // }
	updateScene();
}

void RenderWidget0::mousePressEvent(QMouseEvent *e)
{
    dragging = true;
    last_coords = Vector4(e->x(), this->height() - e->y(), 0, 1);
}

void RenderWidget0::mouseMoveEvent(QMouseEvent *e)
{
    if (dragging) {
        int dimension = this->width();
        if (this->height() < dimension) {
            dimension = this->height();
        }
        Matrix4 ts = Matrix4(
            2.0 / dimension, 0, 0, - ((float) this->width()) / dimension,
            0, 2.0 / dimension, 0, - ((float) this->height()) / dimension,
            0, 0, 1, 0,
            0, 0, 0, 1
            );
        Vector4 v0 = ts * last_coords;
        Vector4 v1 = ts * Vector4(e->x(), this->height() - e->y(), 0, 1);
        float z02 = 1 - v0[0]*v0[0] - v0[1]*v0[1];
        float z12 = 1 - v1[0]*v1[0] - v1[1]*v1[1];
        Vector3 crossproduct =  Vector3(
            v0[0], 
            v0[1], 
            (z02 > 0 ? sqrt(z02) : 0)
            ) * Vector3(
                v1[0], 
                v1[1], 
                (z12 > 0 ? sqrt(z12) : 0)
                );
        float angle = asin(crossproduct.len());
        sceneManager->setSceneTransformation(
            Matrix4::rotateA(crossproduct, angle) *
            sceneManager->getSceneTransformation());
        // for (int i = 0; i < num_objects; i++) {
        //     object_list[i]->setTransformation(
        //         Matrix4::rotateA(crossproduct, angle) *
        //         object_list[i]->getTransformation()
        //         );
        // }
        last_coords = Vector4(e->x(), this->height() - e->y(), 0, 1);
        updateScene();
    }
}

void RenderWidget0::mouseReleaseEvent(QMouseEvent *e)
{
    dragging = false;
}

void RenderWidget0::startAnimation()
{
	if(!timerId)
	{
		timerId = startTimer(5);
	}
}

void RenderWidget0::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (zooming) {
        return;
    }
    zooming = true;
    if (!zoomedin) {
        zoomvector = camera->getCenterOfProjection() - Vector3(
            ( (float)e->x() / this->width() - 0.5) * 5, 
            ( (float)(this->height() - e->y()) / this->height() - 0.5) * 5,
            initial_cop[2] * (((float) (100 - zoompercent)) / 100));
    } else {
        zoomvector = camera->getCenterOfProjection() - initial_cop;
    }
    zoomvector /= (float) max_frames;
    zoomedin = !zoomedin;
    frames = 0;
}

void RenderWidget0::stopAnimation()
{
	if(timerId)
	{
		killTimer(timerId);
		timerId = 0;
	}
}

void RenderWidget0::turnLeft()
{
    if (!turning) {
        turning = turningleft = true;
    }
}

void RenderWidget0::turnRight()
{
    if (!turning) {
        turning = turningright = true;
    }
}

void RenderWidget0::turnDown()
{
    if (!turning) {
        turning = turningdown = true;
    }
}

void RenderWidget0::turnUp()
{
    if (!turning) {
        turning = turningup = true;    
    }
}

void RenderWidget0::toggleFly()
{
    airplanemode = !airplanemode;
}

void RenderWidget0::speedUp()
{
    airplane_speed += 0.005;
}

void RenderWidget0::speedDown()
{
    airplane_speed -= 0.005;
}
