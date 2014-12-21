#ifndef _SKEW_HEAP
#define _SKEW_HEAP

#include "leftistOrSkewHeap.hpp"

namespace NMeldableHeaps
{
    class SkewNode : public INode
    {  
    public:
        explicit SkewNode(int key) : INode(key)
        {
        }
        
        void recalc()
        {
            std::swap(left, right);
        }
    };
    
    class SkewHeap : public LeftistOrSkewHeap  
    {
        INode *getNewNode(int key)
        {
            return new SkewNode(key);
        }
    };
};

#endif