#ifndef _HEAPS_TESTS
#define _HEAPS_TESTS

#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "heaps.hpp"

using namespace NMeldableHeaps;

namespace NMeldableHeapsTests
{
    class arrayOfHeaps
    {
        std::vector <IHeap *> body;
        EHeapType heapType;
    public:
        arrayOfHeaps(EHeapType heapType) : heapType(heapType)
        {
        }
        
        void addHeap(int key)
        {
            body.push_back(generateNewHeap(heapType));
            body.back()->insert(key);
        }
        
        void insert(size_t index, int key)
        {
            body[index]->insert(key);
        }
        
        int extractMin(size_t index)
        {
            return body[index]->extractMin();
        }
        
        int getMinimalElement(size_t index) const
        {
            return body[index]->getMinimalElement();
        }
        
        void meld(size_t index1, size_t index2)
        {
            if (index1 == index2)
            {
                return;
            }
            if (index1 > index2)
            {
                std::swap(index1, index2);
            }
            body[index1]->meld(*body[index2]);
            std::swap(body[index2], body.back());
            body.pop_back();
        }
        
        size_t size()
        {
            return body.size();
        }
        
        size_t size(size_t index)
        {
            return body[index]->size();
        }
    };
    
    struct TestResults
    {
        std::vector <int> responces;
        double executionTime;
        void push(int result)
        {
            responces.push_back(result);
        }
    };
    
    enum EQueryType
    {
        INSERT = 0,
        GET_MINIMAL_ELEMENT = 1,
        EXTRACT_MIN = 2,
        MELD = 3,
        ADD_HEAP = 4
    };
    
    const unsigned int EQueryTypeSize = 5;
    
    TestResults randomTest(EHeapType heapType, size_t numberOfQueries, size_t seed)
    {
        srand(seed);
        arrayOfHeaps heaps(heapType);
        heaps.addHeap(rand());
        TestResults result;
        
        clock_t startTime = clock();
        for (size_t i = 1; i < numberOfQueries; ++i)
        {
            //EQueryType currentQueryType(rand() % EQueryTypeSize);
            size_t currentQueryType = rand() % EQueryTypeSize;
            size_t index;
            switch (currentQueryType)
            {
                case /*INSERT*/0:
                    heaps.insert(rand() % heaps.size(), rand());
                break; case /*GET_MINIMAL_ELEMENT*/1:
                    index = rand() % heaps.size();
                    if (heaps.size(index))
                    {
                        result.push(heaps.getMinimalElement(index));
                    }
                break; case /*EXTRACT_MIN*/2:
                    index = rand() % heaps.size();
                    if (heaps.size(index))
                    {
                        result.push(heaps.extractMin(index));
                    }
                break; case /*MELD*/3:
                    heaps.meld(rand() % heaps.size(), rand() % heaps.size());
                break; case /*ADD_HEAP*/4:
                    heaps.addHeap(rand());
            }
        }
        result.executionTime = (double)(clock() - startTime) / CLOCKS_PER_SEC;
        return result;
    }
};

#endif