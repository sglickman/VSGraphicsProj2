#ifndef __Shapes_h__
#define __Shapes_h__

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "Object.h"
#include "SceneManager.h"

namespace RE330
{
    class RE330_EXPORT Shapes
    {
        protected:
            
        public:
            /** These methods create basic shapes.
    		*/
            static Object *createSphere(float height, int slices, int points);

            static Object *createCone(float height, float base_radius, 
                                      int base_points);

            static Object *createRect(float width, float height);
            static Object *createBox(float height, float width, float depth);

            static float* coneVertices(float height, float base_radius, int base_points, const int num_colors);
            static float* coneColors(int base_points, const int num_colors, float color_list[][3]);
            static int* coneIndices(int base_points, const int num_colors, bool random_colors);

            static float* sphereVertices(float height, int slices, int points);
            static float* sphereColors(int slices, int points);
            static int* sphereIndices(int slices, int points);

            static float* boxVertices(float height, float width, float depth, const int num_colors);
            static float* boxColors(const int num_colors, float color_list[][3]);
            static int* boxIndices();
            static void setupObject(Object* obj, int nVerts, int nIndices, 
                                    float* v, float* n, int* i);
    };
    
}

#endif
