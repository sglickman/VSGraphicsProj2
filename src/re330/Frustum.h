#ifndef __Frustum_h__
#define __Frustum_h__

#include "RE330_global.h"
#include "Matrix4.h"

namespace RE330 
{
	/** This class defines a view frustum.
	@remarks
		The default view frustum has an aspect ratio of one and a field
		of view of about 45 degrees. The near and far clip planes are
		at 1 and 101 respectively.
	*/
	class RE330_EXPORT Frustum
	{
		friend class Camera;

	public:
		Frustum() :	p(2, 0, 0, 0, 0, 2, 0, 0, 0, 0, -1.02, -2.02, 0, 0, -1.f, 0.f) {};

		inline Frustum(float nP, float fP, float aP, float vFOV) 
		{
		  nearPlane = nP;
		  farPlane = fP;
		  aspectRatio = aP;
		  verticalFieldOfView = vFOV;
          updateMatrix();

          // float farMinusNear = farPlane - nearPlane;
		  
          // p = Matrix4(
          //      1/(aspectRatio*tan(verticalFieldOfView/2)), 0, 0, 0,
          //      0, 1/tan(verticalFieldOfView/2), 0, 0,
          //      0, 0, -(farPlane+nearPlane)/farMinusNear, -(2*farPlane*nearPlane)/farMinusNear,
          //      0, 0, -1, 0
          // );
		}
		const Matrix4 &getProjectionMatrix() const { return p; }
        void setNearPlane(float np) {
            nearPlane = np;
            updateMatrix();
		}
		void setFarPlane(float fp) {
            farPlane = fp;
            updateMatrix();
		}
		void setAspectRatio(float ap) {
            aspectRatio = ap;
            updateMatrix();
		}
		void setVerticalFieldOfView(float vfov) {
            verticalFieldOfView = M_PI * vfov / 180;
            updateMatrix();
		}
		
	private:
		Matrix4 p;
		float nearPlane;
		float farPlane;
		float aspectRatio;
		float verticalFieldOfView;
		void updateMatrix() {
		    p = Matrix4(
		        1/(aspectRatio*tan(verticalFieldOfView/2)), 0, 0, 0,
		        0, 1/tan(verticalFieldOfView/2), 0, 0,
		        0, 0, -(farPlane + nearPlane)/(farPlane - nearPlane), -(2 * farPlane * nearPlane) / (farPlane - nearPlane),
		        0, 0, -1, 0
            );
		}
	};

}

#endif

