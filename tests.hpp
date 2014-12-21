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
    class ArrayOfHeps
    {
        std::vector <IHeap *> body;
        EHeapType heapType;
    public:
        explicit ArrayOfHeps(EHeapType heapType) : heapType(heapType)
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
        
        size_t size() const
        {
            return body.size();
        }
        
        size_t size(size_t index) const
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
        INSERT,
        GET_MINIMAL_ELEMENT,
        EXTRACT_MIN,
        MELD,
        ADD_HEAP,
        SIZE,
        OPERATIONS_NUMBER
    };
    
    TestResults randomTest(EHeapType heapType, size_t numberOfQueries, size_t seed)
    {
        srand(seed);
        
        ArrayOfHeps heaps(heapType);
        heaps.addHeap(rand());
        TestResults result;
        
        clock_t startTime = clock();
        for (size_t i = 1; i < numberOfQueries; ++i)
        {
            EQueryType currentQueryType = static_cast<EQueryType>(rand() % OPERATIONS_NUMBER);
            size_t index;
            switch (currentQueryType)
            {
                case INSERT:
                    heaps.insert(rand() % heaps.size(), rand());
                break; case GET_MINIMAL_ELEMENT:
                    index = rand() % heaps.size();
                    result.push(heaps.size(index) ? heaps.getMinimalElement(index) : 0);
                break; case EXTRACT_MIN:
                    index = rand() % heaps.size();
                    result.push(heaps.size(index) ? heaps.extractMin(index) : 0);
                break; case MELD:
                    heaps.meld(rand() % heaps.size(), rand() % heaps.size());
                break; case ADD_HEAP:
                    heaps.addHeap(rand());
                break; case SIZE:
                    index = rand() % heaps.size();
                    result.push(heaps.size(index));
            }
        }
        result.executionTime = (double)(clock() - startTime) / CLOCKS_PER_SEC;
        return result;
    }
};

#endif