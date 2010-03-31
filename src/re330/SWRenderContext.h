#ifndef __SWRenderContext_h__
#define __SWRenderContext_h__


#include "RE330_global.h"
#include "RenderContext.h"
#include "VertexDeclaration.h"
#include "Matrix4.h"
#include <QTime>
#include <limits>

namespace RE330 {

	/** This class implements the abstract base class RenderContext and
		it is the main interface to the low-level graphics API.
	@remarks
		This class also instantiates the Singleton class to make sure there is
		only one instance at any time.
	*/

	class SWWidget;
		
	class RE330_EXPORT SWRenderContext : public RenderContext
	{
	public:
		void init();
		void setViewport(int width, int height);
		void beginFrame();
		void endFrame();
		void setModelViewMatrix(const Matrix4 &m);
		void setProjectionMatrix(const Matrix4 &m);
		void updateVPM();
		/** This is the main method for rendering objects. Note that it uses
			OpenSW vertex arrays. See the OpenSW 2.0 book for details.
		*/
		void render(Object *object);

		/** Set the widget that will receive rendering output.
		*/
		void setWidget(SWWidget *swWidget);
    void boundingBox(int &xmin, int &xmax, int &ymin, int &ymax, 
      Vector3 a, Vector3 b, Vector3 c);
    void barycentricCoords(float x, float y, 
      Vector3 a, Vector3 b, Vector3 c, 
      float &alpha, float &beta, float &gamma);
    bool coordsInTriangle(float a, float b, float c,
      Vector3 v1, Vector3 v2, Vector3 v3);
    bool emptySquare(int y, int x, Vector3 v1,
      Vector3 v2, Vector3 v3);
    float f_function(Vector3 a, Vector3 b, float x, float y);
    float getZBuffer(int x, int y);
    void setZBuffer(int x, int y, float z);

		static SWRenderContext& getSingleton(void);
    static SWRenderContext* getSingletonPtr(void);

	private:
		SWWidget *mswWidget;
		QImage *image;
    int width, height;
		Matrix4 projection;
		Matrix4 modelview;
		Matrix4 viewport;
		Matrix4 total;
		// Cached viewport * projection * modelview calculation
    Matrix4 vpm;
    bool step1, hyp_shading, two_levels;
    int sub_size, rendered_frames, frame_count, sub_size_inc_count;
    QTime t;
    float** zbufferarray;
		void rasterizeTriangle(float p[3][4], float n[3][3], float c[3][4]);
	};

}

#endif