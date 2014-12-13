#ifndef _BINOMIAL_HEAP
#define _BINOMIAL_HEAP

#include <algorithm>
#include <climits>
#include <vector>
#include <typeinfo>
#include "heaps.hpp"

//MinHeap
class BinomialHeap : public IHeap
{   
    struct BinomialTree
    {
        int key;
        
        BinomialTree *lastDescendant;
        BinomialTree *brother;
        
        BinomialTree(int key) : key(key), lastDescendant(NULL), brother(NULL)
        {
        }
        
        int getMinimalElement() const
        {
            return key;
        }
        
        ~BinomialTree()
        {
            if (lastDescendant)
            {
                delete lastDescendant;
            }
            if (brother)
            {
                delete brother;
            }
        }
    };
    BinomialTree *minimalTree;
    
    int minimalElementOf(BinomialTree *tree)
    {
        return (tree ? tree->getMinimalElement() : INT_MAX);
    }
    
    std::vector <BinomialTree *> trees;
    
    BinomialTree * MeldSimilar(BinomialTree *first, BinomialTree *second)
    {
        if (!first || !second)
        {
            return (first ? first : second);
        }
        if (first->getMinimalElement() > second->getMinimalElement())
        {
            std::swap(first, second);
        }
        
        second->brother = first->lastDescendant;
        first->lastDescendant = second;
        return first;
    }
    
    unsigned int isNull(BinomialTree *tree)
    {
        return !bool(tree);
    }
    
    void relaxMinimalTree(BinomialTree *tree)
    {
        if (minimalElementOf(tree) < minimalElementOf(minimalTree))
        {
            minimalTree = tree;
        }
    }
    
    BinomialHeap(int key)
    {
        trees.push_back(new BinomialTree(key));
        minimalTree = trees[0U];
    }
    
    
    //makes a heap from tree root's children and deletes root
    BinomialHeap(BinomialTree *tree)
    {
        minimalTree = NULL;
        if (tree)
        {
            BinomialTree *previous = NULL;
            for (BinomialTree *current = tree->lastDescendant; current; current = current->brother)
            {
                if (previous)
                {
                    previous->brother = NULL;
                }
                trees.push_back(current);
                relaxMinimalTree(current);
                previous = current;
            }
        }
        std::reverse(trees.begin(), trees.end());
        tree->brother = tree->lastDescendant = NULL;
        delete tree;
    }
    
public:
    BinomialHeap() : minimalTree(NULL)
    {
    }
    
    //Merges two Heaps - everything is put in the first one, second is made empty
    void Meld(IHeap &heap)
    {
        try
        {
            BinomialHeap &binomialHeap = dynamic_cast<BinomialHeap &> (heap);
            trees.resize(std::max(trees.size(), binomialHeap.trees.size()) + 1, NULL);
            binomialHeap.trees.resize(trees.size(), NULL);
            BinomialTree *carry = NULL;
            for (size_t i = 0; i < binomialHeap.trees.size(); ++i)
            {
                unsigned int numberOfNulls = isNull(trees[i]) + isNull(binomialHeap.trees[i]) + isNull(carry);
                
                if (!numberOfNulls)
                {
                    carry = MeldSimilar(carry, binomialHeap.trees[i]);
                }
                else
                {
                    //numberOfNulls == 1U
                    carry = MeldSimilar(MeldSimilar(trees[i], binomialHeap.trees[i]), carry);
                    trees[i] = NULL;
                    if (numberOfNulls == 2U)
                    {
                        std::swap(carry, trees[i]);
                    }
                }    
            }
            while (trees.size() && !trees.back())
            {
                trees.pop_back();
            }
            binomialHeap.trees.clear();
            binomialHeap.minimalTree = NULL;
            minimalTree = NULL;
            for (auto const &treePointer: trees)
            {
                relaxMinimalTree(treePointer);
            }
        }
        catch (const std::bad_cast &)
        {
            throw IncorrectMeldException();
        }
    }
    
    void insert(int key)
    {
        BinomialHeap temp(key);
        Meld(temp);
    }
    
    int extractMin()
    {
        if (minimalTree)
        {
            int result = minimalTree->getMinimalElement();
            BinomialHeap temp(minimalTree);
            
            for (auto &treePointer: trees)
            {
                if (treePointer == minimalTree)
                {
                    treePointer = NULL;
                    break;
                }
            }
            
            Meld(temp);
            return result;
        }
        throw EmptyHeapException();
    }
    
    int getMinimalElement() const
    {
        if (minimalTree)
        {
            return minimalTree->getMinimalElement();
        }
        throw EmptyHeapException();
    }
    ~BinomialHeap()
    {
        for (auto const &treePointer: trees)
        {
            delete treePointer;
        }
    }
};
#endif