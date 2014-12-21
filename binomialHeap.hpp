#ifndef _BINOMIAL_HEAP
#define _BINOMIAL_HEAP

#include "heaps.hpp"

#include <algorithm>
#include <climits>
#include <vector>
#include <typeinfo>


namespace NMeldableHeaps
{
    class BinomialHeap : public IHeap
    {   
        struct BinomialTree
        {
            int key;
            
            BinomialTree *lastDescendant;
            BinomialTree *brother;
            
            explicit BinomialTree(int key) : key(key), lastDescendant(NULL), brother(NULL)
            {
            }
            
            int getMinimalElement() const
            {
                return key;
            }
            
            ~BinomialTree()
            {
                delete lastDescendant;
                delete brother;
            }
        };
        
        BinomialTree *minimalTree;
        
        std::vector <BinomialTree *> trees;
        size_t size_;
        
        int minimalElementOf(BinomialTree *tree)
        {
            return (tree ? tree->getMinimalElement() : INT_MAX);
        }
        
        BinomialTree * meldSimilar(BinomialTree *first, BinomialTree *second)
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
        
        explicit BinomialHeap(int key) : size_(1)
        {
            trees.push_back(new BinomialTree(key));
            minimalTree = trees[0U];
        }
        
        
        //makes a heap from tree root's children and deletes root
        BinomialHeap(BinomialTree *tree, size_t size_) : size_(size_ - 1)
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
        BinomialHeap() : minimalTree(NULL) , size_(0)
        {
        }
        
        //Merges two Heaps - everything is put in the first one, second is made empty
        void meld(IHeap &heap)
        {
            try
            {
                size_ += heap.size();
                BinomialHeap &binomialHeap = dynamic_cast<BinomialHeap &> (heap);
                trees.resize(std::max(trees.size(), binomialHeap.trees.size()) + 1, NULL);
                binomialHeap.trees.resize(trees.size(), NULL);
                BinomialTree *carry = NULL;
                for (size_t i = 0; i < binomialHeap.trees.size(); ++i)
                {
                    unsigned int numberOfNulls = isNull(trees[i]) + isNull(binomialHeap.trees[i]) + isNull(carry);
                    
                    if (!numberOfNulls)
                    {
                        carry = meldSimilar(carry, binomialHeap.trees[i]);
                    }
                    else
                    {
                        //numberOfNulls == 1U
                        carry = meldSimilar(meldSimilar(trees[i], binomialHeap.trees[i]), carry);
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
            meld(temp);
        }
        
        int extractMin()
        {
            if (minimalTree)
            {
                int result = minimalTree->getMinimalElement();
                size_t minimalTreeIndex = 0;
                
                for (size_t i = 0; i != trees.size(); ++i)
                {
                    if (trees[i] == minimalTree)
                    {
                        minimalTreeIndex = i;
                        break;
                    }
                }
                size_ -= (1U << minimalTreeIndex);
                BinomialHeap temp(minimalTree, (1U << minimalTreeIndex));
                
                trees[minimalTreeIndex] = NULL;
                
                meld(temp);
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
        
        size_t size() const 
        {
            return size_;
        }
        
        ~BinomialHeap()
        {
            for (auto const &treePointer: trees)
            {
                delete treePointer;
            }
        }
    };
};
#endif