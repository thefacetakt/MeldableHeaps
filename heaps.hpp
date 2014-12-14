#ifndef _HEAPS
#define _HEAPS

#include <typeinfo>

namespace NMeldableHeaps
{
    class IHeap
    {
    public:
        virtual void insert(int) = 0;
        virtual int extractMin() = 0;
        virtual int getMinimalElement() const = 0;
        virtual void meld(IHeap &) = 0;
        virtual size_t size() const = 0;
    };

    class IncorrectMeldException: public std::exception
    {
        const char* message = "Unmeldable type of heap\n";
    public:
        virtual const char* what() const throw()
        {
            return message;
        }
    };

    class EmptyHeapException: public std::exception
    {
        const char* message = "Trying to access element from an empty heap\n";
    public:
        virtual const char* what() const throw()
        {
            return message;
        }
    };
};

#include "binomialHeap.hpp"
#include "leftistHeap.hpp"
#include "skewHeap.hpp"

namespace NMeldableHeaps
{
    enum EHeapType
    {
        EM_BINOMIAL,
        EM_LEFTIST,
        EM_SKEW
    };

    IHeap *generateNewHeap(EHeapType heap)
    {
        switch (heap)
        {
            case EM_BINOMIAL:
                return new BinomialHeap();
            case EM_LEFTIST:
                return new LeftistHeap();
            case EM_SKEW:
                return new SkewHeap();
        }
    }
};

#endif