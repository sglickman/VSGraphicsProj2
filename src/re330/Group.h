#ifndef __Group_h__
#define __Group_h__
#include <list>
#include "Node.h"

using namespace std;

namespace RE330 
{
	class RE330_EXPORT Group : public virtual Node
	{
    public:
        Group() { nodeList = new list<Node*>(); }
        ~Group();

        void light(RenderContext *r, Matrix4 *C);
        void draw(RenderContext *r, Matrix4 *C);

        void addChild(Node *child);
        void removeChild(Node *child);

    protected:
        list<Node*> *nodeList;
	};
	
}

#endif

