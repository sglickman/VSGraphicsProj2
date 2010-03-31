#include "SWRenderContext.h"
#include "SWWidget.h"

using namespace RE330;

SWRenderContext* SWRenderContext::getSingletonPtr(void)
{
	return static_cast<SWRenderContext *>(ms_Singleton);
}

SWRenderContext& SWRenderContext::getSingleton(void)
{  
	assert( ms_Singleton );  
	return ( *(static_cast<SWRenderContext *>(ms_Singleton)) );  
}


void SWRenderContext::init()
{
  rendered_frames = 0;
  sub_size_inc_count = 0;
  frame_count = 200;
  t.start();
  step1 = false;
  hyp_shading = false;
  zbufferarray = NULL;
  sub_size = 2;
  two_levels = true;
	modelview = Matrix4::IDENTITY;
	projection = Matrix4::IDENTITY;
	viewport = Matrix4::IDENTITY;
	total = Matrix4::IDENTITY;
  updateVPM();
}

void SWRenderContext::setViewport(int w, int h)
{
  width = w;
  height = h;
	// Compute viewport matrix based on width, height.
	viewport = Matrix4::Matrix4(
	  ((float) width) / 2.0, 0, 0, ((float) width) / 2.0,
	  0, ((float) -height) / 2.0, 0, ((float) height) / 2.0,
	  0, 0, 0.5, 0.5,
	  0, 0, 0, 1
  );
  updateVPM();
}

void SWRenderContext::updateVPM() {
  vpm = viewport * projection * modelview;
}

/*
* Resets the image and z-buffer
*/
void SWRenderContext::beginFrame()
{
  rendered_frames++;
  // printf("Rendering frame %d out of %d.\n", rendered_frames, frame_count);
  if (rendered_frames == frame_count) {
    printf("%d frames rendered in %d milliseconds with subsquare size %d.\n",
      rendered_frames, t.restart(), sub_size);
    rendered_frames = 0;
    sub_size_inc_count++;
    if (sub_size_inc_count % 5 == 0) {
      sub_size *= 2;
    }
  }
	image->fill(qRgb(0,0,0));
  // set up the zbufferarray
  if (zbufferarray) {
    for (int i = 0; i < width; i++) {
      delete zbufferarray[i];
    }
    delete zbufferarray;
    zbufferarray = NULL;
  }
  if (!zbufferarray) {
    zbufferarray = new float*[width];
    for (int i = 0; i < width; i++) {
      zbufferarray[i] = new float[height];
      for (int j = 0; j < height; j++) {
        zbufferarray[i][j] = std::numeric_limits<float>::max();
      }
    }
  }
}

void SWRenderContext::endFrame()
{
	mswWidget->setPixmap(QPixmap::fromImage(*image));
	mswWidget->repaint();
}

void SWRenderContext::setModelViewMatrix(const Matrix4 &m)
{
	// Set modelview matrix.
  modelview = m;
  updateVPM();
}

void SWRenderContext::setProjectionMatrix(const Matrix4 &m)
{
	// Set projection matrix.
  projection = m;
  updateVPM();
}

void SWRenderContext::render(Object *object)
{
	VertexData& vertexData = object->vertexData;
	VertexDeclaration& vertexDeclaration = vertexData.vertexDeclaration;
	VertexBufferBinding& vertexBufferBinding = vertexData.vertexBufferBinding;

	unsigned char *pPtr;	// Pointer to vertex position
	int pStr;				// Stride: number of bytes between vertex entries
	
	int pSze;				// Size: number of vector elements per vertex
	            // position (typically 3)

	unsigned char *nPtr;
	int nStr;
	int nSze;

	unsigned char *cPtr;
	int cStr;
	int cSze;

	pPtr = 0;	// Disable all arrays per default
	nPtr = 0;
	cPtr = 0;

	// Set up arrays
	for(int j=0; j<vertexDeclaration.getElementCount(); j++)
	{
		const VertexElement *element = vertexDeclaration.getElement(j);

		const VertexBuffer& vertexBuffer = 
		  vertexBufferBinding.getBuffer(element->getBufferIndex());
		unsigned char* buf = vertexBuffer.getBuffer();

		int vertexStride = static_cast<int>(element->getStride());
		int vertexSize = static_cast<int>(element->getSize());
		int offset = element->getOffset();

		switch(element->getSemantic())
		{
			case VES_POSITION :
				pPtr = buf+offset;
				pStr = vertexStride;
				pSze = vertexSize;
				break;
			case VES_NORMAL :
				nPtr = buf+offset;
				nStr = vertexStride;
				nSze = 3;	// always
				break;
			case VES_DIFFUSE :
				cPtr = buf+offset;
				cStr = vertexStride;
				cSze = vertexSize;
				break;
		}
	}
	
	// Draw
	float p[3][4];	// Triangle vertex positions
	float c[3][4];	// Triangle vertex colors
	float n[3][3];	// Triangle vertex normals

	int *iPtr = vertexData.getIndexBuffer();

	for(int i=0; i<vertexData.getIndexCount(); i++)
	{
		// Local index of current triangle vertex
		int k = i%3;

		// Set default values
		p[k][0] = p[k][1] = p[k][2] = 0; 
		p[k][3] = 1.f;
		c[k][0] = c[k][1] = c[k][2] = 1.f;
		c[k][3] = 0;
		n[k][0] = n[k][1] = 0;
		n[k][2] = 1;

		// Vertex position
		if(pPtr)
		{
			float *cur = (float*)(pPtr + pStr*iPtr[i]);
			for(int s=0; s<pSze; s++)
			{
				p[k][s] = *cur;
				cur++;
			}
		}

		// Vertex normal
		if(nPtr)
		{
			float *cur = (float*)(nPtr + nStr*iPtr[i]);
			for(int s=0; s<nSze; s++)
			{
				n[k][s] = *cur;
				cur++;
			}
		}

		// Vertex color
		if(cPtr)
		{
			float *cur = (float*)(cPtr + cStr*iPtr[i]);
			for(int s=0; s<cSze; s++)
			{
				c[k][s] = *cur;
				cur++;
			}
		}

		// Draw triangle
		if(i%3 == 2)
		{
			rasterizeTriangle(p, n, c);
		}
	}
}

/*
** Computes the bounding box for a given triangle
*/
void SWRenderContext::boundingBox(int &xmin, int &xmax, int &ymin, int &ymax,
  Vector3 a, Vector3 b, Vector3 c) {
  
  xmin = (int) a[0] - 1;
  xmax = (int) a[0] + 1;
  ymin = (int) a[1] - 1;
  ymax = (int) a[1] + 1;
  int x, y;
  x = (int) b[0];
  if (x - 1 < xmin) { xmin = x - 1; } else if (x + 1 > xmax) { xmax = x + 1; }
  y = (int) b[1];
  if (y - 1 < ymin) { ymin = y - 1; } else if (y + 1 > ymax) { ymax = y + 1; }
  x = (int) c[0];
  if (x - 1 < xmin) { xmin = x - 1; } else if (x + 1 > xmax) { xmax = x + 1; }
  y = (int) c[1];
  if (y - 1 < ymin) { ymin = y - 1; } else if (y + 1 > ymax) { ymax = y + 1; }
  
  // Checking out-of-image bounds
  if (xmin < 0) { xmin = 0; }
  if (xmax < 0) { xmax = 0; }
  if (xmin > image->width()) { xmin = image->width(); }
  if (xmax > image->width()) { xmax = image->width(); }
  if (ymin < 0) { ymin = 0; }
  if (ymax < 0) { ymax = 0; }
  if (ymin > image->height()) { ymin = image->height(); }
  if (ymax > image->height()) { ymax = image->height(); }
}

/* 
** Used to compute barycentric coordinates.
** From the lecture: f_{ab}(p) = m ^ (p - a), where ^ is the dot product
*/
float SWRenderContext::f_function(Vector3 a, Vector3 b, float x, float y) {
  Vector3 m = Vector3(a[1] - b[1], b[0] - a[0], 1);
  Vector3 p = Vector3(x, y, 1);
  return m ^ (p - a);
}

/* 
** Computes barycentric coordinates for point (x, y) from triangle (a, b, c)
** Stores values to alpha, beta, gamma
*/
void SWRenderContext::barycentricCoords(float x, float y, Vector3 a, 
    Vector3 b, Vector3 c, float &alpha, float &beta, float &gamma) {
  float b_denom = f_function(a, c, b[0], b[1]);
  float g_denom = f_function(a, b, c[0], c[1]);
  // If the triangle is degenerate then we would divide by zero, a no-no
  // If this is the case, set coordinate to 2 so point is outside
  beta = (b_denom == 0 ? 2 : f_function(a, c, x, y) / b_denom);
  gamma = (g_denom == 0 ? 2 : f_function(a, b, x, y) / g_denom);
  alpha = 1 - beta - gamma;
}

/*
** Determines whether or not a given subsquare does not contain any pixels in
** the passed-in triangle.
** When this returns true, the square located at (a, b) with side length
** size has no pixels to be painted.
*/
bool SWRenderContext::emptySquare(int x, int y, Vector3 v1,
  Vector3 v2, Vector3 v3) {
    float a1, a2, a3, a4,
          b1, b2, b3, b4,
          c1, c2, c3, c4;
    barycentricCoords(x, y, v1, v2, v3, a1, b1, c1);
    barycentricCoords(x + sub_size, y, v1, v2, v3, a2, b2, c2);
    barycentricCoords(x + sub_size, y + sub_size, v1, v2, v3, a3, b3, c3);
    barycentricCoords(x, y + sub_size, v1, v2, v3, a4, b4, c4);
    // If at least one coordinate (e.g. beta) is negative
    // for all four corners of the subsquare, then 
    // the subsquare is completely out of the triangle.
    if (
      (a1 < 0 && a2 < 0 && a3 < 0 && a4 < 0) ||
      (b1 < 0 && b2 < 0 && b3 < 0 && b4 < 0) ||
      (c1 < 0 && c2 < 0 && c3 < 0 && c4 < 0)
      ) {
      return true;
    }
  return false;
}

/*
** Returns true if the barycentric coordinates a, b, c are within the range
** of acceptable values, using the top-fill convention.
*/
bool SWRenderContext::coordsInTriangle(float a, float b, float c,
  Vector3 v1, Vector3 v2, Vector3 v3) {
  if (0 <= a && 0 <= b && 0 <= c) {
    if (a <= EPSILON) {
      if (v3[1] - v2[1] > 0)
        return false;
      // check top vs. bottom
      if (v3[0] - v2[0] > 0)
        return false;
    }
    if (b <= EPSILON) {
      if (v1[1] - v3[1] > 0)
        return false;
      if (v1[0] - v3[0] > 0)
        return false;
    }
    if (c <= EPSILON) {
      if (v2[1] - v1[1] > 0)
        return false;
      if (v2[0] - v1[0] > 0)
        return false;
    }
    return true;
  } else {
    return false;
  }
}

/* 
** Draws in the pixels for the triangle
*/
void SWRenderContext::rasterizeTriangle(float p[3][4], float n[3][3],
  float c[3][4])
{
  Vector4 v14, v24, v34;
  v14 = Vector4(p[0]);
  v24 = Vector4(p[1]);
  v34 = Vector4(p[2]);
  v14 = vpm * v14;
  v24 = vpm * v24;
  v34 = vpm * v34;
  // Performing homogeneous division
  Vector3 v1, v2, v3;
  v1 = v14.hdiv();
  v2 = v24.hdiv();
  v3 = v34.hdiv();
  
  int white = 0xFFFFFF;
  if (step1) {
    // Displays only white points rather than a full rasterized image
    if (v1[0] >= 0 && v1[0] < image->width() && 
      v1[1] >= 0 && v1[1] < image->height())
        image->setPixel(v1[0], v1[1], white);
    if (v2[0] >= 0 && v2[0] < image->width() && 
      v2[1] >= 0 && v2[1] < image->height())
    image->setPixel(v2[0], v2[1], white);
    if (v3[0] >= 0 && v3[0] < image->width() && 
      v3[1] >= 0 && v3[1] < image->height())
    image->setPixel(v3[0], v3[1], white);
    return;
  }
  
  // testing for backface culling
  Vector3 v = (v2 - v1) * (v3 - v1);
  if (v[2] > 0) {
    return;
  }

  QRgb c1 = qRgb((int) (c[0][0] * 255), (int) (c[0][1] * 255),
    (int) (c[0][2] * 255));
  QRgb c2 = qRgb((int) (c[1][0] * 255), (int) (c[1][1] * 255),
    (int) (c[1][2] * 255));
  QRgb c3 = qRgb((int) (c[2][0] * 255), (int) (c[2][1] * 255),
    (int) (c[2][2] * 255));
  int color;
  int xmin, xmax, ymin, ymax;
  boundingBox(xmin, xmax, ymin, ymax, v1, v2, v3);
  float alpha, beta, gamma, z;
  for (int a = xmin; a <= xmax; a += sub_size) {
    for (int b = ymin; b <= ymax; b += sub_size) {
      // check if the square contains any of the triangle
      if (two_levels && emptySquare(a, b, v1, v2, v3)) {
        continue;
      }
      for (int i = a;
        i <= a + sub_size && i <= image->width() - 1; 
        i++) {
        for (int j = b;
          j <= b + sub_size && j <= image->height() - 1; 
          j++) {
          barycentricCoords((float) i + 0.5, 
            (float) j + 0.5,
            v1, v2, v3, 
            alpha, beta, gamma);  
          if (coordsInTriangle(alpha, beta, gamma, v1, v2, v3)) {
            z = alpha * v1[2] + beta * v2[2] + gamma * v3[2];
            // check the z buffer, if it's in front of the
            // previous pixel at that point, draw it.
            if (getZBuffer(i, j) > z) {
              setZBuffer(i, j, z);
              if (hyp_shading) {
                float w = alpha / v14[3] + beta / v24[3] + 
                  gamma / v34[3];
                float r = alpha * qRed(c1) / v14[3] +
                      beta * qRed(c2) / v24[3] +
                      gamma * qRed(c3) / v34[3];
                float g = alpha * qGreen(c1) / v14[3] +
                      beta * qGreen(c2) / v24[3] +
                      gamma * qGreen(c3) / v34[3];
                float b = alpha * qBlue(c1) / v14[3] +
                      beta * qBlue(c2) / v24[3] +
                      gamma * qBlue(c3) / v34[3];
                color = qRgb(r / w,
                       g / w,
                       b / w);
              } else {
                color = qRgb(alpha * qRed(c1) + beta * qRed(c2) +
                      gamma * qRed(c3),
                      alpha * qGreen(c1) + beta * qGreen(c2) +
                      gamma * qGreen(c3),
                      alpha * qBlue(c1) + beta * qBlue(c2) +
                      gamma * qBlue(c3)
                      );
              }
              image->setPixel(i, j, color);
            }
          } // end if coordsInTriangle()
        } // end i loop
      } // end j loop
    } // end b loop
  } // end a loop
}

float SWRenderContext::getZBuffer(int i, int j) {
  return zbufferarray[i][j];
}

void SWRenderContext::setZBuffer(int i, int j, float z) {
  zbufferarray[i][j] = z;
}

void SWRenderContext::setWidget(SWWidget *swWidget)
{
	mswWidget = swWidget;
	image = mswWidget->getImage();
}