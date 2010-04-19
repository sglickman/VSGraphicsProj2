#ifndef RenderWidget0_H
#define RenderWidget0_H

#include <QWidget>
#include "SWRenderWidget.h"
#include "SWRenderContext.h"
#include "GLWidget.h"
#include "GLWidget.h"
#include "GLRenderWidget.h"
#include "SceneManager.h"
#include "Object.h"
#include "Shader.h"
#include "RenderScene.h"
#include <math.h>

using namespace RE330;

class RenderWidget0 : public GLRenderWidget
{

public:
    RenderWidget0();
    ~RenderWidget0();

	void startAnimation();
	void stopAnimation();
    void turnLeft();
    void turnRight();
    void turnUp();
    void turnDown();
    void toggleFly();
    void speedUp();
    void speedDown();

protected:
	// Event handlers. These are virtual methods of the base class.
	// They are called automatically to handle specific events.

	// Called when the render window is ready.
	void initSceneEvent();

	// Called when the scene in the render window needs to be re-rendered.
	void renderSceneEvent();

	// Called when the render widget is resized.
	void resizeRenderWidgetEvent(const QSize &s);

	// Virtual methods of QWidget class. This is a subset. Re-implement any
	// that you would like to handle.
	void timerEvent(QTimerEvent *t);
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
    	
    void toDecimal(int num_colors, float color_list[][3]);
    // void setupDefault();
    // void setupSolarSystem();
    // void setupHeightmap();
    // void setupTestCamera(int testcamera);
    // void setupColorfulGeometry();
    // void setupHyperbolicRectangle();
    void setupTeapotAndDragon();
    // void setupTexturedPlanes();
private:
	SceneManager *sceneManager;
	Camera *camera;
    Object *object;
    Object *object1;
    Object *object2;
    Object *house;
    Object *bunny;
    Object *dragon;
	Object *earth;
    Object *sun;
    Object *moon;
    Object *satellite;
    Object *mars;
    Object *terrain;
    Object *jupiter;
    Object *teapot;
	int timerId;
    int counter;
    int frames;
    int turn_frames;
    static int const max_frames = 25;
    static int const max_turn_frames = 15;
    float turning_angle; 
    float earth_theta;
    float earth_axis_theta;
    float moon_theta;
    float mars_theta;
    float jupiter_theta;
    float jupiter_z_theta;
    float terrain_x_scale, terrain_y_scale, terrain_z_scale;
    static const int zoompercent = 40;
    Vector3 zoomvector;
    bool dragging, zooming, zoomedin, solarsystem, airplanemode, heightmap,
        colorful_geometry, hyperbolic_rectangle, shadingmode, texturemode;
    int testcamera;
    bool turning, turningup, turningdown, turningleft, turningright;
    float airplane_speed;
    Vector3 airplane_direction;
    float sphereX, sphereY;
    Vector4 last_coords;
    Object ** object_list;
    int num_objects;
    Vector3 initial_cop;

    RenderScene *scene;
};

#endif // BASICAPP_H
