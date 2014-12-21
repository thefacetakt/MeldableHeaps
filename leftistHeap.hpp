#ifndef _LEFTIST_HEAP
#define _LEFTIST_HEAP

#include "leftistOrSkewHeap.hpp"

namespace NMeldableHeaps
{
    class LeftistNode : public INode
    {
        size_t rank;
        
        static size_t rankOf(LeftistNode *v)
        {
            return (v ? v->rank : 0);
        }
        
    public:
        explicit LeftistNode(int key) : INode(key), rank(1)
        {
        }
        
        void recalc()
        {
            LeftistNode *LeftistLeft = dynamic_cast<LeftistNode *>(left);
            LeftistNode *LeftistRight = dynamic_cast<LeftistNode *>(right);
            
            if (rankOf(LeftistLeft) < rankOf(LeftistRight))
            {
                std::swap(left, right);
            }
            rank = rankOf(LeftistRight) + 1;
        }
    };
    
    class LeftistHeap : public LeftistOrSkewHeap  
    {
        INode *getNewNode(int key)
        {
            return new LeftistNode(key);
        }
    };
};
#endif