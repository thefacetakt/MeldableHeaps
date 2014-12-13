#include "binomialHeap.hpp"
#include "leftistHeap.hpp"
#include "skewHeap.hpp"

#include <cstdio>

int main(int argc, char **argv)
{
    SkewHeap T;
    int n = atoi(argv[1]);
    for (int i = 0; i < n; ++i)
        T.insert(i + 1);
    for (int i = 0; i < n; ++i)
        T.extractMin();
    return 0;
}