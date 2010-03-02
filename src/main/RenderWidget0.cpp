#include "RenderWidget0.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Camera.h"
#include "GLWidget.h"
#include "GLRenderContext.h"
#include "ObjReader.h"
#include "VertexData.h"
#include "Shapes.h"

#include <stdio.h>

#include <QtOpenGL>


RenderWidget0::RenderWidget0()
{
	RenderContext *rs = new GLRenderContext();
	sceneManager = 0;
    mars_theta = 0.2;
}

RenderWidget0::~RenderWidget0()
{
	if(sceneManager)
	{
		delete sceneManager;
	}
}

void RenderWidget0::initSceneEvent() 
{
    solarsystem = false;
    testcamera1 = false;
    testcamera2 = true;
    counter = 0;
    airplanemode = false;
    airplane_direction = Vector3(0, 0, 1);
    airplane_speed = 0.01;
	sceneManager = new SceneManager();

	// Camera
	camera = sceneManager->createCamera();
	
	if (solarsystem) {
        const int sun_colors = 13;
        float sun_list[sun_colors][3] = {
            {255, 200, 0},
            {224, 150, 0},
            {255, 200, 0},
            {255, 200, 0},
            {255, 200, 0},
            {224, 150, 0},
            {255, 200, 0},
            {255, 200, 0},
            {230, 123, 2},
            {194, 42, 0},
            {128, 41, 17},
            {255, 200, 0},
            {224, 150, 0}
        };
        toDecimal(sun_colors, sun_list);
        const int earth_colors = 14;
        float earth_list[earth_colors][3] = {
            {41, 121, 153},
            {41, 121, 153},
            {41, 121, 153},
            {41, 121, 153},
            {41, 121, 153},
            {68, 158, 194},
            {41, 121, 153},
            {68, 158, 194},
            {41, 121, 153},
            {41, 121, 153},
            {41, 121, 153},
            {70, 127, 30},
            {17, 104, 0},
            {100, 77, 15}
        };
        toDecimal(earth_colors, earth_list);
        const int moon_colors = 12;
        float moon_list[moon_colors][3] = {
            {255, 254, 247},
            {176, 180, 214},
            {255, 254, 247},
            {176, 180, 214},
            {255, 254, 247},
            {176, 180, 214},
            {255, 254, 247},
            {255, 254, 247},
            {255, 254, 247},
            {255, 254, 247},
            {176, 180, 214},
            {114, 122, 179},
        };
        toDecimal(moon_colors, moon_list);
        const int mars_colors = 9;
        float mars_list[mars_colors][3] = {
            {249, 84, 16},
            {249, 84, 16},
            {249, 84, 16},
            {249, 84, 16},
            {159, 48, 2},
            {159, 48, 2},
            {112, 4, 19},
            {79, 6, 16},
            {37, 0, 4},
        };
        toDecimal(mars_colors, mars_list);
    
        const int jupiter_colors = 5;
        float jupiter_list[jupiter_colors][3] = {
            {106, 125, 142},
            {194, 152, 102},
            {104,74,52},
            {146,64,32},
            {194,152,102}
        };
        toDecimal(jupiter_colors, jupiter_list);
        sun = Shapes::createSphere(sceneManager, 2, 64, 128, sun_colors, sun_list, 1);
        earth = Shapes::createSphere(sceneManager, 0.5, 16, 64, earth_colors, earth_list, 1);
        moon = Shapes::createSphere(sceneManager, 0.125, 16, 64, moon_colors, moon_list, 1);
        satellite = Shapes::createBox(sceneManager, 0.1, 0.075, 0.075, moon_colors, moon_list, 1);
        mars = Shapes::createSphere(sceneManager, 0.3, 16, 64, mars_colors, mars_list, 1);
        // mars = Shapes::createCone(sceneManager, 0.25, 0.125, 30, mars_colors, mars_list, 1);
        jupiter = Shapes::createSphere(sceneManager, 1, 128, 128, jupiter_colors, jupiter_list, 1);
        num_objects = 6;
        object_list = new Object*[num_objects];
        int object_list_array = 0;
        object_list[object_list_array++] = sun;
        object_list[object_list_array++] = earth;
        object_list[object_list_array++] = satellite;
        object_list[object_list_array++] = moon;
        object_list[object_list_array++] = mars;
        object_list[object_list_array++] = jupiter;
    } else if (testcamera1 || testcamera2) {
        
        if (testcamera1) {
            camera->testCase1();
        } else {
            camera->testCase2();
        }
        
        // A house
        int nVerts = 42;
        float vertices[] = {-4,-4,4, 4,-4,4, 4,4,4, -4,4,4,       // front face
                         -4,-4,-4, -4,-4,4, -4,4,4, -4,4,-4,  // left face
                         4,-4,-4,-4,-4,-4, -4,4,-4, 4,4,-4,   // back face
                         4,-4,4, 4,-4,-4, 4,4,-4, 4,4,4,      // right face
                         4,4,4, 4,4,-4, -4,4,-4, -4,4,4,      // top face
                         -4,-4,4, -4,-4,-4, 4,-4,-4, 4,-4,4,  // bottom face
        
                         -20,-4,20, 20,-4,20, 20,-4,-20, -20,-4,-20,  // ground floor
                         -4,4,4, 4,4,4, 0,8,4,                        // roof
                         4,4,4, 4,4,-4, 0,8,-4, 0,8,4,
                         -4,4,4, 0,8,4, 0,8,-4, -4,4,-4,
                         4,4,-4, -4,4,-4, 0,8,-4};
        
        float colors[] = {1,0,0, 1,0,0, 1,0,0, 1,0,0,    // front face
                       0,1,0, 0,1,0, 0,1,0, 0,1,0,   // left face
                       1,0,0, 1,0,0, 1,0,0, 1,0,0,   // back face
                       0,1,0, 0,1,0, 0,1,0, 0,1,0,   // right face
                       0,0,1, 0,0,1, 0,0,1, 0,0,1,   // top face
                       0,0,1, 0,0,1, 0,0,1, 0,0,1,   // bottom face
        
                       0,0.5,0, 0,0.5,0, 0,0.5,0, 0,0.5,0,   // ground floor
                       0,0,1, 0,0,1, 0,0,1,                  // roof
                       1,0,0, 1,0,0, 1,0,0, 1,0,0,
                       0,1,0, 0,1,0, 0,1,0, 0,1,0,
                       0,0,1, 0,0,1, 0,0,1,};
        
        // Add an object to the scene
        object = sceneManager->createObject();
        
        // Set up the vertex data
        VertexData& vertexData = object->vertexData;
        
        // Specify the elements of the vertex data:
        // - one element for vertex positions
        vertexData.vertexDeclaration.addElement(0, 0, 3, 3*sizeof(float), RE330::VES_POSITION);
        // - one element for vertex colors
        vertexData.vertexDeclaration.addElement(1, 0, 3, 3*sizeof(int), RE330::VES_DIFFUSE);
        
        // Create the buffers and load the data
        vertexData.createVertexBuffer(0, nVerts*3*sizeof(float), (unsigned char*)vertices);
        vertexData.createVertexBuffer(1, nVerts*3*sizeof(float), (unsigned char*)colors);
        
        // The index data that stores the connectivity of the triangles
        int indices[] = {0,2,3, 0,1,2,           // front face
                      4,6,7, 4,5,6,          // left face
                      8,10,11, 8,9,10,       // back face
                      12,14,15, 12,13,14,    // right face
                      16,18,19, 16,17,18,    // top face
                      20,22,23, 20,21,22,    // bottom face
        
                      24,26,27, 24,25,26,    // ground floor
                      28,29,30,              // roof
                      31,33,34, 31,32,33,
                      35,37,38, 35,36,37,
                      39,40,41}; 
        
        vertexData.createIndexBuffer(60, indices);
        num_objects = 1;
        object_list = new Object*[num_objects];
        int object_list_array = 0;
        object_list[object_list_array++] = object;
    } else {
        int nVerts;
        float *vertices;
        float *normals;
        float *texcoords;
        int nIndices;
        int *indices;

        ObjReader::readObj("bunny.obj", nVerts, &vertices, &normals, &texcoords, nIndices, &indices);
        ObjReader::normalize(vertices, nVerts);

        bunny = sceneManager->createObject();
        VertexData& vertexData = bunny->vertexData;
        vertexData.vertexDeclaration.addElement(0, 0, 3, 3*sizeof(float), RE330::VES_POSITION);
        vertexData.createVertexBuffer(0, nVerts*3*sizeof(float), (unsigned char*)vertices);
        if(normals)
        {
        	vertexData.vertexDeclaration.addElement(1, 0, 3, 3*sizeof(float), RE330::VES_NORMAL);		
        	vertexData.createVertexBuffer(1, nVerts*3*sizeof(float), (unsigned char*)normals);
        }

        vertexData.createIndexBuffer(nIndices, indices);

        if(normals) delete[] normals;
        if(texcoords) delete[] texcoords;
        delete[] vertices;
        delete[] indices;

        const int earth_colors = 14;
        float earth_list[earth_colors][3] = {
            {41, 121, 153},
            {41, 121, 153},
            {41, 121, 153},
            {41, 121, 153},
            {41, 121, 153},
            {68, 158, 194},
            {41, 121, 153},
            {68, 158, 194},
            {41, 121, 153},
            {41, 121, 153},
            {41, 121, 153},
            {70, 127, 30},
            {17, 104, 0},
            {100, 77, 15}
        };
        toDecimal(earth_colors, earth_list);
        
        earth = Shapes::createSphere(sceneManager, 0.5, 16, 64, earth_colors, earth_list, 1);
        earth->setTransformation(earth->getTransformation() * Matrix4::translate(-4, 0, 0));
        
        num_objects = 2;
        object_list = new Object*[num_objects];
        int object_list_array = 0;
        object_list[object_list_array++] = bunny;
        object_list[object_list_array++] = earth;
    }
    
    initial_cop = camera->getCenterOfProjection();
	// Trigger timer event every 5ms.
	timerId = startTimer(5);
}

void RenderWidget0::toDecimal(int num_colors, float color_list[][3]) {
    for (int i = 0; i < num_colors; i++) {
        color_list[i][0] = color_list[i][0] / 255;
        color_list[i][1] = color_list[i][1] / 255;
        color_list[i][2] = color_list[i][2] / 255;
    }
}

void RenderWidget0::renderSceneEvent()
{
	sceneManager->renderScene();
}

void RenderWidget0::resizeRenderWidgetEvent(const QSize &s)
{
}

void RenderWidget0::timerEvent(QTimerEvent *t)
{
    if (airplanemode) {
        
    }
    if (zooming) {
        Vector3 cop = camera->getCenterOfProjection();
        camera->setCenterOfProjection(cop - zoomvector);
        frames++;
        if (frames == max_frames) {
            zooming = false;
        }
    }
    if (solarsystem) {
        Matrix4 m = Matrix4::rotateY(0.001);
        Matrix4 m2 = Matrix4::rotateZ(0.002);
        Matrix4 m3 = Matrix4::rotateY(-0.01);
        Matrix4 earth_back = Matrix4::translate(-4, 0, 0);
        Matrix4 earth_final = Matrix4::translate(4, 0, 0);
        Matrix4 tr = Matrix4::translate(0, 0, 0.05);
        Matrix4 tr2 = Matrix4::translate(0, 0, -0.05);
        Vector3 mars_axis = Vector3(0.2, 1, 0.1);
        Vector3 mars_offset = Vector3(-0.1, 0, 0.2);
        mars_offset.normalize();
        mars_offset *= 5 * (1 + abs(sin(mars_theta))/2);
        Matrix4 jupiter_final = Matrix4::translate(8, 0, 0);

        earth_theta += 0.007;
        earth_axis_theta += 0.005;
        moon_theta += 0.01;
        mars_theta += 0.0035;
        jupiter_theta += 0.0015;
        jupiter_z_theta += 0.005;

        sun->setTransformation(sun->getTransformation() * m * m2);
        earth->setTransformation(Matrix4::rotateY(earth_theta) * earth_final * Matrix4::rotateA(Vector3(1, 1.73, 0), earth_axis_theta));
        moon->setTransformation(
            Matrix4::translate(cos(earth_theta) * 4, 0, -sin(earth_theta) * 4) * 
            Matrix4::rotateA(Vector3(0, 1, 1), moon_theta) *
            Matrix4::translate(0.75, 0, 0));
        satellite->setTransformation(
            Matrix4::translate(cos(earth_theta) * 4, 0, -sin(earth_theta) * 4) *
            Matrix4::rotateX(moon_theta) *
            Matrix4::translate(0, 0.75, 0)
        );
        mars->setTransformation(
            Matrix4::rotateA(mars_axis, mars_theta) * Matrix4::translate(mars_offset)
        );
        jupiter->setTransformation(
            Matrix4::rotateY(jupiter_theta) * jupiter_final * Matrix4::rotateX(jupiter_z_theta)
        );
    }
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
        for (int i = 0; i < num_objects; i++) {
            object_list[i]->setTransformation(
                Matrix4::rotateA(crossproduct, angle) * object_list[i]->getTransformation()
            );
        }
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
