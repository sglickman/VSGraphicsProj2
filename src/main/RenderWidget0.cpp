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
#include "RobotScene.h"

#include <stdio.h>

#include <QtOpenGL>


RenderWidget0::RenderWidget0()
{
	RenderContext *rs = new GLRenderContext();
    // rs->init();
	sceneManager = 0;
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
        delete scene;
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
	
	// if (heightmap) {
    //     setupHeightmap();
	// } else if (solarsystem) {
    //     setupSolarSystem();
    // } else if (testcamera) {
    //     setupTestCamera(testcamera);
    // } else if (colorful_geometry) {
    //     setupColorfulGeometry();
    // } else if (hyperbolic_rectangle) {
    //     setupHyperbolicRectangle();
    // } else if (shadingmode) {
         setupTeapotAndDragon();
         camera->testCase1();
    // } else if (texturemode) {
    //     setupTexturedPlanes();
    // } else {
    //     setupDefault();
    // }
  
    initial_cop = camera->getCenterOfProjection();
	// Trigger timer event every 5ms.
	timerId = startTimer(5);
}

/*
** Sets up the textured planes, as required in the lab.
*/

// void RenderWidget0::setupTexturedPlanes() {
//     // Shader
//     Shader *shader = new Shader("src/Shaders/texture_shading.vert",
//                                 "src/Shaders/texture_shading.frag");
//     shader->use();
  
//     int nVerts1 = 4;
//     float vertices1[] = 
//         {
//             -5,5,0,  5,-5,0,   5,5,0,
//             -5,-5,0
//         };
//     float colors1[] = 
//         {
//             1,0,0,  0,0,1,   1,0,0,
//             1,0,0
//         };
//     int indices1[] = 
//         {
//             0,1,2,  0,3,1
//         };
  
//     float texcoords1[] = 
//         {
//             0, 0, 1, 1, 1, 0,
//             1, 0
//         };
  
//     float normals1[] = 
//         {
//             0,0,1, 0,0,1, 0,0,1, 
//             0,0,1
//         };
  
//     int nVerts2 = 16;
  
//     float vertices2[] = 
//         {
//             -1, 1, -1,  -1, 1, -1,
//             -1, 1, 1,   -1, 1, 1,
//             1, 1, 1,    1, 1, 1,
//             1, 1, -1,   1, 1, -1,
//             -1, -1, -1, -1, -1, -1,
//             -1, -1, 1,  -1, -1, 1,
//             1, -1, 1,   1, -1, 1,
//             1, -1, -1,  1, -1, -1,
//         };
  
//     float normals2[] = 
//         {
//             -1, 1, -1,  -1, 1, -1,
//             -1, 1, 1,   -1, 1, 1,
//             1, 1, 1,    1, 1, 1,
//             1, 1, -1,   1, 1, -1,
//             -1, -1, -1, -1, -1, -1,
//             -1, -1, 1,  -1, -1, 1,
//             1, -1, 1,   1, -1, 1,
//             1, -1, -1,  1, -1, -1,
//         };
  

//     float colors2[] = 
//         {
//             0,0,0,  0,0,0,
//             0,0,0,  0,0,0,
//             0,0,0,  0,0,0,
//             0,0,0,  0,0,0,
//             0,0,0,  0,0,0,
//             0,0,0,  0,0,0,
//             0,0,0,  0,0,0,
//             0,0,0,  0,0,0,    
//         };
//     int indices2[] = 
//         {
//             0, 4, 6,     0, 2, 4,
//             4, 14, 6,    4, 12, 14,
//             12, 8, 14,   12, 10, 8,
//             10, 2, 8,    8, 2, 0,
    
//             3, 13, 5,    3, 11, 13,
//             1, 7, 15,    15, 9, 1
//         };
  
//     float texcoords2[] = 
//         {
//             0,0,  0,0, 
//             0,1,  0,0,
//             1,1,  1,0,
//             1,0,  0,1,
//             1,0,  1,0,
//             1,1,  0,1,
//             0,1,  1,1,
//             0,0,  1,1
//         };
  
  
//     object1 = sceneManager->createObject();
//     // Set up the vertex data
// 	VertexData& vertexData1 = object1->vertexData;

// 	// Specify the elements of the vertex data:
// 	// - one element for vertex positions
// 	vertexData1.vertexDeclaration.addElement(0, 0, 3, 
//                                              3*sizeof(float), RE330::VES_POSITION);
// 	// - one element for vertex colors
// 	vertexData1.vertexDeclaration.addElement(1, 0, 3, 
//                                              3*sizeof(float), RE330::VES_DIFFUSE);
	  
// 	vertexData1.vertexDeclaration.addElement(2, 0, 3,
//                                              3*sizeof(float), RE330::VES_NORMAL);
//     vertexData1.createVertexBuffer(2, nVerts1 * 3 * sizeof(float), (unsigned char*)normals1);

// 	// Create the buffers and load the data
// 	vertexData1.createVertexBuffer(0, nVerts1*3*sizeof(float), 
//                                    (unsigned char*)vertices1);
// 	vertexData1.createVertexBuffer(1, nVerts1*3*sizeof(float), 
//                                    (unsigned char*)colors1);
	
// 	vertexData1.createIndexBuffer(2 * 3, indices1);
// 	vertexData1.vertexDeclaration.addElement(3, 0, 2, 2*sizeof(float),
//                                              RE330::VES_TEXTURE_COORDINATES);
// 	vertexData1.createVertexBuffer(3, nVerts1*2*sizeof(float), 
//                                    (unsigned char*)texcoords1);
	
//     QImage *texImg1 = new QImage("stone.png", "PNG");
//     Texture *t1 = new Texture(texImg1);  
//     Material* object1_material = new Material();
//     object1_material->setTexture(t1);
//     object1->setMaterial(object1_material);

	
//     object2 = sceneManager->createObject();
//     // Set up the vertex data
// 	VertexData& vertexData2 = object2->vertexData;

// 	// Specify the elements of the vertex data:
// 	// - one element for vertex positions
// 	vertexData2.vertexDeclaration.addElement(0, 0, 3, 
//                                              3*sizeof(float), RE330::VES_POSITION);
// 	// - one element for vertex colors
// 	vertexData2.vertexDeclaration.addElement(1, 0, 3, 
//                                              3*sizeof(float), RE330::VES_DIFFUSE);

// 	// Create the buffers and load the data
// 	vertexData2.createVertexBuffer(0, nVerts2*3*sizeof(float), 
//                                    (unsigned char*)vertices2);
// 	vertexData2.createVertexBuffer(1, nVerts2*3*sizeof(float), 
//                                    (unsigned char*)colors2);
	  
//     vertexData2.vertexDeclaration.addElement(2, 0, 3,
//                                              3*sizeof(float), RE330::VES_NORMAL);
//     vertexData2.createVertexBuffer(2, 3*nVerts2*sizeof(float), (unsigned char*)normals2);
	
// 	vertexData2.createIndexBuffer(36, indices2);
	
// 	vertexData2.vertexDeclaration.addElement(3, 0, 2, 2*sizeof(float),
//                                              RE330::VES_TEXTURE_COORDINATES);
// 	vertexData2.createVertexBuffer(3, nVerts2*2*sizeof(float), 
//                                    (unsigned char*)texcoords2);

//     QImage *texImg2 = new QImage("brick.jpg", "JPG");
//     Texture *t2 = new Texture(texImg2);  
//     Material* object2_material = new Material();
//     object2_material->setTexture(t2);
//     object2->setMaterial(object2_material);
	
	
//     object1->setTransformation(object1->getTransformation() * Matrix4::translate(-3, 0, -1));
//     object2->setTransformation(object2->getTransformation() * Matrix4::translate(3, 0, 1));
  
// 	num_objects = 2;
//     object_list = new Object*[num_objects];
//     int object_list_array = 0;
//     object_list[object_list_array++] = object1;
//     object_list[object_list_array++] = object2;
// }


/*
** Sets up hyperbolic interpolation test, as required in the lab.
*/
// void RenderWidget0::setupHyperbolicRectangle() {
  
//     int nVerts = 6;
//     float vertices[] = 
//         {
//             -5,5,0,  5,-5,0,   5,5,0,
//             -5,5,0,  -5,-5,0,  5,-5,0
//         };
//     float colors[] = 
//         {
//             1,0,0,  0,0,1,   1,0,0,
//             1,0,0,  0,0,1,   0,0,1
//         };
//     int indices[] = 
//         {
//             0,1,2,  3,4,5
//         };
  
// 	// Add an object to the scene
// 	object = sceneManager->createObject();

// 	// Set up the vertex data
// 	VertexData& vertexData = object->vertexData;

// 	// Specify the elements of the vertex data:
// 	// - one element for vertex positions
// 	vertexData.vertexDeclaration.addElement(0, 0, 3, 
//                                             3*sizeof(float), RE330::VES_POSITION);
// 	// - one element for vertex colors
// 	vertexData.vertexDeclaration.addElement(1, 0, 3, 
//                                             3*sizeof(float), RE330::VES_DIFFUSE);

// 	// Create the buffers and load the data
// 	vertexData.createVertexBuffer(0, nVerts*3*sizeof(float), 
//                                   (unsigned char*)vertices);
// 	vertexData.createVertexBuffer(1, nVerts*3*sizeof(float), 
//                                   (unsigned char*)colors);
	
// 	vertexData.createIndexBuffer(2 * 3, indices);
// 	num_objects = 1;
//     object_list = new Object*[num_objects];
//     int object_list_array = 0;
//     object_list[object_list_array++] = object;
	
// }

/* 
** Sets up colorful geometry, as required in the lab.
*/
// void RenderWidget0::setupColorfulGeometry() {
//     camera->scene1();
//     // quad houses
//     int nVerts = 42 + (24 + 14) * 3;
//     float vertices[] = 
//         {-4+6,-4, 4+6,  4+6,-4, 4+6,  4+6, 4, 4+6,-4+6, 4, 4+6,  // front face
//          -4+6,-4,-4+6, -4+6,-4, 4+6, -4+6, 4, 4+6, -4+6, 4,-4+6,  // left face
//          4+6,-4,-4+6, -4+6,-4,-4+6, -4+6, 4,-4+6,  4+6, 4,-4+6,  // back face
//          4+6,-4, 4+6,  4+6,-4,-4+6,  4+6, 4,-4+6,  4+6, 4, 4+6,  // right face
//          4+6, 4, 4+6,  4+6, 4,-4+6, -4+6, 4,-4+6, -4+6, 4, 4+6,  // top face
//          -4+6,-4, 4+6, -4+6,-4,-4+6,  4+6,-4,-4+6,  4+6,-4, 4+6,  // bottom face

//          -20,-4,20,  20,-4,20,  20,-4,-20,  -20,-4,-20,       // ground floor

//          -4+6,4, 4+6,   4+6,4, 4+6,  0+6,8, 4+6,           // the roof
//          4+6,4, 4+6,   4+6,4,-4+6,  0+6,8,-4+6,   0+6,8, 4+6,
//          -4+6,4, 4+6,   0+6,8, 4+6,  0+6,8,-4+6,  -4+6,4,-4+6,
//          4+6,4,-4+6,  -4+6,4,-4+6,  0+6,8,-4+6, 

//          -4+6,-4, 4-6,   4+6,-4, 4-6,   4+6, 4, 4-6,  -4+6, 4, 4-6,  // front face
//          -4+6,-4,-4-6,  -4+6,-4, 4-6,  -4+6, 4, 4-6,  -4+6, 4,-4-6,  // left face
//          4+6,-4,-4-6,  -4+6,-4,-4-6,  -4+6, 4,-4-6,   4+6, 4,-4-6,  // back face
//          4+6,-4, 4-6,   4+6,-4,-4-6,   4+6, 4,-4-6,   4+6, 4, 4-6,  // right face
//          4+6, 4, 4-6,   4+6, 4,-4-6,  -4+6, 4,-4-6,  -4+6, 4, 4-6,  // top face
//          -4+6,-4, 4-6,  -4+6,-4,-4-6,   4+6,-4,-4-6,   4+6,-4, 4-6,  // bottom face

//          -4+6,4, 4-6,   4+6,4, 4-6,  0+6,8, 4-6,           // the roof
//          4+6,4, 4-6,   4+6,4,-4-6,  0+6,8,-4-6,  0+6,8, 4-6,
//          -4+6,4, 4-6,   0+6,8, 4-6,  0+6,8,-4-6, -4+6,4,-4-6,
//          4+6,4,-4-6,  -4+6,4,-4-6,  0+6,8,-4-6, 

//          -4-6,-4, 4-6,   4-6,-4, 4-6,   4-6, 4, 4-6,  -4-6, 4, 4-6,  // front face
//          -4-6,-4,-4-6,  -4-6,-4, 4-6,  -4-6, 4, 4-6,  -4-6, 4,-4-6,  // left face
//          4-6,-4,-4-6,  -4-6,-4,-4-6,  -4-6, 4,-4-6,   4-6, 4,-4-6,  // back face
//          4-6,-4, 4-6,   4-6,-4,-4-6,   4-6, 4,-4-6,   4-6, 4, 4-6,  // right face
//          4-6, 4, 4-6,   4-6, 4,-4-6,  -4-6, 4,-4-6,  -4-6, 4, 4-6,  // top face
//          -4-6,-4, 4-6,  -4-6,-4,-4-6,   4-6,-4,-4-6,   4-6,-4, 4-6,  // bottom face

//          -4-6,4, 4-6,   4-6,4, 4-6,  0-6,8, 4-6,           // the roof
//          4-6,4, 4-6,   4-6,4,-4-6,  0-6,8,-4-6,  0-6,8, 4-6,
//          -4-6,4, 4-6,   0-6,8, 4-6,  0-6,8,-4-6, -4-6,4,-4-6,
//          4-6,4,-4-6,  -4-6,4,-4-6,  0-6,8,-4-6, 


//          -4-6,-4, 4+6,   4-6,-4, 4+6,   4-6, 4, 4+6,  -4-6, 4, 4+6,  // front face
//          -4-6,-4,-4+6,  -4-6,-4, 4+6,  -4-6, 4, 4+6,  -4-6, 4,-4+6,  // left face
//          4-6,-4,-4+6,  -4-6,-4,-4+6,  -4-6, 4,-4+6,   4-6, 4,-4+6,  // back face
//          4-6,-4, 4+6,   4-6,-4,-4+6,   4-6, 4,-4+6,   4-6, 4, 4+6,  // right face
//          4-6, 4, 4+6,   4-6, 4,-4+6,  -4-6, 4,-4+6,  -4-6, 4, 4+6,  // top face
//          -4-6,-4, 4+6,  -4-6,-4,-4+6,   4-6,-4,-4+6,   4-6,-4, 4+6,  // bottom face

//          -4-6,4, 4+6,   4-6,4, 4+6,  0-6,8, 4+6,           // the roof
//          4-6,4, 4+6,   4-6,4,-4+6,  0-6,8,-4+6,  0-6,8, 4+6,
//          -4-6,4, 4+6,   0-6,8, 4+6,  0-6,8,-4+6, -4-6,4,-4+6,
//          4-6,4,-4+6,  -4-6,4,-4+6,  0-6,8,-4+6, 

//         };

//   	float colors[] = {1,0,0, 1,1,0, 1,0,0, 1,0,1,
//                       0,1,0, 0,1,0, 0,1,1, 0,1,0,
//                       1,0,1, 1,0,0, 1,0,1, 1,0,0,
//                       1,1,0, 0,1,0, 0,1,1, 0,1,0,
//                       0,0,1, 1,0,1, 0,0,1, 0,1,1,
//                       1,0,1, 0,1,1, 0,0,1, 0,0,1,

//                       0,0,0, 0,1,0, 1,1,0, 1,0,0,  // ground floor

//                       0,1,1, 0,0,1, 1,0,1,     // roof
//                       1,0,0, 1,0,1, 1,0,0, 1,1,0,
//                       1,1,0, 0,1,0, 1,1,0, 0,1,0,
//                       0,1,1, 0,0,1, 1,0,1, 

//                       1,0,0, 1,1,0, 1,0,0, 1,0,1,
//                       0,1,0, 0,1,0, 0,1,1, 0,1,0,
//                       1,0,1, 1,0,0, 1,0,1, 1,0,0,
//                       1,1,0, 0,1,0, 0,1,1, 0,1,0,
//                       0,0,1, 1,0,1, 0,0,1, 0,1,1,
//                       1,0,1, 0,1,1, 0,0,1, 0,0,1,

//                       0,1,1, 0,0,1, 1,0,1,     // roof
//                       1,0,0, 1,0,1, 1,0,0, 1,1,0,
//                       1,1,0, 0,1,0, 1,1,0, 0,1,0,
//                       0,1,1, 0,0,1, 1,0,1, 

//                       1,0,0, 1,1,0, 1,0,0, 1,0,1,
//                       0,1,0, 0,1,0, 0,1,1, 0,1,0,
//                       1,0,1, 1,0,0, 1,0,1, 1,0,0,
//                       1,1,0, 0,1,0, 0,1,1, 0,1,0,
//                       0,0,1, 1,0,1, 0,0,1, 0,1,1,
//                       1,0,1, 0,1,1, 0,0,1, 0,0,1,

//                       0,1,1, 0,0,1, 1,0,1,     // roof
//                       1,0,0, 1,0,1, 1,0,0, 1,1,0,
//                       1,1,0, 0,1,0, 1,1,0, 0,1,0,
//                       0,1,1, 0,0,1, 1,0,1,

//                       1,0,0, 1,1,0, 1,0,0, 1,0,1,
//                       0,1,0, 0,1,0, 0,1,1, 0,1,0,
//                       1,0,1, 1,0,0, 1,0,1, 1,0,0,
//                       1,1,0, 0,1,0, 0,1,1, 0,1,0,
//                       0,0,1, 1,0,1, 0,0,1, 0,1,1,
//                       1,0,1, 0,1,1, 0,0,1, 0,0,1,

//                       0,1,1, 0,0,1, 1,0,1,     // roof
//                       1,0,0, 1,0,1, 1,0,0, 1,1,0,
//                       1,1,0, 0,1,0, 1,1,0, 0,1,0,
//                       0,1,1, 0,0,1, 1,0,1,
//     };


//   	// Add an object to the scene
//   	object = sceneManager->createObject();

//   	// Set up the vertex data
//   	VertexData& vertexData = object->vertexData;

//   	// Specify the elements of the vertex data:
//   	// - one element for vertex positions
//   	vertexData.vertexDeclaration.addElement(0, 0, 3, 
//                                             3*sizeof(float), RE330::VES_POSITION);
//   	// - one element for vertex colors
//   	vertexData.vertexDeclaration.addElement(1, 0, 3, 
//                                             3*sizeof(float), RE330::VES_DIFFUSE);

//   	// Create the buffers and load the data
//   	vertexData.createVertexBuffer(0, nVerts*3*sizeof(float), 
//                                   (unsigned char*)vertices);
//   	vertexData.createVertexBuffer(1, nVerts*3*sizeof(float), 
//                                   (unsigned char*)colors);

//   	// The index data that stores the connectivity of the triangles
//   	int indices[] = 
//         {0,2,3, 0,1,2,     // front face
//          4,6,7, 4,5,6,     // left face
//          8,10,11, 8,9,10,    // back face
//          12,14,15, 12,13,14,   // right face
//          16,18,19, 16,17,18,   // top face
//          20,22,23, 20,21,22,   // bottom face

//          24,26,27, 24,25,26,   // ground floor

//          28,29,30,       // roof
//          31,33,34, 31,32,33,
//          35,37,38, 35,36,37,
//          39,40,41, 

//          0+42, 2+42, 3+42,  0+42, 1+42, 2+42,   // front face
//          4+42, 6+42, 7+42,  4+42, 5+42, 6+42,   // left face
//          8+42,10+42,11+42,  8+42, 9+42,10+42,   // back face
//          12+42,14+42,15+42, 12+42,13+42,14+42,  // right face
//          16+42,18+42,19+42, 16+42,17+42,18+42,  // top face
//          20+42,22+42,23+42, 20+42,21+42,22+42,  // bottom face

//          28+42-28+24,29+42-28+24,30+42-28+24,   // roof
//          31+42-28+24,33+42-28+24,34+42-28+24, 31+42-28+24,32+42-28+24,33+42-28+24,
//          35+42-28+24,37+42-28+24,38+42-28+24, 35+42-28+24,36+42-28+24,37+42-28+24,
//          39+42-28+24,40+42-28+24,41+42-28+24, 

//          0+80,2+80,3+80, 0+80,1+80,2+80,    // front face
//          4+80,6+80,7+80, 4+80,5+80,6+80,    // left face
//          8+80,10+80,11+80, 8+80,9+80,10+80,   // back face
//          12+80,14+80,15+80, 12+80,13+80,14+80,  // right face
//          16+80,18+80,19+80, 16+80,17+80,18+80,  // top face
//          20+80,22+80,23+80, 20+80,21+80,22+80,  // bottom face

//          28+80-4,29+80-4,30+80-4,         // roof
//          31+80-4,33+80-4,34+80-4, 31+80-4,32+80-4,33+80-4,
//          35+80-4,37+80-4,38+80-4, 35+80-4,36+80-4,37+80-4,
//          39+80-4,40+80-4,41+80-4, 

//          0+118,2+118,3+118, 0+118,1+118,2+118,    // front face
//          4+118,6+118,7+118, 4+118,5+118,6+118,    // left face
//          8+118,10+118,11+118, 8+118,9+118,10+118,   // back face
//          12+118,14+118,15+118, 12+118,13+118,14+118,  // right face
//          16+118,18+118,19+118, 16+118,17+118,18+118,  // top face
//          20+118,22+118,23+118, 20+118,21+118,22+118,  // bottom face

//          28+118-4,29+118-4,30+118-4,          // roof
//          31+118-4,33+118-4,34+118-4, 31+118-4,32+118-4,33+118-4,
//          35+118-4,37+118-4,38+118-4, 35+118-4,36+118-4,37+118-4,
//          39+118-4,40+118-4,41+118-4, 
//         };	

// 	vertexData.createIndexBuffer(60 + (36 + 18) * 3, indices);
// 	num_objects = 1;
//     object_list = new Object*[num_objects];
//     int object_list_array = 0;
//     object_list[object_list_array++] = object;
// }

/*
** Sets up the teapot, which has normals.
*/
void RenderWidget0::setupTeapotAndDragon() {
    scene = new RobotScene(sceneManager);
    scene->init();
}


/*
** Sets up the default view, with the bunny in the center
** and the planet Earth off to the side.
*/
// void RenderWidget0::setupDefault() {
//     int nVerts;
//     float *vertices;
//     float *normals;
//     float *texcoords;
//     int nIndices;
//     int *indices;

//     ObjReader::readObj("bunny.obj", nVerts, &vertices, &normals,
//                        &texcoords, nIndices, &indices);
//     ObjReader::normalize(vertices, nVerts);

//     bunny = sceneManager->createObject();
//     VertexData& vertexData = bunny->vertexData;
//     vertexData.vertexDeclaration.addElement(0, 0, 3, 3*sizeof(float),
//                                             RE330::VES_POSITION);
//     vertexData.createVertexBuffer(0, nVerts*3*sizeof(float), 
//                                   (unsigned char*)vertices);
//     if(normals)
//     {
//         vertexData.vertexDeclaration.addElement(1, 0, 3, 3*sizeof(float),
//                                                 RE330::VES_NORMAL);		
//         vertexData.createVertexBuffer(1, nVerts*3*sizeof(float), 
//                                       (unsigned char*)normals);
//     }

//     vertexData.createIndexBuffer(nIndices, indices);

//     if(normals) delete[] normals;
//     if(texcoords) {
//         printf("texcoords 0, 1 and 2: %f, %f, %f\n", texcoords[0], texcoords[1], texcoords[2]);
//         delete[] texcoords;
//     }
//     delete[] vertices;
//     delete[] indices;

//     const int earth_colors = 14;
//     float earth_list[earth_colors][3] = {
//         {41, 121, 153},
//         {41, 121, 153},
//         {41, 121, 153},
//         {41, 121, 153},
//         {41, 121, 153},
//         {68, 158, 194},
//         {41, 121, 153},
//         {68, 158, 194},
//         {41, 121, 153},
//         {41, 121, 153},
//         {41, 121, 153},
//         {70, 127, 30},
//         {17, 104, 0},
//         {100, 77, 15}
//     };
//     toDecimal(earth_colors, earth_list);
  
//     earth = Shapes::createSphere(sceneManager, 0.5, 16, 64, 
//                                  earth_colors, earth_list, 1);
//     earth->setTransformation(earth->getTransformation() *
//                              Matrix4::translate(-4, 0, 0));
  
//     num_objects = 2;
//     object_list = new Object*[num_objects];
//     int object_list_array = 0;
//     object_list[object_list_array++] = bunny;
//     object_list[object_list_array++] = earth;
// }

/*
** Sets up the solar system demo, with the sun, earth, moon, satellite,
** mars, and jupiter.
*/
// void RenderWidget0::setupSolarSystem() {
//     const int sun_colors = 13;
//     float sun_list[sun_colors][3] = {
//         {255, 200, 0},
//         {224, 150, 0},
//         {255, 200, 0},
//         {255, 200, 0},
//         {255, 200, 0},
//         {224, 150, 0},
//         {255, 200, 0},
//         {255, 200, 0},
//         {230, 123, 2},
//         {194, 42, 0},
//         {128, 41, 17},
//         {255, 200, 0},
//         {224, 150, 0}
//     };
//     toDecimal(sun_colors, sun_list);
//     const int earth_colors = 14;
//     float earth_list[earth_colors][3] = {
//         {41, 121, 153},
//         {41, 121, 153},
//         {41, 121, 153},
//         {41, 121, 153},
//         {41, 121, 153},
//         {68, 158, 194},
//         {41, 121, 153},
//         {68, 158, 194},
//         {41, 121, 153},
//         {41, 121, 153},
//         {41, 121, 153},
//         {70, 127, 30},
//         {17, 104, 0},
//         {100, 77, 15}
//     };
//     toDecimal(earth_colors, earth_list);
//     const int moon_colors = 12;
//     float moon_list[moon_colors][3] = {
//         {255, 254, 247},
//         {176, 180, 214},
//         {255, 254, 247},
//         {176, 180, 214},
//         {255, 254, 247},
//         {176, 180, 214},
//         {255, 254, 247},
//         {255, 254, 247},
//         {255, 254, 247},
//         {255, 254, 247},
//         {176, 180, 214},
//         {114, 122, 179},
//     };
//     toDecimal(moon_colors, moon_list);
//     const int mars_colors = 9;
//     float mars_list[mars_colors][3] = {
//         {249, 84, 16},
//         {249, 84, 16},
//         {249, 84, 16},
//         {249, 84, 16},
//         {159, 48, 2},
//         {159, 48, 2},
//         {112, 4, 19},
//         {79, 6, 16},
//         {37, 0, 4},
//     };
//     toDecimal(mars_colors, mars_list);

//     const int jupiter_colors = 5;
//     float jupiter_list[jupiter_colors][3] = {
//         {106, 125, 142},
//         {194, 152, 102},
//         {104,74,52},
//         {146,64,32},
//         {194,152,102}
//     };
//     toDecimal(jupiter_colors, jupiter_list);
//     sun = Shapes::createSphere(sceneManager, 2, 64, 128, 
//                                sun_colors, sun_list, 1);
//     earth = Shapes::createSphere(sceneManager, 0.5, 16, 64, 
//                                  earth_colors, earth_list, 1);
//     moon = Shapes::createSphere(sceneManager, 0.125, 16, 64, 
//                                 moon_colors, moon_list, 1);
//     satellite = Shapes::createBox(sceneManager, 0.1, 0.075, 0.075,
//                                   moon_colors, moon_list, 1);
//     mars = Shapes::createSphere(sceneManager, 0.3, 16, 64, 
//                                 mars_colors, mars_list, 1);
//     jupiter = Shapes::createSphere(sceneManager, 1, 128, 128,
//                                    jupiter_colors, jupiter_list, 1);
//     num_objects = 6;
//     object_list = new Object*[num_objects];
//     int object_list_array = 0;
//     object_list[object_list_array++] = sun;
//     object_list[object_list_array++] = earth;
//     object_list[object_list_array++] = satellite;
//     object_list[object_list_array++] = moon;
//     object_list[object_list_array++] = mars;
//     object_list[object_list_array++] = jupiter;
// }

/*
** Sets up heightmap reading in hardcoded file.
*/
// void RenderWidget0::setupHeightmap() {
//     int rows, cols;
//     int & _rows = rows;
//     int & _cols = cols;
//     unsigned char * heights = loadPGM("Heightmap.pgm", _rows, _cols);

//     int nVerts = rows * cols;
//     int nIndices = 6 * (rows - 1) * (cols - 1);
//     float * vertices = new float[3 * nVerts];
//     float * colors = new float[3 * nVerts];
//     int * indices = new int[nIndices];
//     int index = 0;
//     // Create vertex array
//     for (int y = 0; y < cols; y++) {
//         for (int x = 0; x < rows; x++) {
//             vertices[index++] = 
//                 scale(x, 0, rows, 
//                       -1 * terrain_x_scale, 1 * terrain_x_scale);
//             vertices[index++] = 
//                 scale(heights[y * rows + x], 0, 255, 
//                       -1 * terrain_y_scale, 1 * terrain_y_scale);
//             vertices[index++] = 
//                 scale(y, 0, cols, 
//                       -1 * terrain_z_scale, 1 * terrain_z_scale);
//         }
//     }
//     index = 0;
  
//     // Create color array
//     float color_level;
//     for (int y = 0; y < cols; y++) {
//         for (int x = 0; x < rows; x++) {
//             color_level = scale(heights[y * rows + x], 0, 255, 0, 1);
//             if (color_level < 0.25) {
//                 // smooth gradient from blue to yellow
//                 // blue = (0, 0, 1)
//                 // yellow = (1, 1, 0)
//                 colors[index++] = scale(color_level, 0, 0.25, 0, 1);
//                 colors[index++] = scale(color_level, 0, 0.25, 0, 1);
//                 colors[index++] = scale(color_level, 0, 0.25, 1, 0);
//             } else if (color_level < 0.5) {
//                 // smooth gradient from yellow to green
//                 // yellow = (1, 1, 0)
//                 // green = (0, 1, 0)
//                 colors[index++] = scale(color_level, 0.25, 0.5, 1, 0);
//                 colors[index++] = scale(color_level, 0.25, 0.5, 1, 1);
//                 colors[index++] = scale(color_level, 0.25, 0.5, 0, 0);
//             } else if (color_level < 0.75) {
//                 // smooth gradient from green to brown
//                 // green = (0, 1, 0)
//                 // brown = (150/255, 75/255, 0)
//                 colors[index++] = scale(color_level, 0.5, 0.75, 0, 0.6);
//                 colors[index++] = scale(color_level, 0.5, 0.75, 1, 0.3);
//                 colors[index++] = scale(color_level, 0.5, 0.75, 0, 0);
//             } else if (color_level < 0.85) {
//                 // smooth gradient from brown to white
//                 // brown = (150/255, 75/255, 0)
//                 // white = (1, 1, 1)
//                 colors[index++] = scale(color_level, 0.75, 0.85, 0.6, 1);
//                 colors[index++] = scale(color_level, 0.75, 0.85, 0.3, 1);
//                 colors[index++] = scale(color_level, 0.75, 0.85, 0, 1);
//             } else {
//                 // the top 15% is pure white
//                 colors[index++] = 1;
//                 colors[index++] = 1;
//                 colors[index++] = 1;
//             }
//         }
//     }
  
//     // Create index array
//     index = 0;
//     for (int y = 0; y < cols - 1; y++) {
//         for (int x = 0; x < rows - 1; x++) {
//             indices[index++] = y * rows + x;
//             indices[index++] = (y + 1) * rows + x;
//             indices[index++] = y * rows + x + 1;
//             indices[index++] = (y + 1) * rows + x;
//             indices[index++] = (y + 1) * rows + x + 1;
//             indices[index++] = y * rows + x + 1;
//         }
//     }
  
//     terrain = sceneManager->createObject();
//     VertexData& vertexData = terrain->vertexData;
//     // Specify the elements of the vertex data:
//     // - one element for vertex positions
//     vertexData.vertexDeclaration.addElement(0, 0, 3, 3*sizeof(float),
//                                             RE330::VES_POSITION);
//     // - one element for vertex colors
//     vertexData.vertexDeclaration.addElement(1, 0, 3, 3*sizeof(int),
//                                             RE330::VES_DIFFUSE);
//     // Create the buffers and load the data
//     vertexData.createVertexBuffer(0, nVerts*3*sizeof(float), 
//                                   (unsigned char*)vertices);
//     vertexData.createVertexBuffer(1, nVerts*3*sizeof(float), 
//                                   (unsigned char*)colors);
//     vertexData.createIndexBuffer(nIndices, indices);
//     num_objects = 1;
//     object_list = new Object*[num_objects];
//     int object_list_array = 0;
//     object_list[object_list_array++] = terrain;
// }

/*
** Sets up either camera test viewing the primary-colored house
*/
// void RenderWidget0::setupTestCamera(int testcamera) {
//     if (testcamera == 1) {
//         camera->testCase1();
//     } else if (testcamera == 2) {
//         camera->testCase2();
//     }
  
//     // A house
//     int nVerts = 42;
//     float vertices[] = 
//         {-4,-4,4, 4,-4,4, 4,4,4, -4,4,4,     // front face
//          -4,-4,-4, -4,-4,4, -4,4,4, -4,4,-4,  // left face
//          4,-4,-4,-4,-4,-4, -4,4,-4, 4,4,-4,   // back face
//          4,-4,4, 4,-4,-4, 4,4,-4, 4,4,4,    // right face
//          4,4,4, 4,4,-4, -4,4,-4, -4,4,4,    // top face
//          -4,-4,4, -4,-4,-4, 4,-4,-4, 4,-4,4,  // bottom face

//          -20,-4,20, 20,-4,20, 20,-4,-20, -20,-4,-20,  // ground floor
//          -4,4,4, 4,4,4, 0,8,4,            // roof
//          4,4,4, 4,4,-4, 0,8,-4, 0,8,4,
//          -4,4,4, 0,8,4, 0,8,-4, -4,4,-4,
//          4,4,-4, -4,4,-4, 0,8,-4};
  
//     float colors[] = {1,0,0, 1,0,0, 1,0,0, 1,0,0,  // front face
//                       0,1,0, 0,1,0, 0,1,0, 0,1,0,   // left face
//                       1,0,0, 1,0,0, 1,0,0, 1,0,0,   // back face
//                       0,1,0, 0,1,0, 0,1,0, 0,1,0,   // right face
//                       0,0,1, 0,0,1, 0,0,1, 0,0,1,   // top face
//                       0,0,1, 0,0,1, 0,0,1, 0,0,1,   // bottom face
  
//                       0,0.5,0, 0,0.5,0, 0,0.5,0, 0,0.5,0,   // ground floor
//                       0,0,1, 0,0,1, 0,0,1,          // roof
//                       1,0,0, 1,0,0, 1,0,0, 1,0,0,
//                       0,1,0, 0,1,0, 0,1,0, 0,1,0,
//                       0,0,1, 0,0,1, 0,0,1,};
  
//     house = sceneManager->createObject();
  
//     // Set up the vertex data
//     VertexData& vertexData = house->vertexData;
  
//     // Specify the elements of the vertex data:
//     // - one element for vertex positions
//     vertexData.vertexDeclaration.addElement(0, 0, 3, 3*sizeof(float),
//                                             RE330::VES_POSITION);
//     // - one element for vertex colors
//     vertexData.vertexDeclaration.addElement(1, 0, 3, 3*sizeof(int),
//                                             RE330::VES_DIFFUSE);
  
//     // Create the buffers and load the data
//     vertexData.createVertexBuffer(0, nVerts*3*sizeof(float), 
//                                   (unsigned char*)vertices);
//     vertexData.createVertexBuffer(1, nVerts*3*sizeof(float), 
//                                   (unsigned char*)colors);
  
//     // The index data that stores the connectivity of the triangles
//     int indices[] = {0,2,3, 0,1,2,       // front face
//                      4,6,7, 4,5,6,      // left face
//                      8,10,11, 8,9,10,     // back face
//                      12,14,15, 12,13,14,  // right face
//                      16,18,19, 16,17,18,  // top face
//                      20,22,23, 20,21,22,  // bottom face
  
//                      24,26,27, 24,25,26,  // ground floor
//                      28,29,30,        // roof
//                      31,33,34, 31,32,33,
//                      35,37,38, 35,36,37,
//                      39,40,41}; 
  
//     vertexData.createIndexBuffer(60, indices);
//     num_objects = 1;
//     object_list = new Object*[num_objects];
//     int object_list_array = 0;
//     object_list[object_list_array++] = house;
// }

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
	sceneManager->renderScene();
}

void RenderWidget0::resizeRenderWidgetEvent(const QSize &s)
{
}

/*
** Takes care of turning, zooming in, and airplane movement
** as well as object animation.
*/ 
void RenderWidget0::timerEvent(QTimerEvent *t)
{
    // if (shadingmode) {
    //     dragon->setTransformation(dragon->getTransformation() * Matrix4::rotateY(0.03));
    //     teapot->setTransformation(teapot->getTransformation() * Matrix4::rotateY(-0.03));
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
        sceneManager->setWorldTransformation(
            Matrix4::rotateA(crossproduct, angle) *
            sceneManager->getWorldTransformation());
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
