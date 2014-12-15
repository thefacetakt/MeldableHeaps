#ifndef _SKEW_HEAP
#define _SKEW_HEAP

#include "heaps.hpp"

namespace NMeldableHeaps
{
    class SkewHeap : public IHeap
    {
        struct Node
        {
            int key;
            Node *left, *right;
            Node(int key) : key(key), left(NULL), right(NULL)
            {
            }
            ~Node()
            {
                if (left)
                {
                    delete left;
                }
                if (right)
                {
                    delete right;
                }
            }
        };
        
        Node *root;
        size_t size_;
        
        static Node * meld_(Node *first, Node *second)
        {
            if (!first || !second)
            {
                return (first ? first : second);
            }
            if (first->key > second->key)
            {
                std::swap(first, second);
            }
            first->right = meld_(first->right, second);
            std::swap(first->left, first->right);
            return first;
        }
        
    public:
        SkewHeap() : root(NULL), size_(0)
        {
        }
        
        void meld(IHeap &heap)
        {
            try
            {
                size_ += heap.size();
                SkewHeap &skewHeap = dynamic_cast<SkewHeap &> (heap);
                root = meld_(root, skewHeap.root);
            }
            catch (const std::bad_cast &)
            {
                throw IncorrectMeldException();
            }
        }
        
        void insert(int key)
        {
            root = meld_(root, new Node(key));
            ++size_;
        }
        
        int getMinimalElement() const
        {
            if (!root)
            {
                throw EmptyHeapException();
            }
            return root->key;
        }
        
        int extractMin()
        {
            if (!root)
            {
                throw EmptyHeapException();
            }
            --size_;
            int result = root->key;
            Node *newRoot = meld_(root->left, root->right);
            root->left = root->right = NULL;
            delete root;
            root = newRoot;
            return result;
        }
        
        size_t size() const
        {
            return size_;
        }
    };
};
#endif