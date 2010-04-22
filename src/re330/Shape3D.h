#ifndef __Shape3D_h__
#define __Shape3D_h__
#include "Leaf.h"

namespace RE330 
{
	class RE330_EXPORT Shape3D : public Leaf
	{
    public:
        Shape3D() : _obj(NULL), _mat(NULL) {}
        Shape3D(Object *obj, Material *mat) {
            _obj = obj;
            _mat = mat;
        }
        ~Shape3D() {
            if (_obj) { delete _obj; }
            if (_mat) { delete _mat; }
        }

        void light(RenderContext *r, const Matrix4 &C) {};
        void draw(RenderContext *r, const Matrix4 &C, const Matrix4 &P, bool culling);

        Object* getObject() { return _obj; }
        Material* getMaterial() { return _mat; }
        
        void setObject(Object* obj) { 
            if(_obj) { delete _obj; }
            _obj = obj;
        }
        void setMaterial(Material* mat) { 
            if(_mat) { delete _mat; }
            _mat = mat; 
        }

    protected:
        Object *_obj;
        Material *_mat;
	};
	
}

#endif

