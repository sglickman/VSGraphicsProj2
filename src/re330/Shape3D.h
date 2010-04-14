#ifndef __Shape3D_h__
#define __Shape3D_h__

namespace RE330 
{
	class RE330_EXPORT Shape3D : Leaf
	{
    public:
      Object* getObject();
      
    protected:
      Object* obj;
	};
	
}

#endif

