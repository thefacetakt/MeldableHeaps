#ifndef _HEAPS
#define _HEAPS

class IHeap
{
    virtual void insert(int) = 0;
    virtual int extractMin() = 0;
    virtual int getMinimalElement() const = 0;
    virtual void Meld(IHeap &) = 0;
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

#endif