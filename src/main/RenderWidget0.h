#ifndef RenderWidget0_H
#define RenderWidget0_H

#include <QWidget>
#include "GLRenderWidget.h"
#include "GLRenderWidget.h"
#include "SceneManager.h"
#include "Object.h"
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
    	
	// Creates the sphere's vertices
    float* makeSphereVertices(int slices, int points);
    int* makeSphereIndices(int slices, int points);
    float* makeSphereColors(int slices, int points);
    float* makePyramidVertices(int height, int base_points);
    int* makePyramidIndices(int height, int base_points);
    float* makePyramidColors(int height, int base_points);
    void toDecimal(int num_colors, float color_list[][3]);
private:
	SceneManager *sceneManager;
	Camera *camera;
    Object *object;
    Object *bunny;
	Object *earth;
    Object *sun;
    Object *moon;
    Object *satellite;
    Object *mars;
    Object *terrain;
    Object *jupiter;
	int timerId;
    int counter;
    int frames;
    static int const max_frames = 25;
    float earth_theta;
    float earth_axis_theta;
    float moon_theta;
    float mars_theta;
    float jupiter_theta;
    float jupiter_z_theta;
    float terrain_x_scale, terrain_y_scale, terrain_z_scale;
    static const int zoompercent = 40;
    Vector3 zoomvector;
    bool testcamera1, testcamera2, dragging, zooming, zoomedin, solarsystem, airplanemode, heightmap;
    float airplane_speed;
    Vector3 airplane_direction;
    float sphereX, sphereY;
    Vector4 last_coords;
    Object ** object_list;
    int num_objects;
    Vector3 initial_cop;
};

#endif // BASICAPP_H
