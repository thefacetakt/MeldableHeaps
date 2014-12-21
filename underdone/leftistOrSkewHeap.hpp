#ifndef _LEFTIST_OR_SKEW_HEAP
#define _LEFTIST_OR_SKEW_HEAP

#include "heaps.hpp"

namespace NMeldableHeaps
{
    class LeftistOrSkewHeap : public IHeap
    {
    protected:
        virtual struct Node
        {
            int key;
            Node *left, *right;
            explicit Node(int key) : key(key), left(NULL), right(NULL)
            {
            }
            virtual ~Node()
            {
                delete left;
                delete right;
            }
        };
        
        Node *root;
        size_t size_;
        
        virtual Node * meld_(Node *&first, Node *&second)
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
            second = NULL;
            /*
            
            std::swap(first->left, first->right);
            return first;
            */
        }
        
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
            Node *temp = new Node(key);
            root = meld_(root, temp);
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
            int result = root->key;
            Node *newRoot = meld_(root->left, root->right);
            root->left = root->right = NULL;
            delete root;
            root = newRoot;
            --size_;
            return result;
        }
        
        size_t size() const
        {
            return size_;
        }
        
        virtual ~LeftistOrSkewHeap() = 0;
    };
    LeftistOrSkewHeap::~LeftistOrSkewHeap() 
    {
    }
};
#endif