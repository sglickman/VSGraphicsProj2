#ifndef __Shape3D_h__
#define __Shape3D_h__

namespace RE330 
{
	class RE330_EXPORT Shape3D : Leaf
	{
    public:
        Shape3D() : obj(NULL), mat(NULL) {}
        ~Shape3D() { 
            if ( _obj != 0 ) { delete _obj; }
            if ( _mat != 0 ) { delete _mat; }}

        Object* getObject() { return _obj; }
        Material* getMaterial() { return _mat; }
        
        void setObject(Object* obj) { _obj = obj; }
        void setMaterial(Material *mat) { _mat = mat; }
      
    protected:
        Object *_obj;
        Material *_mat;
	};
	
}

#endif

