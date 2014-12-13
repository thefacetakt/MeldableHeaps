#ifndef _LEFTIST_HEAP
#define _LEFTIST_HEAP

#include "heaps.hpp"

class LeftistHeap : public IHeap
{
    struct Node
    {
        int key;
        size_t rank;
        Node *left, *right;
        Node(int key) : key(key), rank(1), left(NULL), right(NULL)
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
    
    static Node * Meld_(Node *first, Node *second)
    {
        if (!first || !second)
        {
            return (first ? first : second);
        }
        if (first->key > second->key)
        {
            std::swap(first, second);
        }
        first->right = Meld_(first->right, second);
        if (rankOf(first->left) < rankOf(first->right))
        {
            std::swap(first->left, first->right);
        }
        recalc(first);
        return first;
    }
    
public:
    LeftistHeap() : root(NULL)
    {
    }
    
    void Meld(IHeap &heap)
    {
        try
        {
            LeftistHeap &leftistHeap = dynamic_cast<LeftistHeap &> (heap);
            Meld_(root, leftistHeap.root);
        }
        catch (const std::bad_cast &)
        {
            throw IncorrectMeldException();
        }
    }
    
    void insert(int key)
    {
        root = Meld_(root, new Node(key));
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
        Node *newRoot = Meld_(root->left, root->right);
        root->left = root->right = NULL;
        delete root;
        root = newRoot;
        return result;
    }
};

#endif