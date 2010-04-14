#ifndef __Group_h__
#define __Group_h__

namespace RE330 
{
	class RE330_EXPORT Group : Node
	{
    public:
      std::list<Node *>::const_iterator getChildren();
      void addChild(Node * child);
      void removeChild(Node * child);
    protected:
      std::list<Node *>::const_iterator nodeList;
	};
	
}

#endif

