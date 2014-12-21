#ifndef _LEFTIST_OR_SKEW_HEAP
#define _LEFTIST_OR_SKEW_HEAP

#include "heaps.hpp"
#include <typeinfo>

namespace NMeldableHeaps
{
    class INode
    {
    protected:
        int key;
        INode *left, *right;
        
    public:
        explicit INode(int key) : key(key), left(NULL), right(NULL)
        {
        }
        
        virtual void recalc() = 0;
        
        int getKey() const
        {
            return key;
        }
        
        INode *&getRight()
        {
            return right;
        }
        
        INode *&getLeft()
        {
            return left;
        }
        
        virtual ~INode()
        {
        }
        
    };
    
    class LeftistOrSkewHeap : public IHeap
    {   
        
        INode *root;
        size_t size_;
        
        INode * meld_(INode *&first, INode *&second)
        {
            if (!first || !second)
            {
                return (first ? first : second);
            }
            if (first->getKey() > second->getKey())
            {
                std::swap(first, second);
            }            
            first->getRight() = meld_(first->getRight(), second);
            first->recalc();
            second = NULL;
            return first;
        }
        
        virtual INode *getNewNode(int) = 0;
        
    public:
        LeftistOrSkewHeap() : root(NULL), size_(0)
        {
        }
        
        void meld(IHeap &heap)
        {
            try
            {
                size_ += heap.size();
                LeftistOrSkewHeap &skewHeap = dynamic_cast<LeftistOrSkewHeap &> (heap);
                root = meld_(root, skewHeap.root);
            }
            catch (const std::bad_cast &)
            {
                throw IncorrectMeldException();
            }
        }
        
        void insert(int key)
        {
            INode *temp = getNewNode(key);
            root = meld_(root, temp);
            ++size_;
        }
        
        int getMinimalElement() const
        {
            if (!root)
            {
                throw EmptyHeapException();
            }
            return root->getKey();
        }
        
        int extractMin()
        {
            if (!root)
            {
                throw EmptyHeapException();
            }
            int result = root->getKey();
            INode *newRoot = meld_(root->getLeft(), root->getRight());
            root->getLeft() = root->getRight() = NULL;
            delete root;
            root = newRoot;
            --size_;
            return result;
        }
        
        virtual size_t size() const
        {
            return size_;
        }
        
        virtual ~LeftistOrSkewHeap()
        {
            delete root;
        }
    };
};
#endif