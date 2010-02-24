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
	        Camera() : viewMatrix(1,0,0,0, 0,1,0,0, 0,0,1,-10, 0,0,0,1) {};
	  
	        inline Camera(Vector3 cOfP, Vector3 lAtP, Vector3 uV)
	        {
		  centerOfProjection = cOfP;
		  lookAtPoint = lAtP;
		  upVector = uV;
          updateViewMatrix();

		}
		
		Vector3 getCenterOfProjection() { return centerOfProjection; }
		Vector3 getlookAtPoint() { return lookAtPoint; }
		Vector3 getupVector() { return upVector; }

        void setCenterOfProjection(Vector3 cOfP) { centerOfProjection = cOfP; updateViewMatrix();}
        void setlookAtPoint(Vector3 lAtP) { lookAtPoint = lAtP; updateViewMatrix();}
        void setupVector(Vector3 uV) { upVector = uV; updateViewMatrix();}
        
        void updateViewMatrix() {
            Vector3 z = centerOfProjection - lookAtPoint;
            z.normalize();
            Vector3 x = (upVector * z);
            x.normalize();
            Vector3 y = z * x;

            viewMatrix = Matrix4(
                x.getX(), x.getY(), x.getZ(), -centerOfProjection.getX() * x.getX() - centerOfProjection.getY() * x.getY() - centerOfProjection.getZ() * x.getZ(),
                y.getX(), y.getY(), y.getZ(), -centerOfProjection.getX() * y.getX() - centerOfProjection.getY() * y.getY() - centerOfProjection.getZ() * y.getZ(),
                z.getX(), z.getY(), z.getZ(), -centerOfProjection.getX() * z.getX() - centerOfProjection.getY() * z.getY() - centerOfProjection.getZ() * z.getZ(),
                0, 0, 0, 1
            );
        }
		void testCase1() {
            centerOfProjection = Vector3(0, 0, 40);
            lookAtPoint = Vector3(0, 0, 0);
            upVector = Vector3(0, 1, 0);
            updateViewMatrix();
		}
		
		void testCase2() {
            centerOfProjection = Vector3(-10, 40, 40);
            lookAtPoint = Vector3(-5, 0, 0);
            upVector = Vector3(0, 1, 0);
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

