#ifndef __Light_h__
#define __Light_h__

namespace RE330 {
    class Light;
}

#include "RE330_global.h"
#include "Leaf.h"
#include "Vector3.h"

namespace RE330 {
	class RE330_EXPORT Light : public Leaf
	{
	public:
		enum Type {
			DIRECTIONAL = 1,
			POINT = 2,
			SPOT = 3,
		};

		Light();
        ~Light();

        void light(RenderContext *r, const Matrix4 &C);
        void draw(RenderContext *r, const Matrix4 &C) {}

        // Quickly set the colors of the lights
        void setAllColors(Vector3 d, Vector3 s, Vector3 a)
        {
            mDiffuse = d; mSpecular = s; mAmbient = a;
        }

        // Quickly set the light to spot, point, or directional light
        void makeSpot(Vector3 pos, Vector3 dir, 
                      float exp, float cut)
        { 
            mPosition = pos; mSpotDirection = dir;
            mSpotExponent = exp; mSpotCutoff = cut;
            mType = SPOT;
        }
        void makePoint(Vector3 pos)
        {
            mPosition = pos;
            mType = POINT;
        }
        void makeDirectional(Vector3 dir)
        {
            mDirection = dir;
            mType = DIRECTIONAL;
        }

		Type getType() const;
		const Vector3 &getDirection() const;
		const Vector3 &getPosition() const;
		const Vector3 &getDiffuseColor() const;
		const Vector3 &getSpecularColor() const;
		const Vector3 &getAmbientColor() const;
		const Vector3 &getSpotDirection() const;
		float getSpotExponent() const;
		float getSpotCutoff() const;

		void setType(const Type type);
		void setDirection(const Vector3 &direction);
		void setPosition(const Vector3 &position);
		void setDiffuseColor(const Vector3 &diffuse);
		void setSpecularColor(const Vector3 &specular);
		void setAmbientColor(const Vector3 &ambient);
		void setSpotDirection(const Vector3 &spotDirection);
		void setSpotExponent(float spotExponent);
		void setSpotCutoff(float spotCutoff);

	private:
		Vector3 mDirection;
		Vector3 mPosition;
		Vector3 mDiffuse;
		Vector3 mSpecular;
		Vector3 mAmbient;
		Vector3 mSpotDirection;
		float mSpotExponent;
		float mSpotCutoff;
		Type mType;
	};


}

#endif
