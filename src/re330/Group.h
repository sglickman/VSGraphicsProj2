#ifndef __Group_h__
#define __Group_h__
#include <list>

using namespace std;

namespace RE330 
{
	class RE330_EXPORT Group : Node
	{
    public:
      list<Node*>::const_iterator getChildrenIterator();
      void addChild(Node *child);
      void removeChild(Node *child);

    protected:
      list<Node*>::const_iterator nodeList;
	};
	
}

#endif

