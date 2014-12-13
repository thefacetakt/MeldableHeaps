#ifndef _SKEW_HEAP
#define _SKEW_HEAP

#include "heaps.hpp"

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
        std::swap(first->left, first->right);
        return first;
    }
    
public:
    SkewHeap() : root(NULL)
    {
    }
    
    void Meld(IHeap &heap)
    {
        try
        {
            SkewHeap &skewHeap = dynamic_cast<SkewHeap &> (heap);
            Meld_(root, skewHeap.root);
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