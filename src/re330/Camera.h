#ifndef __Camera_h__
#define __Camera_h__

#include "RE330_global.h"
#include "Frustum.h"
#include "Matrix4.h"
#include "Vector3.h"

namespace RE330 
{
	/** Camera specification.
	@remarks
		This class specifies a camera. The default camera is located at
		(0,0,10) in world coordinates and looks towards (0,0,0).
	*/
	class RE330_EXPORT Camera : public Frustum
	{
	public:
	        Camera() : viewMatrix(1,0,0,0, 0,1,0,0, 0,0,1,-10, 0,0,0,1), centerOfProjection(0, 0, 10), lookAtPoint(0, 0, 0), upVector(0, 1, 0) {};
	  
	        inline Camera(Vector3 cOfP, Vector3 lAtP, Vector3 uV)
	        {
		  centerOfProjection = cOfP;
		  lookAtPoint = lAtP;
		  upVector = uV;
          updateViewMatrix();

		}
		
		Vector3 getCenterOfProjection() { return centerOfProjection; }
		Vector3 getLookAtPoint() { return lookAtPoint; }
		Vector3 getUpVector() { return upVector; }

        void setCenterOfProjection(Vector3 cOfP) { centerOfProjection = cOfP; updateViewMatrix();}
        void setLookAtPoint(Vector3 lAtP) { lookAtPoint = lAtP; updateViewMatrix();}
        void setUpVector(Vector3 uV) { upVector = uV; updateViewMatrix();}
        
        void updateViewMatrix() {
            Vector3 z = centerOfProjection - lookAtPoint;
            z.normalize();
            Vector3 x = (upVector * z);
            x.normalize();
            Vector3 y = z * x;

            viewMatrix = Matrix4(
                x[0], x[1], x[2], -centerOfProjection[0] * x[0] - centerOfProjection[1] * x[1] - centerOfProjection[2] * x[2],
                y[0], y[1], y[2], -centerOfProjection[0] * y[0] - centerOfProjection[1] * y[1] - centerOfProjection[2] * y[2],
                z[0], z[1], z[2], -centerOfProjection[0] * z[0] - centerOfProjection[1] * z[1] - centerOfProjection[2] * z[2],
                0, 0, 0, 1
            );
        }
		void testCase1() {
            centerOfProjection = Vector3(0, 0, 40);
            lookAtPoint = Vector3(0, 0, 0);
            upVector = Vector3(0, 1, 0);
            setAspectRatio(1);
            setVerticalFieldOfView(60);
            setNearPlane(1);
            setFarPlane(100);
            updateViewMatrix();
		}
		
		void testCase2() {
            centerOfProjection = Vector3(-10, 40, 40);
            lookAtPoint = Vector3(-5, 0, 0);
            upVector = Vector3(0, 1, 0);
            setAspectRatio(1);
            setVerticalFieldOfView(60);
            setNearPlane(1);
            setFarPlane(100);
            updateViewMatrix();
		}
		
		void scene1() {
            centerOfProjection = Vector3(20, 20, 20);
            lookAtPoint = Vector3(0, 0, 0);
            upVector = Vector3(0, 1, 0);
            setAspectRatio(1);
            setVerticalFieldOfView(60);
            setNearPlane(1);
            setFarPlane(100);
            updateViewMatrix();
		}

		void scene2() {
            centerOfProjection = Vector3(-10, 20, 200);
            lookAtPoint = Vector3(-5, 0, 0);
            upVector = Vector3(0, 1, 0);
            setAspectRatio(1);
            setVerticalFieldOfView(60);
            setNearPlane(1);
            setFarPlane(100);
            updateViewMatrix();
		}
		
		const Matrix4 &getViewMatrix() const { return viewMatrix; }

	private:
		Matrix4 viewMatrix;
		Vector3 centerOfProjection;
		Vector3 lookAtPoint;
		Vector3 upVector;
	};
	
}

#endif

