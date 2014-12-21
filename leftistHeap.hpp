#ifndef _LEFTIST_HEAP
#define _LEFTIST_HEAP

#include "leftistOrSkewHeap.hpp"

namespace NMeldableHeaps
{
//     class LeftistHeap : public LeftistOrSkewHeap
//     {
//         struct Node : public LeftistOrSkewHeap::Node
//         {
//             size_t rank;
//             explicit Node(int key) : LeftistOrSkewHeap::Node(key), rank(1) 
//             {
//             }
//         };
//         
//         size_t rankOf(LeftistHeap::Node *v)
//         {
//             return (v ? v->rank : 0);
//         }
//         
//         void recalc(Node *v)
//         {
//             if (v)
//             {
//                 v->rank = 1 + rankOf(v->right);
//             }
//         }
//         
//         Node * meld_(LeftistHeap::Node *&first, LeftistHeap::Node *&second)
//         {
//             LeftistOrSkewHeap::meld_(first, second);
//             if (rankOf(first->left) < rankOf(first->right))
//             {
//                 std::swap(first->left, first->right);
//             }
//             recalc(first);
//             return first;
//         }
//     public:
//         LeftistHeap() : LeftistOrSkewHeap() 
//         {
//         }
//     };
    template<>
    struct Node<EM_LEFTIST>
    {
        int key;
        size_t rank;
        Node *left, *right;
        explicit Node(int key) : key(key), rank(1), left(NULL), right(NULL)
        {
        }
        virtual ~Node()
        {
            delete left;
            delete right;
        }
    };
    
    size_t rankOf(Node<EM_LEFTIST> *v)
    {
        return (v ? v->rank : 0);
    }
    
    void recalc(Node<EM_LEFTIST> *v)
    {
        if (v)
        {
            v->rank = 1 + rankOf(v->right);
        }
    }
    
    template<>
    class LeftistOrSkewHeap<EM_LEFTIST>
    {    
        Node<EM_LEFTIST> * meld_(Node<EM_LEFTIST> *&first, Node<EM_LEFTIST> *&second)
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
            if (rankOf(first->left) < rankOf(first->right))
            {
                std::swap(first->left, first->right);
            }
            recalc(first);
            second = NULL;
            return first;
        }
    };
    
    
    typedef LeftistOrSkewHeap<EM_LEFTIST> LeftistHeap;
    
    int createSmt()
    {
        LeftistHeap *x = new LeftistHeap();
        x->insert(5);
        return x->getMinimalElement();
    }
    

};
/*
namespace NMeldableHeaps
{
    class LeftistHeap : public IHeap
    {
        struct Node
        {
            int key;
            size_t rank;
            Node *left, *right;
            explicit Node(int key) : key(key), rank(1), left(NULL), right(NULL)
            {
            }
            ~Node()
            {
                delete left;
                delete right;
            }
        };
        
        Node *root;
        size_t size_;
        
        static size_t rankOf(Node *v)
        {
            return (v ? v->rank : 0);
        }
        
        static void recalc(Node *v)
        {
            if (v)
            {
                v->rank = 1 + rankOf(v->right);
            }
        }
        
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
            if (rankOf(first->left) < rankOf(first->right))
            {
                std::swap(first->left, first->right);
            }
            recalc(first);
            second = NULL;
            return first;
        }
        
    public:
        LeftistHeap() : root(NULL), size_(0)
        {
        }
        
        void meld(IHeap &heap)
        {
            try
            {
                size_ += heap.size();
                LeftistHeap &leftistHeap = dynamic_cast<LeftistHeap &> (heap);
                root = meld_(root, leftistHeap.root);
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
    };
};
*/
#endif